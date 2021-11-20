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

#include <grpc/support/log.h>
#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

struct thread_arg{
  int tid;
  Greeter::AsyncService *service_;
  std::unique_ptr<ServerCompletionQueue> cq_;
}arg[50];

//thread function declaration
void *HandleRpcs_thread(void *);


class baseClass{
  public:
   virtual void Proceed()=0; 
};


class sayHelloMthod: public baseClass{
  private:
    Greeter::AsyncService *service_;
    ServerCompletionQueue* cq_;
    ServerContext ctx_;
    HelloRequest request_;
    HelloReply reply_;
    ServerAsyncResponseWriter<HelloReply> responder_;
    enum CallStatus { CREATE, PROCESS, FINISH };
    CallStatus status_;
    int tid;

  public :
    sayHelloMthod(Greeter::AsyncService* service, ServerCompletionQueue* cq,int thread_id)
      : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE), tid(thread_id) {
      Proceed();
    }

    void Proceed() {
      if (status_ == CREATE) {
        status_ = PROCESS;
        service_->RequestSayHello(&ctx_, &request_, &responder_, cq_, cq_,this);
      } 
      else if (status_ == PROCESS) {
        new sayHelloMthod(service_, cq_,this->tid);
        std::string prefix(" Hello ");
        std::string tid_str = std::to_string(this->tid);
        reply_.set_message(tid_str+prefix + request_.name());
        status_ = FINISH;
        responder_.Finish(reply_, Status::OK, this);
      } 
      else {
        GPR_ASSERT(status_ == FINISH);
        delete this;
      }
    }
};

class ServerImpl final {
 private:
  Greeter::AsyncService service_;
  std::unique_ptr<Server> server_;
  int thread_count;
 
 public:
  ~ServerImpl() {
    server_->Shutdown();
    // Always shutdown the completion queue after the server.
      for(int i=0;i<thread_count;i++) {
        arg[i].cq_->Shutdown();
      }
  }
  void Run(int thread_count) {
    this->thread_count=thread_count;
    std::string server_address("0.0.0.0:50034");
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

    for(int i=0;i<thread_count;i++){
      pthread_join(threads[i],NULL);
    }
  }
};

int main(int argc, char** argv) {
  ServerImpl server;
  server.Run(10);
  return 0;
}

void * HandleRpcs_thread(void * thread_arg){
    struct thread_arg *arg= (struct thread_arg *)thread_arg;
    new sayHelloMthod((arg->service_), arg->cq_.get(),arg->tid);
    void* tag;  // uniquely identifies a request.
    bool ok;
    while (true) {
      GPR_ASSERT(arg->cq_->Next(&tag, &ok));
      // 0- shutdown 2-timeout 1-gotresponse
      GPR_ASSERT(ok);
      static_cast<baseClass*>(tag)->Proceed();
    }
}