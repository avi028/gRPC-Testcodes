#include <iostream>
#include <vector>
#include <fstream>
#include <string>  
#include <bits/stdc++.h>
#include <utility>  
#include <pthread.h> 
#include <semaphore.h>
#include <map>

#define NUM_CHAR 8
#define MAX_SIZE 256
#define NUM_FILES MAX_SIZE / NUM_CHAR

using namespace std;

struct file {                        
    // pthread_mutex_t mu;
    // pthread_cond_t cond_read;
    // pthread_cond_t cond_write;
    // int AR = 0, AW = 0, WR = 0, WW = 0;
    sem_t mx , wrt;
    int ctr;
    map<string, std::iostream::pos_type> key_dict_read;
    map<string, std::iostream::pos_type> key_dict_write;
} files[NUM_FILES];

void init_storage(int thread_count){
    for (int file_no = 0; file_no != NUM_FILES; file_no++) {
        sem_init(&files[file_no].mx,0,thread_count);
        sem_init(&files[file_no].wrt,0,1);
    }
}


class Persistant {

//--------need to modify this------------
/*
ios::in	Open for input operations.
ios::out	Open for output operations.
ios::binary	Open in binary mode.
ios::ate	Set the initial position at the end of the file.If this flag is not set, the initial position is the beginning of the file.
ios::app	All output operations are performed at the end of the file, appending the content to the current content of the file.
ios::trunc	If the file is opened for output operations and it already existed, its previous content is deleted and replaced by the new one.
*/
private:
   fstream desc[NUM_FILES];
 
public:
    Persistant() {
        for (int i = 0; i != NUM_FILES; i++) {
            desc[i].open("storage/"+to_string(i) + ".txt", ios::app);
        }        
    }
    ~Persistant() {
        for (int i = 0; i != NUM_FILES; i++) {
            desc[i].close();
        }        
    }

    string get_padded_value(int init_size , string value) {
        char padded[(MAX_SIZE*2)-1-init_size+2];
        memset(padded, '#', sizeof(padded));
        strncpy(padded, value.c_str(), value.size());
        padded[(MAX_SIZE*2)-init_size]='\n';
        padded[(MAX_SIZE*2)-init_size+1]='\0';
        return padded;
    }


