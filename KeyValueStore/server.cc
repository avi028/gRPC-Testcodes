/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <fstream>
#include <chrono>
#include <ctime> 
#include <sys/stat.h>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <csignal>
#include <grpc/support/log.h>
#include <grpcpp/grpcpp.h>

#include "MyCache.h"
// #include "configReader.h"


#ifdef BAZEL_BUILD
#include "examples/protos/keyvaluestore.grpc.pb.h"
#else
#include "keyvaluestore.grpc.pb.h"
#endif

//#define DebugFlag 1

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;
using keyvaluestore::storeManager;
using keyvaluestore::responseValue;
using keyvaluestore::requestKeyValue;
using keyvaluestore::requestKey;
using keyvaluestore::responseStatus;


int cacheType;

struct thread_arg{
  int tid;
  storeManager::AsyncService *service_;
  std::unique_ptr<ServerCompletionQueue> cq_;
}arg[50];

struct kv_pair {
  std::string key;
  std::string value;
};

std::mutex log_mutex;
std::condition_variable log_cv;

static std::vector<struct kv_pair> kvs_map;

//thread function declaration
void *HandleRpcs_thread(void *);
void printKvsMap();

std::vector<std::string> log_strings;

void write_log(std::string data)
{
  auto end = std::chrono::system_clock::now();
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  data = data + "\tAT\t"+std::ctime(&end_time)+"\n";

  std::unique_lock<std::mutex> lk(log_mutex);
     log_strings.push_back(data);
  lk.unlock();  
  log_cv.notify_one();    
}

void * log_writer(void*)
{
  mkdir("server_logs",S_IRWXU);
  std::string log_file = "server_logs/server.log"; 
  while(true){
    std::string data="";
    std::unique_lock<std::mutex> lk(log_mutex);
    while(log_strings.size()==0){
      log_cv.wait(lk);
    }
    for(size_t i=0;i<log_strings.size();i++)
      data += log_strings[i];
    log_strings.clear();
    lk.unlock();      
    std::fstream w;
    w.open(log_file,std::ios::app);
    w << data;
    w.close();
  }
}


class baseClass{
  public:
   virtual void Proceed()=0; 
};

class GetMethod: public baseClass{
  private:
    storeManager::AsyncService *service_;
    ServerCompletionQueue* cq_;
    ServerContext ctx_;
    requestKey request_;
    responseValue reply_;
    ServerAsyncResponseWriter<responseValue> responder_;
    enum CallStatus { CREATE, PROCESS, FINISH };
    CallStatus status_;
    int tid;
    Persistant *obj;
    keyvaluestore::statusValue get_value_from_map(std::string key, std::string & value) {
      // const std::lock_guard<std::mutex> lock(kvs_map_mutex);
      // for (size_t i = 0; i < kvs_map.size(); ++i) {        
      //   if (key.compare(kvs_map[i].key) == 0) {
      //     value =  kvs_map[i].value;
      //     return keyvaluestore::statusValue::SUCCESS;
      //   }
      // }
      // value=ErrorMessage;
      //  return keyvaluestore::statusValue::FAILURE;
      value = getCache(key,cacheType,obj);
      if(value.compare(ErrorMessage)==0)
        return keyvaluestore::statusValue::FAILURE;
      return keyvaluestore::statusValue::SUCCESS;
    }

  public :
    GetMethod(storeManager::AsyncService* service, ServerCompletionQueue* cq,int thread_id,Persistant *obj)
      : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE), tid(thread_id),obj(obj) {
      Proceed();
    }

    void Proceed() {
      if (status_ == CREATE) {
        status_ = PROCESS;
        service_->RequestGET(&ctx_, &request_, &responder_, cq_, cq_,this);
      } 
      else if (status_ == PROCESS) {
        new GetMethod(service_, cq_,this->tid,obj);
       write_log("GET request :key-"+request_.key());

        std::string value;
        reply_.set_status(get_value_from_map(request_.key(),value));
        reply_.set_value(value);
        status_ = FINISH;
        responder_.Finish(reply_, Status::OK, this);

        write_log("GET response :status-"+std::to_string(reply_.status())+(std::string)" value-"+reply_.value());
      } 
      else {
        GPR_ASSERT(status_ == FINISH);
        delete this;
      }
    }
};

