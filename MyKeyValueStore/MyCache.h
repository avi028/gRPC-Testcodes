#include <iostream>
#include <string>

#include "configReader.h"
#include "storage.h"

#define Cache_LFU 1
#define Cache_LRU 2

class MyCache {
    std::string key;
    std::string value;
    int freq;
    int isUpdated;

public:
    MyCache(std::string, std::string, int, int);
    MyCache(std::string, std::string, int);
    std::string get_key();
    std::string get_value();
    int get_freq();
    int get_isUpdated();
    void set_value(std::string);
    void set_freq(int);
    void set_isUpdated(int);
};

void setCacheSize(int size);
std::string getCache(std::string key,int cacheType,Persistant * obj);
void putCache(std::string key, std::string value,int cacheType,Persistant *obj);
std::string delCache(std::string key,int cacheType,Persistant*obj);
void init_cache();
void cacheFill();