    string get_value(string key) {
        string out;
        int file_no = key.size() / NUM_CHAR;
        string path = "storage/"+to_string(file_no) + ".txt";
        pthread_mutex_t mutex_lock = files[file_no].mu;
        pthread_cond_t cv_read = files[file_no].cond_read;
        pthread_cond_t cv_write = files[file_no].cond_write;
        string myText;

        pthread_mutex_lock(&mutex_lock);
        while ((files[file_no].AW + files[file_no].WW) > 0) {
            files[file_no].WR++;
            pthread_cond_wait(&cv_read, &mutex_lock);
            files[file_no].WR--;
        }
        files[file_no].AR++;
        pthread_mutex_unlock(&mutex_lock);

        //----------------------
        ifstream read_fd;
        auto itr = files[file_no].key_dict_read.find(key);
        
        if (itr == files[file_no].key_dict_read.end())
            out = "KEY_NOT_EXIST";
        else {
            iostream::pos_type value_location = (itr)->second;
            read_fd.open(path.c_str());
            if (!read_fd){
                pthread_mutex_lock(&mutex_lock);
                files[file_no].AR--;
                if (files[file_no].AR == 0 && files[file_no].WW > 0)
                    pthread_cond_signal(&cv_write);
                pthread_mutex_unlock(&mutex_lock);
                out =  "FILE_ERROR";
            }
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
        //----------------------
        
        pthread_mutex_lock(&mutex_lock);
        files[file_no].AR--;
        if (files[file_no].AR == 0 && files[file_no].WW > 0)
            pthread_cond_signal(&cv_write);
        pthread_mutex_unlock(&mutex_lock);
        return out;
    }

    string put_value(string key, string value) {

        int file_no = key.size() / NUM_CHAR;
        string line = get_padded_value(key.size()+1,value);
        //----------------------

        desc[file_no].close();
        desc[file_no].open("storage/"+to_string(file_no) + ".txt",ios::out | ios::in );
        string result;
        auto itr = files[file_no].key_dict_write.find(key);
        if (itr == files[file_no].key_dict_write.end()){
             desc[file_no].seekp(0,ios_base::end);

            desc[file_no] << key << '#';
            files[file_no].key_dict_read.insert(make_pair(key, desc[file_no].tellg()));
            files[file_no].key_dict_write.insert(make_pair(key,desc[file_no].tellp()));
            files[file_no].key_dict_read.erase(key);
            files[file_no].key_dict_write.erase(key);
            desc[file_no] << line;

            result =  "inserted to file "+std::to_string(file_no)+"\n";
        }
        else {
            iostream::pos_type value_location = (itr)->second;
            desc[file_no].seekp((iostream::pos_type)((int)value_location - key.size() - 1));
            desc[file_no] << key << "#" << line;                          // overwrite the line1
            result = "updated to file "+std::to_string(file_no)+"\n";
        }
        desc[file_no].close();
        //-----------------------

        pthread_mutex_lock(&mutex_lock);
        files[file_no].AW--;
        if(files[file_no].WW>0)
            pthread_cond_signal(&cv_write);
        else if (files[file_no].WR > 0)
            pthread_cond_broadcast(&cv_read); 
        pthread_mutex_unlock(&mutex_lock);
        return result;
    } 

    string delete_value(string key) {
        int file_no = key.size() / NUM_CHAR;
        pthread_mutex_t mutex_lock = files[file_no].mu;
        pthread_cond_t cv_read = files[file_no].cond_read;
        pthread_cond_t cv_write = files[file_no].cond_write;
  
        pthread_mutex_lock(&mutex_lock);
        while ((files[file_no].AW + files[file_no].AR) > 0) { 
            files[file_no].WW++;
            pthread_cond_wait(&cv_write, &mutex_lock); 
            files[file_no].WW--;
        }
        files[file_no].AW++; 
        pthread_mutex_unlock(&mutex_lock);
        string result;
        //-------------------------------------
        auto itr = files[file_no].key_dict_write.find(key);
        if (itr == files[file_no].key_dict_write.end()) {
            result =  "Not_Found";
        }
        else {
            iostream::pos_type value_location = (itr)->second;
            desc[file_no].close();
            desc[file_no].open("storage/"+to_string(file_no) + ".txt", ios::out | ios::in);
            desc[file_no].seekp((iostream::pos_type)((int)value_location - key.size() - 1));
            for (int i =0; i < MAX_SIZE*2; i++) {
                desc[file_no] << "#";
            }
            desc[file_no].close();
            result =  "Success";
        }
        //-------------------------------------

        pthread_mutex_lock(&mutex_lock);
        files[file_no].AW--;
        if(files[file_no].WW>0)
            pthread_cond_signal(&cv_write);
        else if (files[file_no].WR > 0)
            pthread_cond_broadcast(&cv_read); 
        pthread_mutex_unlock(&mutex_lock);
        return result;
    }
};

void * func (void *args){
    Persistant p1 ;
    cout<< p1.put_value("key1", "value1");
    cout<< p1.put_value("key2", "value2");
    cout<< p1.get_value("key1") << "\n";
    cout<< p1.put_value("key1", "value5");
    cout<< p1.put_value("key3", "value21");
    cout<< p1.put_value("key2", "value21");
    cout << p1.delete_value("key2") << "\n";
    cout<< p1.get_value("key3") << "\n";
    cout<< p1.put_value("key4", "value21");
    cout<< p1.get_value("key1") << "\n";
    cout<< p1.put_value("keykeykeykeykey1", "value2");
    cout<< p1.put_value("keykeykeykeykeykeykeykeykeykeykeykeykeykeykeykeykey1", "value1");
    cout<< p1.put_value("keykeykeykeykeykeykeykeykeykeykeykeykeykeykeykeykey2", "value2");
    cout<< p1.put_value("keykeykeykeykeykeykeykeykeykeykeykeykeykeykeykeykey1", "value67");
    cout<< p1.put_value("keykeykeykeykeykeykeykeykeykeykeykeykeykeykeykeykey3", "value3");
    cout << p1.get_value("keykeykeykeykeykeykeykeykeykeykeykeykeykeykeykeykey1") << "\n";
    cout<< p1.delete_value("keykeykeykeykeykeykeykeykeykeykeykeykeykeykeykeykey3")<<endl;
    cout << p1.get_value("keykeykeykeykeykeykeykeykeykeykeykeykeykeykeykeykey3") << "\n";
    cout<< p1.put_value("key2", "value4");
    cout<< p1.put_value("key3", "value5");
    cout << p1.delete_value("key2") << "\n";
    cout << p1.get_value("key2") << "\n";
    cout << p1.get_value("key1") << "\n";
    cout << p1.get_value("keykeykeykeykeykeykeykeykeykeykeykeykeykeykeykeykey1") << "\n";
    cout << p1.get_value("key1") << "\n";
    cout << p1.get_value("key3") << "\n";
    return 0;
    
}

int main () {

    int thread_count=2;
    pthread_t tid[thread_count];

    for (int i=0; i<thread_count; i++) {
        pthread_create(&(tid[i]), NULL, &func, (void *)&tid[i]);
    }

    for (int i=0; i<thread_count; i++) {
        pthread_join(tid[i], NULL);
    }
}