class PutMethod: public baseClass{
  private:
    storeManager::AsyncService *service_;
    ServerCompletionQueue* cq_;
    ServerContext ctx_;
    requestKeyValue request_;
    responseStatus reply_;
    ServerAsyncResponseWriter<responseStatus> responder_;
    enum CallStatus { CREATE, PROCESS, FINISH };
    CallStatus status_;
    int tid;
    Persistant *obj;
    keyvaluestore::statusValue put_key_value_into_map(std::string key, std::string value) {
      // size_t i = 0;
      // const std::lock_guard<std::mutex> lock(kvs_map_mutex);
      // for (size_t i = 0; i < kvs_map.size(); ++i) {        
      //   if (key.compare(kvs_map[i].key) == 0) {
      //     kvs_map[i].value=value;
      //     return keyvaluestore::statusValue::UPDATED;
      //   }
      // }
      // struct kv_pair t;
      // t.key=key;
      // t.value=value;
      // kvs_map.push_back(t);
      putCache(key,value,cacheType,obj);
      return keyvaluestore::statusValue::SUCCESS;
    }


  public :
    PutMethod(storeManager::AsyncService* service, ServerCompletionQueue* cq,int thread_id,Persistant *obj)
      : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE), tid(thread_id),obj(obj) {
      Proceed();
    }

    void Proceed() {
      if (status_ == CREATE) {
        status_ = PROCESS;
        service_->RequestPUT(&ctx_, &request_, &responder_, cq_, cq_,this);
      } 
      else if (status_ == PROCESS) {
        new PutMethod(service_, cq_,this->tid,obj);
        
        write_log("PUT request :key-"+request_.key()+" value-"+request_.value());

        reply_.set_status(put_key_value_into_map(request_.key(),request_.value()));

        #ifdef DebugFlag
        std::cout<<"After PUT"<<std::endl;printKvsMap();std::cout<<std::endl;
        #endif

        status_ = FINISH;
        responder_.Finish(reply_, Status::OK, this);

        write_log("PUT response :status-"+std::to_string(reply_.status()));

      } 
      else {
        GPR_ASSERT(status_ == FINISH);
        delete this;
      }
    }
};

class DeleteMethod: public baseClass{
  private:
    storeManager::AsyncService *service_;
    ServerCompletionQueue* cq_;
    ServerContext ctx_;
    requestKey request_;
    responseValue reply_;
    ServerAsyncResponseWriter<responseValue> responder_;
    enum CallStatus { CREATE, PROCESS, FINISH };
    CallStatus status_;
    int tid;
    Persistant *obj;
    keyvaluestore::statusValue del_key_value_from_map(std::string key,std::string & value) {
      // const std::lock_guard<std::mutex> lock(kvs_map_mutex);
      // for (size_t i = 0; i < kvs_map.size(); ++i) {        
      //   if (key.compare(kvs_map[i].key) == 0) {
      //       kvs_map.erase(kvs_map.begin()+i);
      //       value=SuccessMessage;
      //       return keyvaluestore::statusValue::SUCCESS;
      //   }
      // }
      // value = ErrorMessage;
      // return keyvaluestore::statusValue::FAILURE;
      value = delCache(key,cacheType,obj);
      if(value.compare(ErrorMessage)==0)
        return keyvaluestore::statusValue::FAILURE;
      return keyvaluestore::statusValue::SUCCESS;
    }


  public :
    DeleteMethod(storeManager::AsyncService* service, ServerCompletionQueue* cq,int thread_id,Persistant *obj)
      : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE), tid(thread_id),obj(obj) {
      Proceed();
    }

    void Proceed() {
      if (status_ == CREATE) {
        status_ = PROCESS;
        service_->RequestDEL(&ctx_, &request_, &responder_, cq_, cq_,this);
      } 
      else if (status_ == PROCESS) {
        new DeleteMethod(service_, cq_,this->tid,obj);
        std::string value;

       write_log("DEL request :key-"+request_.key());

        reply_.set_status(del_key_value_from_map(request_.key(),value));
        reply_.set_value(value);
        
        #ifdef DebugFlag
        std::cout<<"After DEL"<<std::endl;printKvsMap();std::cout<<std::endl;
        #endif

        status_ = FINISH;
        responder_.Finish(reply_, Status::OK, this); 
        write_log("DEL response :status-"+std::to_string(reply_.status())+(std::string)" value-"+reply_.value());
      } 
      else {
        GPR_ASSERT(status_ == FINISH);
        delete this;
      }
    }
};

