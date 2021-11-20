#include <iostream>
#include <vector>
#include <fstream>
#include <string>  
#include <bits/stdc++.h>
#include <utility>  
#include <pthread.h> 
#include <sys/stat.h>
#include <map>

#include "storage.h"

using namespace std;

struct file {                        
    pthread_mutex_t mu;
    pthread_cond_t cond_read;
    pthread_cond_t cond_write;
    map<string, std::iostream::pos_type> key_dict_read;
    map<string, std::iostream::pos_type> key_dict_write;
    int AR = 0, AW = 0, WR = 0, WW = 0;
} files[NUM_FILES];

void init_storage()
{
    mkdir("storage",S_IRWXU);
    for (int i=0; i<NUM_FILES; i++) {
        pthread_mutex_init(&files[i].mu, NULL);
        pthread_cond_init(&files[i].cond_read, NULL);
        pthread_cond_init(&files[i].cond_write, NULL);
    }
}

Persistant:: Persistant() {
    for (int i = 0; i != NUM_FILES; i++) {
        desc[i].open("storage/"+to_string(i) + ".txt", ios::app);
    }

}
Persistant::~Persistant() {
    for (int i = 0; i != NUM_FILES; i++) {
        desc[i].close();
    }        
}

string Persistant::get_padded_value(int init_size , string value) {
    char padded[(MAX_SIZE*2)-1-init_size+2];
    memset(padded, '#', sizeof(padded));
    strncpy(padded, value.c_str(), value.size());
    padded[(MAX_SIZE*2)-init_size]= '\n';
    padded[(MAX_SIZE*2)-init_size+1]='\0';
    return padded;
}

std::vector<std::string> Persistant::parser(std::string line) {
    std::vector<std::string> tokens{};
    std::stringstream stream1(line);
    std::string intermediate;
    while(getline(stream1, intermediate, '#')) {
        tokens.push_back(intermediate);
    }
    return tokens;
}

string Persistant::get_value(string key) {
    string out;
    int file_no = key.size() / NUM_CHAR;
    string path = "storage/"+to_string(file_no) + ".txt";
    pthread_mutex_t *mutex_lock = &files[file_no].mu;
    pthread_cond_t *cv_read = &files[file_no].cond_read;
    pthread_cond_t *cv_write = &files[file_no].cond_write;
    string myText;

    pthread_mutex_lock(mutex_lock);
    files[file_no].WR++;
    while ((files[file_no].AW + files[file_no].WW) > 0) {
        pthread_cond_wait(cv_read, mutex_lock);
    }
        files[file_no].WR--;
    files[file_no].AR++;
    pthread_mutex_unlock(mutex_lock);
    pthread_cond_broadcast(cv_read);

    //----------------------
    ifstream read_fd;
    auto itr = files[file_no].key_dict_read.find(key);

    desc[file_no].close();
    desc[file_no].open("storage/"+to_string(file_no) + ".txt",ios::out | ios::in );

    if (itr == files[file_no].key_dict_read.end()) {
        read_fd.open(path.c_str());
        string myText;
        int flag = 0;
        while (getline(read_fd, myText)) {
            std::vector<string> tokens = parser(myText);
            if (tokens[0].compare(key) == 0) {
                flag = 1;
                files[file_no].key_dict_read.insert(make_pair(key, (iostream::pos_type)((int)read_fd.tellg()-2*MAX_SIZE+key.size())));
                desc[file_no].seekp((iostream::pos_type)((int)read_fd.tellg()-2*MAX_SIZE+key.size()));
                files[file_no].key_dict_write.insert(make_pair(key, desc[file_no].tellp()));
                out = tokens[1];
                break;
            }
        }
        if (flag == 0) {
            out = ErrorMessage; 
        }
        read_fd.close();
    }
    else {
        iostream::pos_type value_location = (itr)->second;
        read_fd.open(path.c_str());
        if (!read_fd.is_open()){
            pthread_mutex_lock(mutex_lock);
            files[file_no].AR--;
            if (files[file_no].AR == 0 && files[file_no].WW > 0)
                pthread_cond_signal(cv_write);
            pthread_mutex_unlock(mutex_lock);
            out =  ErrorMessage;
        }
        else{
            char letter;
            read_fd.seekg(value_location,ios::beg);
            read_fd >> letter;
            int count=0;
            while(letter != '#' && count<MAX_SIZE){
                out += letter;
                read_fd >> letter;
                count++;
            }
            read_fd.close();
        }
    }
    //----------------------
    
    pthread_mutex_lock(mutex_lock);
    if ((--files[file_no].AR) == 0)
        pthread_cond_signal(cv_write);
    pthread_mutex_unlock(mutex_lock);
    return out;
}

