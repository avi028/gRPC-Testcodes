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
#include <chrono>
#include <fstream>
#include <bits/stdc++.h>
#include <grpcpp/grpcpp.h>
#include <vector>
#include "configReader.h"

#ifdef BAZEL_BUILD
#include "examples/protos/keyvaluestore.grpc.pb.h"
#else
#include "keyvaluestore.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientAsyncResponseReader;
using grpc::CompletionQueue;
using grpc::Status;

using keyvaluestore::storeManager;
using keyvaluestore::requestKey;
using keyvaluestore::requestKeyValue;
using keyvaluestore::responseStatus;
using keyvaluestore::responseValue;
// using namespace std::chrono;

std::vector<std::string> parser(std::string request) {
  std::vector<std::string> tokens{};
  std::stringstream stream1(request);
  std::string intermediate;
  while(getline(stream1, intermediate, ' ')) {
      tokens.push_back(intermediate);
  }
  return tokens;
}

class KeyValueStoreClient {
 public:
  KeyValueStoreClient(std::shared_ptr<Channel> channel)
      : stub_(storeManager::NewStub(channel)) {
      }

  void BatchMode(const std::string filename) {
    std::string myText;
    std::ifstream MyReadFile(filename);
    std::vector<std::string> result_set{};
    std::vector<double> time_required{};

    while (getline(MyReadFile, myText)) {
      std::string result;
      keyvaluestore::statusValue cmdStatus;  
      std::vector<std::string> tokens = parser(myText);
      if (tokens[0].compare("GET") == 0) {
        if (tokens[1].size()<1 || tokens[1].size()>256) {
          result_set.push_back("Wrong key");
          continue;
        }
        else {
         auto start = std::chrono::high_resolution_clock::now();
          cmdStatus = GET(tokens[1],&result);
          auto stop = std::chrono::high_resolution_clock::now(); 
          auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
          time_required.push_back(time.count() * 1e-9);
        }
      }
      else if (tokens[0].compare("PUT") == 0) {
        if ((tokens[1].size()<1 || tokens[1].size()>256) && (tokens[2].size()<1 || tokens[2].size()>256)) {
          result_set.push_back("Wrong key or value");
          continue;
        }
        else {
          auto start = std::chrono::high_resolution_clock::now();
          cmdStatus = PUT(tokens[1],tokens[2],&result);
          auto stop = std::chrono::high_resolution_clock::now(); 
          auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
          time_required.push_back(time.count() * 1e-9);
        }
      }
      else if (tokens[0].compare("DEL") == 0) {
        if (tokens[1].size()<1 || tokens[1].size()>256) {
          result_set.push_back("Wrong key");
          continue;
        }
        else {
          auto start = std::chrono::high_resolution_clock::now();
          cmdStatus = DEL(tokens[1],&result);
          auto stop = std::chrono::high_resolution_clock::now(); 
          auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
          time_required.push_back(time.count() * 1e-9);
        }
      }
      else {
        result_set.push_back("Wrong command");
        continue;
      }
      //"Command Status    :"<<cmdStatus<<"   |   Result   :"<<result
      result_set.push_back("Return  Status    :"+std::to_string(cmdStatus)+"   |   Result   :"+result);
    } 

    for (int i=0; i<result_set.size(); i++) {
      std::cout << result_set[i] << "\n";
    }
    double min=INT32_MAX, max=0, sum=0;
    for (int i=0; i<time_required.size(); i++) {
      if (time_required[i] < min) {
        min = time_required[i];
      }
      if (time_required[i] > max) {
        max = time_required[i];
      }
      sum = sum + time_required[i];
    }
    double avg = sum/time_required.size();

    std::cout << "Min Time Required: " << min << "\n";
    std::cout << "Max Time Required: " << max << "\n";
    std::cout << "Avg Time Required: " << avg << "\n";

    MyReadFile.close();
  } 

  keyvaluestore::statusValue GET(std::string key, std::string *value) {

    ClientContext context;
    CompletionQueue cq;
    requestKey request;
    Status status;
    responseValue response;
    request.set_key(key);

    std::unique_ptr<ClientAsyncResponseReader<responseValue> > rpc(stub_->PrepareAsyncGET(&context, request, &cq));

    rpc->StartCall();
    rpc->Finish(&response, &status, (void*)1);

    void* got_tag;
    bool ok = false;
    GPR_ASSERT(cq.Next(&got_tag, &ok));
    GPR_ASSERT(got_tag == (void*)1);
    GPR_ASSERT(ok);
 
    *value = response.value();
    if (!status.ok()) {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      std::cout << "RPC failed";
    }
    return response.status();
  }

  keyvaluestore::statusValue DEL(std::string key , std::string * strStatus) {
    ClientContext context;
    CompletionQueue cq;
    requestKey request;
    Status status;
    responseValue response;
    std::string value;

    request.set_key(key);

    std::unique_ptr<ClientAsyncResponseReader<responseValue> > rpc(stub_->PrepareAsyncDEL(&context, request, &cq));

    rpc->StartCall();
    rpc->Finish(&response, &status, (void*)1);

    void* got_tag;
    bool ok = false;
    GPR_ASSERT(cq.Next(&got_tag, &ok));
    GPR_ASSERT(got_tag == (void*)1);
    GPR_ASSERT(ok);

    // std::cout<<response.status()<<std::endl;
    *strStatus = response.value();
    if (!status.ok()) {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      std::cout << "RPC failed";
    }
    return response.status();
  }