class ServerImpl final {
 private:
  storeManager::AsyncService service_;
  std::unique_ptr<Server> server_;
  int thread_count;
  bool running_flag;
 public:
  ServerImpl(){
    running_flag=false;    
  }
  ~ServerImpl() {
    if(running_flag==true){
      server_->Shutdown();
      for(int i=0;i<thread_count;i++) {
        arg[i].cq_->Shutdown();
      }
    }
  }
  int Run(int thread_count) {
    configReader config;
    if(config.readConfigFile("../../config.in")==-1){
      return -1;
    }
    else{
      running_flag=true;
      cacheType=config.getCacheReplacementType();
      init_cache();
      // std::cout<<cacheType<<std::endl;
      setCacheSize(config.getCacheSize());
      init_cache();
      this->thread_count=config.getThreadPoolSize();
      std::string server_address("0.0.0.0:"+std::to_string(config.getListeningPort()));
      ServerBuilder builder;
      builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
      builder.RegisterService(&service_);
      // struct thread_arg *arg = (struct thread_arg *)malloc(sizeof(struct thread_arg)*thread_count);
      pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*thread_count);
      for(int i=0;i<thread_count;i++){
        arg[i].tid=i+1;
        arg[i].cq_ = builder.AddCompletionQueue();
        arg[i].service_=&service_;
      }
      server_ = builder.BuildAndStart();

      for(int i=0;i<thread_count;i++){
        pthread_create(&threads[i],NULL,HandleRpcs_thread,&arg[i]);
      }
      std::cout << "Server listening on " << server_address << std::endl;
      
      std::string log = "\n-----------------------------------------------------------------------------------------------------------\n";
      log = log+"Server Started";
      write_log(log);

      for(int i=0;i<thread_count;i++){
        pthread_join(threads[i],NULL);
      }
    }
    return 0;
  }
};

#ifdef DebugFlag
void initializeKvsMap(int size){
  for(size_t i=0;i<size;i++){
    struct kv_pair t;
    t.key="key"+std::to_string(i+1);
    t.value="value"+std::to_string(i+1);
    kvs_map.push_back(t);
  }
}

void printKvsMap(){
  const std::lock_guard<std::mutex> lock(kvs_map_mutex);
  for (size_t i = 0; i < kvs_map.size(); i++){
    std::cout<<kvs_map[i].key<<" "<<kvs_map[i].value<<std::endl;
  }
}
#endif

void signal_handler( int signal_num ) {
   cacheFill();
   exit(signal_num);  
}
  
int main(int argc, char** argv) {
  signal(SIGINT, signal_handler);  
  init_storage();
  ServerImpl server;
  int size = 10;
  pthread_t log_thread;
  int log_thread_id=1;
  pthread_create(&log_thread,NULL,log_writer,&log_thread_id);
  if(server.Run(10)==-1)
    std::cout<<"Cannot read Config File Server Exiting...\n";
  pthread_join(log_thread,NULL);
//  cacheFill();
  return 0;
}

void * HandleRpcs_thread(void * thread_arg){
  Persistant obj;
  struct thread_arg *arg= (struct thread_arg *)thread_arg;
  new DeleteMethod((arg->service_), arg->cq_.get(),arg->tid,&obj);
  new PutMethod((arg->service_), arg->cq_.get(),arg->tid,&obj);
  new GetMethod((arg->service_), arg->cq_.get(),arg->tid,&obj);
  void* tag;  // uniquely identifies a request.
  bool ok;
  while (true) {
    GPR_ASSERT(arg->cq_->Next(&tag, &ok));
    // 0- shutdown 2-timeout 1-gotresponse
    GPR_ASSERT(ok);
    static_cast<baseClass*>(tag)->Proceed();
  }
}