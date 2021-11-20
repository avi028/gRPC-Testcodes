#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
#include <pthread.h>

#include "MyCache.h"

using namespace std;

int CACHE_SIZE=3;

MyCache::MyCache(string key, string value, int freq, int isUpdated) {
    this->key = key;
    this->value = value;
    this->freq = freq;
    this->isUpdated = isUpdated;
}

MyCache::MyCache(string key, string value, int isUpdated) {
    this->key = key;
    this->value = value;
    this->freq = 0;
    this->isUpdated = isUpdated;
}

string MyCache::get_key() {
    return key;
}

string MyCache::get_value() {
    return value;
}

int MyCache::get_freq() {
    return freq;
}

int MyCache::get_isUpdated() {
    return isUpdated;
}

void MyCache::set_value(string value) {
    this->value = value;
}

void MyCache::set_freq(int freq) {
    this->freq = freq;
}

void MyCache::set_isUpdated(int isUpdated) {
    this->isUpdated = isUpdated;
}

std::vector<MyCache*> key_value_cache{};
std::vector<pthread_mutex_t> locks(100);
std::vector<std::string> key_queue{};

pthread_mutex_t KVlock;
pthread_mutex_t KQlock;
pthread_mutex_t KVClock;
// pthread_mutex_t temp;


int get_min() {
    int min = INT32_MAX, index = 0;
    for (int j=0; j<key_value_cache.size(); j++) {
        if (key_value_cache[j]->get_freq() < min) {
            min = key_value_cache[j]->get_freq();
            index = j;
        }
    } 
    return index;
}

std::vector<std::string> parser(string s1) {
    std::vector<std::string> str{};
    for (int i=0; i<s1.size(); i++) {
        if (s1[i] == ',') {
            str.push_back(s1.substr(0, i));
            str.push_back(s1.substr(i+1, s1.size()-i-1));
            break;
        }
    }
    return str;
}