string Persistant::put_value(string key, string value) {

    int file_no = key.size() / NUM_CHAR;
    pthread_mutex_t *mutex_lock = &files[file_no].mu;
    pthread_cond_t *cv_read = &files[file_no].cond_read;
    pthread_cond_t *cv_write = &files[file_no].cond_write;

    string line = get_padded_value(key.size()+1,value);
    pthread_mutex_lock(mutex_lock);
    files[file_no].WW++;
    if ((files[file_no].AW + files[file_no].AR) > 0) { 

        // std::cout<<"LOCKED "<<(files[file_no].AW + files[file_no].AR)<<std::endl;
        pthread_cond_wait(cv_write, mutex_lock); 
        // std::cout<<"FREED"<<std::endl;
    }
    files[file_no].WW--;
    files[file_no].AW++; 
    pthread_mutex_unlock(mutex_lock);
    // std::cout<<"ERROR"<<std::endl;
    //----------------------
    string path = "storage/"+to_string(file_no) + ".txt";
    desc[file_no].close();
    desc[file_no].open(path.c_str(),ios::out | ios::in );
    string result;
    auto itr = files[file_no].key_dict_write.find(key);
    if (itr == files[file_no].key_dict_write.end()){
        ifstream read_fd;
        read_fd.open(path.c_str());
        string myText;
        int flag = 0;
        while (getline(read_fd, myText)) {
            std::vector<string> tokens = parser(myText);
            if (tokens[0].compare(key) == 0) {
                flag = 1;
                files[file_no].key_dict_read.insert(make_pair(key, (iostream::pos_type)((int)read_fd.tellg()-2*MAX_SIZE+key.size())));
                desc[file_no].seekp((iostream::pos_type)((int)(read_fd.tellg())-2*MAX_SIZE-1));
                files[file_no].key_dict_write.insert(make_pair(key, (iostream::pos_type)((int)desc[file_no].tellp()+key.size()+1)));
                desc[file_no] << key << '#' << line;
                result = UpdateMessage;//"updated to file "+std::to_string(file_no)+"\n";
                break;
            }
        }
        if (flag == 0) {
            desc[file_no].seekp(0,ios_base::end);

            desc[file_no] << key << '#';
            files[file_no].key_dict_read.insert(make_pair(key, desc[file_no].tellg()));
            files[file_no].key_dict_write.insert(make_pair(key,desc[file_no].tellp()));
            desc[file_no] << line;

            result =  PutMessage;//"inserted to file "+std::to_string(file_no)+"\n"; 
        }
        read_fd.close();
        
    }
    else {
        iostream::pos_type value_location = (itr)->second;
        desc[file_no].seekp((iostream::pos_type)((int)value_location - key.size() -1));
        desc[file_no] << key << "#" << line;                          // overwrite the line1
        result = UpdateMessage;//"updated to file "+std::to_string(file_no)+"\n";
    }
    desc[file_no].close();
    //-----------------------

    pthread_mutex_lock(mutex_lock);
    files[file_no].AW--;
    // if(files[file_no].WR > 0)
        pthread_cond_broadcast(cv_read);
    // else
        pthread_cond_signal(cv_write);
    pthread_mutex_unlock(mutex_lock);
    return result;
} 

