#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include "MyCache.h"


std::vector<std::string> parser_1(std::string request) {
  std::vector<std::string> tokens{};
  std::stringstream stream1(request);
  std::string intermediate;
  while(getline(stream1, intermediate, '=')) {
      tokens.push_back(intermediate);
  }
  return tokens;
}


configReader::configReader(){
        LISTENING_PORT = 50051;
        CACHE_REPLACEMENT_TYPE ="LRU";
        CACHE_SIZE=10;
        THREAD_POOL_SIZE=10;
    }

int configReader::readConfigFile(std::string filename){
    std::string myText;
    std::ifstream MyReadFile;
    MyReadFile.open(filename);
    if(MyReadFile.is_open())
    {
        while (getline(MyReadFile, myText)) {
            std::vector<std::string> tokens = parser_1(myText);
            if(tokens[0]=="LISTENING_PORT")
                LISTENING_PORT=atoi(tokens[1].c_str());
            else if(tokens[0]=="CACHE_REPLACEMENT_TYPE")
                CACHE_REPLACEMENT_TYPE=tokens[1];
            else if (tokens[0]=="CACHE_SIZE"){
                CACHE_SIZE = atoi(tokens[1].c_str());
            }
            else if(tokens[0]=="THREAD_POOL_SIZE"){
                THREAD_POOL_SIZE= atoi(tokens[1].c_str());
            }
        }    

    }
    else{
        return -1;
    }
    return 0;
}

int  configReader::getListeningPort(){
        return this->LISTENING_PORT;
    }

int configReader::getCacheReplacementType(){
    if(CACHE_REPLACEMENT_TYPE.compare("LFU")==0)
        return Cache_LFU;
    if(CACHE_REPLACEMENT_TYPE.compare("LRU")==0)
        return Cache_LRU;
    return -1;
}

int configReader::getCacheSize(){
    return this->CACHE_SIZE;
}

size_t configReader::getThreadPoolSize(){
    return this->THREAD_POOL_SIZE;
}