string getCache(string key,int cacheType,Persistant *obj) {
    if(cacheType==Cache_LFU){
    auto it = key_value_cache.begin(); int index;

      do {
            pthread_mutex_lock(&KVlock);            
            it = std::find_if(key_value_cache.begin(), key_value_cache.end(), [key](MyCache* obj)->bool {return obj->get_key() == key;});
            index = it - key_value_cache.begin(); 
            pthread_mutex_unlock(&KVlock);            
        } while(pthread_mutex_lock(&locks[index]) == -1); 
        if (it != key_value_cache.end()) {
            key_value_cache[index]->set_freq(key_value_cache[index]->get_freq()+1);
            // for (int j=0; j<key_value_cache.size(); j++) {
            //     cout << key_value_cache[j]->get_key() << " " << key_value_cache[j]->get_freq() << " ";
            // }
            // cout << "\n";
            std::string val = key_value_cache[index]->get_value();
            pthread_mutex_unlock(&locks[index]);
            return val;
        }
        else {
            pthread_mutex_unlock(&locks[index]);
            std::string value = obj->get_value(key); // getValFromStorage(key);   
            if (value.compare("ERROR") == 0) {
                return ErrorMessage;
            }
            else {
                auto it1 = key_value_cache.begin();
                do {
                    pthread_mutex_lock(&KVlock);            
                    it1 = std::find_if(key_value_cache.begin(), key_value_cache.end(), [key](MyCache* obj)->bool {return obj->get_key() == key;});
                    pthread_mutex_unlock(&KVlock);            
                } while (pthread_mutex_lock(&locks[it1 - key_value_cache.begin()]) == -1); 
                
                if (it1 != key_value_cache.end()) {
                    if (key_value_cache[it1-key_value_cache.begin()]->get_isUpdated() == 2) {
                        pthread_mutex_unlock(&locks[it1 - key_value_cache.begin()]);
                        return ErrorMessage;
                    }
                    else if (key_value_cache[it1-key_value_cache.begin()]->get_isUpdated() == 1) {
                        std::string val = key_value_cache[it1-key_value_cache.begin()]->get_value();
                        pthread_mutex_unlock(&locks[it1 - key_value_cache.begin()]);
                        return val;
                    }
                    else {
                        pthread_mutex_unlock(&locks[it1 - key_value_cache.begin()]);
                        return value;
                    }
                }
                else {
                    pthread_mutex_unlock(&locks[it1 - key_value_cache.begin()]);
                    MyCache *newKV = new MyCache(key, value, 1, 0);
                    pthread_mutex_lock(&KVlock);
                    if (key_value_cache.size() == CACHE_SIZE) {
                        pthread_mutex_unlock(&KVlock);
                        int index;
                        do {
                            pthread_mutex_lock(&KVlock);
                            index = get_min();
                            pthread_mutex_unlock(&KVlock);
                        } while (pthread_mutex_lock(&locks[index]));
                        MyCache* temp = key_value_cache[index];
                        key_value_cache.erase(key_value_cache.begin()+index);
                        key_value_cache.insert(key_value_cache.begin()+index, newKV);

                        pthread_mutex_unlock(&locks[index]);

                        if (temp->get_isUpdated() == 1) {
                            obj->put_value(temp->get_key(),temp->get_value());
                            //putIntoStorage(temp->get_key(), temp->get_value());
                        }
                        else if (temp->get_isUpdated() == 2) {
                            obj->delete_value(temp->get_key());
                            //deleteFromStorage(temp->get_key());
                        }
                    }
                    else {
                        key_value_cache.push_back(newKV);
                        pthread_mutex_unlock(&KVlock);
                    }

                    // for (int j=0; j<key_value_cache.size(); j++) {
                    //     cout << key_value_cache[j]->get_key() << " " << key_value_cache[j]->get_freq() << " ";
                    // }
                    // cout << "\n";
                    return value;
                }
                
            }
        }
    }
    else if(cacheType==Cache_LRU){
            auto it1 = key_value_cache.begin(); 
            int index2;
            do {
                pthread_mutex_lock(&KQlock);
                it1 = std::find_if(key_value_cache.begin(), key_value_cache.end(), [key](MyCache* obj)->bool {return obj->get_key() == key;});
                index2 = it1 - key_value_cache.begin();
                pthread_mutex_unlock(&KQlock);
            } while (pthread_mutex_lock(&locks[index2]) == -1);
            // pthread_mutex_lock(&locks[index2]);
            if (it1 != key_value_cache.end()) {
                if (key_value_cache[index2]->get_isUpdated() == 2) {
                    pthread_mutex_unlock(&locks[index2]);
                    return ErrorMessage;
                }
                else {
                    std::string value = key_value_cache[index2]->get_value();

                    pthread_mutex_lock(&KQlock);

                    auto it = std::find_if(key_queue.begin(), key_queue.end(), [key](std::string obj)->bool {return obj == key;});
                    int index1 = it - key_queue.begin();
                    std::string temp_key = key_queue[index1];
                    key_queue.erase(it);
                    key_queue.push_back(temp_key);

                    pthread_mutex_unlock(&KQlock);

                    pthread_mutex_unlock(&locks[index2]);
                    return value;
                }
            }
            else {
                    pthread_mutex_unlock(&locks[index2]);
                    std::string value = obj->get_value(key); // getValFromStorage(key);   
                    if (value.compare(ErrorMessage) == 0) {
                        return ErrorMessage;
                    }
                    else {
                        auto it3 = key_value_cache.begin();
                        do {
                            pthread_mutex_lock(&KQlock);
                            it3 = std::find_if(key_value_cache.begin(), key_value_cache.end(), [key](MyCache* obj)->bool {return obj->get_key() == key;});
                            pthread_mutex_unlock(&KQlock);
                        } while (pthread_mutex_lock(&locks[it3-key_value_cache.begin()]) == -1);
                        // pthread_mutex_lock(&locks[it3-key_value_cache.begin()]);
                        if (it3 != key_value_cache.end()) {
                            if (key_value_cache[it3-key_value_cache.begin()]->get_isUpdated() == 2) {
                                pthread_mutex_unlock(&locks[it3-key_value_cache.begin()]);
                                return ErrorMessage;
                            }
                            else if (key_value_cache[it3-key_value_cache.begin()]->get_isUpdated() == 1) {
                                std::string val = key_value_cache[it3-key_value_cache.begin()]->get_value();
                                pthread_mutex_unlock(&locks[it3-key_value_cache.begin()]);
                                return val;
                            }
                            pthread_mutex_unlock(&locks[it3-key_value_cache.begin()]);
                            return value;
                        }
                        else {
                            pthread_mutex_unlock(&locks[it3-key_value_cache.begin()]);
                            MyCache *newKV = new MyCache(key, value, 0);
                            std::string temp_key;
                             pthread_mutex_lock(&KQlock);
                            if (key_queue.size()==CACHE_SIZE) {
                                temp_key = key_queue[0];
                                key_queue.erase(key_queue.begin());
                                key_queue.push_back(key);
                                pthread_mutex_unlock(&KQlock);   

                                do {
                                    pthread_mutex_lock(&KQlock);   
                                    it3 = std::find_if(key_value_cache.begin(), key_value_cache.end(), [temp_key](MyCache* obj)->bool {return obj->get_key() == temp_key;});
                                    pthread_mutex_unlock(&KQlock);   
                                } while (pthread_mutex_lock(&locks[it3-key_value_cache.begin()]) == -1);
                                // pthread_mutex_lock(&locks[it3-key_value_cache.begin()]);
                                MyCache *temp = key_value_cache[it3-key_value_cache.begin()];
                                key_value_cache.erase(it3);
                                key_value_cache.insert(it3, newKV);

                                pthread_mutex_unlock(&locks[it3-key_value_cache.begin()]);

                                if (temp->get_isUpdated() == 1) {
                                    obj->put_value(temp->get_key(), temp->get_value());
                                    // putIntoStorage(temp->get_key(), temp->get_value());
                                }
                                else if (temp->get_isUpdated() == 2) {
                                    obj->delete_value(temp->get_key());
                                    // deleteFromStorage(temp->get_key());
                                }
                            }
                            else {
                                key_queue.push_back(key);
                                pthread_mutex_unlock(&KQlock);
                                pthread_mutex_lock(&KQlock);
                                key_value_cache.push_back(newKV);
                                pthread_mutex_unlock(&KQlock);
                            }
                            return value;
                        } 
                    }
            }

    }
    return ErrorMessage;
} 

