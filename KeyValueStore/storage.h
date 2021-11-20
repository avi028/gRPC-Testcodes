#include <iostream>
#include <string>  
#include <vector>

#define NUM_CHAR 8
#define MAX_SIZE 256
#define NUM_FILES MAX_SIZE / NUM_CHAR

static std::string SuccessMessage = "KEY DELETED";
static std::string ErrorMessage = "KEY NOT EXIST";
static std::string PutMessage = "KEY INSERTED";
static std::string UpdateMessage = "KEY UPDATED";

class Persistant {
private:
   std::fstream desc[NUM_FILES];
 
public:
    Persistant();
    ~Persistant();
    std::string get_padded_value(int init_size , std::string value);
    std::vector<std::string> parser(std::string line);
    std::string get_value(std::string key);
    std::string put_value(std::string key, std::string value);
    std::string delete_value(std::string key);
};

void init_storage();