  keyvaluestore::statusValue PUT(std::string key, std::string value, std::string *strStatus) {
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    CompletionQueue cq;
    requestKeyValue request;
    Status status;
    responseStatus response;

    request.set_key(key);
    request.set_value(value);

    std::unique_ptr<ClientAsyncResponseReader<responseStatus> > rpc(stub_->PrepareAsyncPUT(&context, request, &cq));
    rpc->StartCall();
    rpc->Finish(&response, &status, (void*)1);

    void* got_tag;
    bool ok = false;
    GPR_ASSERT(cq.Next(&got_tag, &ok));
    GPR_ASSERT(got_tag == (void*)1);
    GPR_ASSERT(ok);

    *strStatus = "Inserted";
    if (!status.ok()) {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      std::cout << "RPC failed";
    }
    return response.status();
  }

 private:
  std::unique_ptr<storeManager::Stub> stub_;

};


int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint specified by
  // the argument "--target=" which is the only expected argument.
  // We indicate that the channel isn't authenticated (use of
  // InsecureChannelCredentials()).
  std::string target_str;
  std::string arg_str("--target");
  if (argc > 1) {
    std::string arg_val = argv[1];
    size_t start_pos = arg_val.find(arg_str);
    if (start_pos != std::string::npos) {
      start_pos += arg_str.size();
      if (arg_val[start_pos] == '=') {
        target_str = arg_val.substr(start_pos + 1);
      } else {
        std::cout << "The only correct argument syntax is --target="
                  << std::endl;
        return 0;
      }
    } else {
      std::cout << "The only acceptable argument is --target=" << std::endl;
      return 0;
    }
  } else {
    target_str = "localhost:50051";
  }
 
  configReader config;
  if(config.readConfigFile("../../config.in")==-1){
    std::cout<<"Cannot Read config.in file\n";
    return 0;
  }
  
  target_str = "localhost:"+std::to_string(config.getListeningPort());
  KeyValueStoreClient client(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));  
  std::string mode;

  while(1){

  std::cout << "Select the method of requests";  
  std::cout << "Choose one of the following. \n1 For Batch Mode\n2 For Interactive Mode\n3 To Exit Client\n Enter mode: ";
  std::cin  >> mode;
  if(mode.compare("3")==0)
        break;
  if (mode.compare("1")==0) {
    std::string filepath;
    std::cout << "Enter a file path: ";
    std::cin >> filepath;
    client.BatchMode(filepath);
  }
  else if (mode.compare("2")==0) {
    while(1) {
        std::string command, key, value,result;        
        keyvaluestore::statusValue cmdStatus;
        cmdStatus=keyvaluestore::statusValue::FAILURE;
        result="";
        std::cout << "Write command in UpperCase only(\nGET, \nPUT, \nDEL,\nEXIT(To Exit Interactive Mode)): ";
        std::cin >> command;
        if(command.compare("EXIT") ==0 ){
            std::cout<<"Exiting Interactive Mode..\n";
            break;
        }
        std::cout << "Write key: ";
        std::cin >> key;
        
        if (key.size() < 1 || key.size() > 256) {
            std::cout << "Wrong key\n";
            continue;
        } 
        if (command.compare("PUT") == 0) {
            std::cout << "Write value: ";
            std::cin >> value;
            if (value.size() < 1 || value.size() > 256) {
            std::cout << "Wrong value\n";
            continue;
            } 
            auto start = std::chrono::high_resolution_clock::now();
            cmdStatus  = client.PUT(key, value,&result);
            auto stop = std::chrono::high_resolution_clock::now(); 
            auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
            std::cout << "The time taken by the PUT operation: " << time.count() * 1e-9 << "\n";      
        }
        else if (command.compare("GET") == 0) {
            auto start = std::chrono::high_resolution_clock::now();
            cmdStatus  = client.GET(key, &result);
            auto stop = std::chrono::high_resolution_clock::now(); 
            auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
            std::cout << "The time taken by the GET operation: " << time.count() * 1e-9 << "\n";      
        }
        else if (command.compare("DEL") == 0) {
            auto start = std::chrono::high_resolution_clock::now();
            cmdStatus  = client.DEL(key,&result);
            auto stop = std::chrono::high_resolution_clock::now(); 
            auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
            std::cout << "The time taken by the DEL operation: " << time.count() * 1e-9 << "\n";      
        }
        else {
            std::cout << "Wrong command!!\n";
            continue;
        }
            std::cout << "Return    Status    :"<<cmdStatus<<"   |   Result   :"<<result<<std::endl;
        }
    }
    else {
        std::cout << "Wrong Mode";
    //    std::cin.clear();
    }
   }
 return 0;
}