void putCache(string key, string value,int cacheType,Persistant *obj) {
    if(cacheType == Cache_LFU){
        auto it = key_value_cache.begin();
        int index;
        do {
            pthread_mutex_lock(&KVlock);
            it = std::find_if(key_value_cache.begin(), key_value_cache.end(), [key](MyCache* obj)->bool {return obj->get_key() == key;}); 
            index = it - key_value_cache.begin();
            pthread_mutex_unlock(&KVlock);
        } while (pthread_mutex_lock(&locks[index]) == -1);

        if (it != key_value_cache.end()) {
            key_value_cache[index]->set_freq(key_value_cache[index]->get_freq()+1);
            key_value_cache[index]->set_value(value);
            key_value_cache[index]->set_isUpdated(1);

            // for (int j=0; j<key_value_cache.size(); j++) {
            //     cout << key_value_cache[j]->get_key() << " " << key_value_cache[j]->get_freq() << " ";
            // }
            // cout << "\n";
            pthread_mutex_unlock(&locks[index]);
            return;
        }
        else {
            pthread_mutex_unlock(&locks[index]);
            pthread_mutex_lock(&KVlock);

            if (key_value_cache.size() == CACHE_SIZE) {
                // for (int j=0; j<key_value_cache.size(); j++) {
                //     cout << key_value_cache[j]->get_key() << " " << key_value_cache[j]->get_freq() << " ";
                // }
                // cout << "\n";
                pthread_mutex_unlock(&KVlock);

                int index;
                do {    

                    pthread_mutex_lock(&KVlock);
                    index = get_min(); 
                    pthread_mutex_unlock(&KVlock);
                } while (pthread_mutex_lock(&locks[index]) == -1);
    
                MyCache* temp = key_value_cache[index];
                key_value_cache.erase(key_value_cache.begin()+index);
                MyCache *newKV = new MyCache(key, value, 1, 1);
                key_value_cache.insert(key_value_cache.begin()+index, newKV);

                pthread_mutex_unlock(&locks[index]);

                if (temp->get_isUpdated() == 1) {
                    obj->put_value(temp->get_key(), temp->get_value());
                    //putIntoStorage(temp->get_key(), temp->get_value());
                }
                else if (temp->get_isUpdated() == 2) {
                   obj->delete_value(temp->get_key());
                    //deleteFromStorage(temp->get_key());
                }
            }
            else {
                // pthread_mutex_unlock(&KVlock);
                // pthread_mutex_lock(&KVlock);
                MyCache *newKV = new MyCache(key, value, 1, 1);
                key_value_cache.push_back(newKV);
                pthread_mutex_unlock(&KVlock);
            }
            pthread_mutex_lock(&KVlock);
                // for (int j=0; j<key_value_cache.size(); j++) {
                //     cout << key_value_cache[j]->get_key() << " " << key_value_cache[j]->get_freq() << " ";
                // }
                // cout << "\n";
            pthread_mutex_unlock(&KVlock);
            return;
        }
    }
    else if(cacheType == Cache_LRU){
         auto it2 = key_value_cache.begin();
        int index2;
        do {
            pthread_mutex_lock(&KQlock);
            it2 = std::find_if(key_value_cache.begin(), key_value_cache.end(), [key](MyCache* obj)->bool {return obj->get_key() == key;}); 
            index2 = it2 - key_value_cache.begin();
            pthread_mutex_unlock(&KQlock);
        } while (pthread_mutex_lock(&locks[index2]) == -1);
        // pthread_mutex_lock(&locks[index2]);
        if (it2 != key_value_cache.end()) {
            key_value_cache[index2]->set_value(value);
            key_value_cache[index2]->set_isUpdated(1);
            pthread_mutex_lock(&KQlock);

            auto it = std::find_if(key_queue.begin(), key_queue.end(), [key](std::string obj)->bool {return obj == key;});
            int index1 = it - key_queue.begin();
            std::string temp_key = key_queue[index1];
            key_queue.erase(it);
            key_queue.push_back(temp_key);

            // for (int j=0; j<key_value_cache.size(); j++) {
            //     cout << key_value_cache[j]->get_key() << " " << key_value_cache[j]->get_freq() << " ";
            // }

            // cout << "\n";
            
            pthread_mutex_unlock(&KQlock);
            
            pthread_mutex_unlock(&locks[index2]);
            
            return;
        }
        else {
            pthread_mutex_unlock(&locks[index2]); 
            std::string temp_key;
            pthread_mutex_lock(&KQlock);
            if (key_queue.size()==CACHE_SIZE) {
                temp_key = key_queue[0];
                key_queue.erase(key_queue.begin());
                key_queue.push_back(key);
                // for (int j=0; j<key_value_cache.size(); j++) {
                //     cout << key_value_cache[j]->get_key() << " " << key_value_cache[j]->get_freq() << " ";
                // }
                // cout << "\n";
                pthread_mutex_unlock(&KQlock);
                auto it2 = key_value_cache.begin();
                do {
                    pthread_mutex_lock(&KQlock);
                    it2 = std::find_if(key_value_cache.begin(), key_value_cache.end(), [temp_key](MyCache* obj)->bool {return obj->get_key() == temp_key;});
                    pthread_mutex_unlock(&KQlock);
                } while (pthread_mutex_lock(&locks[it2-key_value_cache.begin()]) == -1);
                // pthread_mutex_lock(&locks[it2-key_value_cache.begin()]);

                MyCache *temp = key_value_cache[it2-key_value_cache.begin()];
                key_value_cache.erase(it2);
                MyCache *newKV = new MyCache(key, value, 1);
                key_value_cache.insert(it2, newKV);

                pthread_mutex_unlock(&locks[it2-key_value_cache.begin()]);

                if (temp->get_isUpdated() == 1) {
                    obj->put_value(temp->get_key(), temp->get_value());
                    //putIntoStorage(temp->get_key(), temp->get_value());
                }
                else if (temp->get_isUpdated() == 2) {
                    obj->delete_value(temp->get_key());
                    //deleteFromStorage(temp->get_key());
                }
            }
            else {
                key_queue.push_back(key);
                MyCache *newKV = new MyCache(key, value, 1);
                key_value_cache.push_back(newKV);
                // for (int j=0; j<key_value_cache.size(); j++) {
                //     cout << key_value_cache[j]->get_key() << " " << key_value_cache[j]->get_freq() << " ";
                // }
                // cout << "\n";
                pthread_mutex_unlock(&KQlock);
            }
            return;
        }   
    }
} 

