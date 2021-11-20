#include <iostream>
#include <string>

class configReader{
    private:       
        int LISTENING_PORT;
        std::string CACHE_REPLACEMENT_TYPE;
        int CACHE_SIZE;
        size_t THREAD_POOL_SIZE;

    public:
        configReader();
        int readConfigFile(std::string filename);
        int getListeningPort();
        int getCacheReplacementType();
        int getCacheSize();
        size_t getThreadPoolSize();
};