string Persistant::delete_value(string key) {
    int file_no = key.size() / NUM_CHAR;
    pthread_mutex_t *mutex_lock = &files[file_no].mu;
    pthread_cond_t *cv_read = &files[file_no].cond_read;
    pthread_cond_t *cv_write = &files[file_no].cond_write;

    pthread_mutex_lock(mutex_lock);
    while ((files[file_no].AW + files[file_no].AR) > 0) { 
        files[file_no].WW++;
        pthread_cond_wait(cv_write, mutex_lock); 
        files[file_no].WW--;
    }
    files[file_no].AW++; 
    pthread_mutex_unlock(mutex_lock);
    string result;

    string path = "storage/"+to_string(file_no) + ".txt";
    desc[file_no].close();
    desc[file_no].open(path.c_str(), ios::out | ios::in);

    //-------------------------------------
    auto itr = files[file_no].key_dict_write.find(key);
    if (itr == files[file_no].key_dict_write.end()) {
        ifstream read_fd;
        
        read_fd.open(path.c_str());
        string myText;
        int flag = 0;
        while (getline(read_fd, myText)) {
            std::vector<string> tokens = parser(myText);
            if (tokens[0].compare(key) == 0) {
                flag = 1;
                ofstream write_fd;
                desc[file_no].seekp((iostream::pos_type)((int)(read_fd.tellg())-2*MAX_SIZE -1));
                for (int i = 0; i < MAX_SIZE*2; i++) {
                    desc[file_no] << "#";
                }
                result = SuccessMessage;
                break;
            }
        }
        if (flag == 0) {
            result = ErrorMessage; 
        }
        read_fd.close();
    }
    else {
        iostream::pos_type value_location = (itr)->second;
        desc[file_no].seekp((iostream::pos_type)((int)value_location - key.size() - 1));
        files[file_no].key_dict_read.erase(key);
        files[file_no].key_dict_write.erase(key);
        for (int i =0; i < MAX_SIZE*2; i++) {
            desc[file_no] << "#";
        }
        result =  SuccessMessage;
        
    }
    desc[file_no].close();
    //-------------------------------------

    pthread_mutex_lock(mutex_lock);
    files[file_no].AW--;
    // if (files[file_no].WR > 0)
        pthread_cond_signal(cv_read); 
    // else
        pthread_cond_signal(cv_write);
    pthread_mutex_unlock(mutex_lock);
    return result;
}

// void * func (void *args){
//     Persistant p1 ;
//     cout<< p1.get_value("key1") << "\n"; 
//     cout<< p1.put_value("key1", "value1");
//     cout<< p1.put_value("key2", "value2"); 
//     cout<< p1.put_value("key1", "value5"); 
//     cout<< p1.put_value("key3", "value21");
//     cout<< p1.put_value("key2", "value21");
//     cout << "key2" << p1.delete_value("key2") << "\n";
//     cout<< p1.get_value("key3") << "\n";
//     cout<< p1.put_value("key4", "value21");
//     cout<< p1.get_value("key1") << "\n";
//     cout<< p1.put_value("key2", "value4");
//     cout<< p1.put_value("key3", "value5");
//     cout << "key2" << p1.delete_value("key2") << "\n";
//     cout << p1.get_value("key2") << "\n";
//     cout << p1.get_value("key1") << "\n";
//     cout << p1.get_value("keykeykeykeykeykeykeykeykeykeykeykeykeykeykeykeykey1") << "\n";
//     cout << p1.get_value("key1") << "\n";
//     cout << p1.get_value("key3") << "\n";
//     cout << "key4" << p1.delete_value("key4") << "\n";
//     cout<< p1.put_value("keykeykeykeykey1", "value2");
//     cout<< p1.put_value("keykeykeykeykeykeykeykeykeykeykeykeykeykeykeykeykey1", "value1");
//     cout<< p1.put_value("keykeykeykeykeykeykeykeykeykeykeykeykeykeykeykeykey2", "value2");
//     cout<< p1.put_value("keykeykeykeykeykeykeykeykeykeykeykeykeykeykeykeykey1", "value67");
//     cout<< p1.put_value("keykeykeykeykeykeykeykeykeykeykeykeykeykeykeykeykey3", "value3");
//     cout << p1.get_value("keykeykeykeykeykeykeykeykeykeykeykeykeykeykeykeykey1") << "\n";
//     cout << "keykeykeykeykeykeykeykeykeykeykeykeykeykeykeykeykey3" << p1.delete_value("keykeykeykeykeykeykeykeykeykeykeykeykeykeykeykeykey3") << "\n";
//     cout << p1.get_value("keykeykeykeykeykeykeykeykeykeykeykeykeykeykeykeykey3") << "\n";
//     return 0;
    
// }

// int main () {

//     int thread_count=20;
//     pthread_t tid[thread_count];


//     for (int i=0; i<NUM_FILES; i++) {
//         pthread_mutex_init(&files[i].mu, NULL);
//         pthread_cond_init(&files[i].cond_read, NULL);
//         pthread_cond_init(&files[i].cond_write, NULL);
//     }

//     for (int i=0; i<thread_count; i++) {
//         pthread_create(&(tid[i]), NULL, &func, (void *)&tid[i]);
//     }

//     for (int i=0; i<thread_count; i++) {
//         pthread_join(tid[i], NULL);
//     }
// }