string delCache(string key,int cacheType,Persistant *obj) {
    if(cacheType == Cache_LFU){
        auto it = key_value_cache.begin();
        int index;
        do {
            pthread_mutex_lock(&KVlock);            
            it = std::find_if(key_value_cache.begin(), key_value_cache.end(), [key](MyCache* obj)->bool {return obj->get_key() == key;}); 
            index = it - key_value_cache.begin();
            pthread_mutex_unlock(&KVlock);            
        } while (pthread_mutex_lock(&locks[index]) == -1);
    
        if (it != key_value_cache.end()) {
            if (key_value_cache[it-key_value_cache.begin()]->get_isUpdated() == 2) {
                pthread_mutex_unlock(&locks[index]);
                return ErrorMessage;
            }
            else {
                key_value_cache[it-key_value_cache.begin()]->set_isUpdated(2);
                pthread_mutex_unlock(&locks[index]);
                return SuccessMessage;          
            }
        }
        else {
            pthread_mutex_unlock(&locks[index]);
            // deleteKeyFromStorage();
            return obj->delete_value(key);
        }
    }
    else if(cacheType == Cache_LRU){
        auto it1 = key_value_cache.begin();
        do {
            pthread_mutex_lock(&KQlock);            
            it1 = std::find_if(key_value_cache.begin(), key_value_cache.end(), [key](MyCache* obj)->bool {return obj->get_key() == key;});
            pthread_mutex_unlock(&KQlock);            
        } while (pthread_mutex_lock(&locks[it1-key_value_cache.begin()]) == -1);
        // pthread_mutex_lock(&locks[it1-key_value_cache.begin()]);
        if (it1 != key_value_cache.end()) {
            if (key_value_cache[it1-key_value_cache.begin()]->get_isUpdated() == 2) {
                pthread_mutex_unlock(&locks[it1-key_value_cache.begin()]);
                return ErrorMessage;
            }
            else {
                key_value_cache[it1-key_value_cache.begin()]->set_isUpdated(2);
                pthread_mutex_unlock(&locks[it1-key_value_cache.begin()]);
            return SuccessMessage;          
            }
        }
        else {
            pthread_mutex_unlock(&locks[it1-key_value_cache.begin()]);
            //deleteFromStorage(key);
            return obj->delete_value(key);
        }
    }
    return ErrorMessage;
} 

void cacheFill(){
    Persistant obj;
    for(int i=0;i<key_value_cache.size();i++)
    {       
        if(key_value_cache[i]->get_isUpdated()==1)
            obj.put_value(key_value_cache[i]->get_key(),key_value_cache[i]->get_value());
        else if (key_value_cache[i]->get_isUpdated()==2)
            obj.delete_value(key_value_cache[i]->get_key());
    }
}
void setCacheSize(int size){
    CACHE_SIZE=size;
}

void init_cache(){

    for (int i=0; i<=CACHE_SIZE; i++) {
        pthread_mutex_init(&locks[i], NULL);
    }
    pthread_mutex_init(&KVlock, NULL);
    pthread_mutex_init(&KQlock, NULL);
    pthread_mutex_init(&KVClock, NULL);
}

// void* fun(void *arg) {
//     Persistant obj;
// /*
// PUT k1 v1
// PUT k2 v2
// PUT k3 v3
// PUT k4 v4
// GET k3
// GET k5
// DEL k3
// DEL k3
// PUT k34 v1
// */ 
//     putCache("k1", "v1",1,&obj);
//     putCache("k2", "v2",1,&obj);
//     putCache("k3", "v3",1,&obj);
//     putCache("k4", "v4",1,&obj);
//      std::cout << getCache("k3",1,&obj) << "\n";
//     std::cout << getCache("k5",1,&obj) << "\n";
//     std::cout << delCache("k3",1,&obj) << "\n";
//     std::cout << delCache("k3",1,&obj) << "\n";
//     putCache("k34", "v1",1,&obj);
//     putCache("k15", "v1",1,&obj);
//     putCache("k25", "v2",1,&obj);
//     putCache("k35", "v3",1,&obj);
//     putCache("k45", "v4",1,&obj);
//     putCache("k15", "v1",1,&obj);
//     putCache("k255", "v2",1,&obj);
//     putCache("k53", "v3",1,&obj);
//     putCache("k45", "v4",1,&obj);
//     return 0;
// }


// #define tc 1
// int main() {
//     init_storage();
//     // string myText;
//     // ifstream MyReadFile("keyValue.txt");
//     // int count = 0;
//     // while (getline (MyReadFile, myText) && count<8) {
//     //     std::vector<string> tempkey = parser(myText);
//     //     MyCache *newKV = new MyCache(tempkey[0], tempkey[1], 1, 0);
//     //     key_value_cache.push_back(newKV);
//     //     count++;
//     // }    
//     setCacheSize(10);

//     init_cache();

//     pthread_t ths[tc];
//     int tid[10];
//     for (int i=0; i<tc; i++) {
//         tid[i] = i;
//     }


//     for (int i=0; i<tc; i++) {
//         pthread_create(&(ths[i]), NULL, &fun, (void *)&tid[i]);
//     }

//     for (int i=0; i<tc; i++) {
//         pthread_join(ths[i], NULL);
//     }

//     cacheFill();
//     // std::cout << get("key1") << "\n";
//     // std::cout << get("key7") << "\n";
//     // std::cout << get("key11") << "\n";
//     // std::cout << get("key20") << "\n";
//     // std::cout << get("key21") << "\n";
//     // std::cout << get("key15") << "\n";
//     // std::cout << get("key8") << "\n";
//     // put("key21", "value21");
//     // put("key15", "value22");
//     // put("key17", "value23");
//     // put("key1", "value24");
//     // put("key16", "value16");
//     // std::cout << del("key21") << "\n";
//     // std::cout << del("key11") << "\n";
//     // std::cout << del("key1") << "\n";
//     // std::cout << del("key15") << "\n";
//     return 0;
// }
