// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: keyvaluestore.proto

#include "keyvaluestore.pb.h"
#include "keyvaluestore.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace keyvaluestore {

static const char* storeManager_method_names[] = {
  "/keyvaluestore.storeManager/GET",
  "/keyvaluestore.storeManager/DEL",
  "/keyvaluestore.storeManager/PUT",
};

std::unique_ptr< storeManager::Stub> storeManager::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< storeManager::Stub> stub(new storeManager::Stub(channel, options));
  return stub;
}

storeManager::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_GET_(storeManager_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_DEL_(storeManager_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_PUT_(storeManager_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status storeManager::Stub::GET(::grpc::ClientContext* context, const ::keyvaluestore::requestKey& request, ::keyvaluestore::responseValue* response) {
  return ::grpc::internal::BlockingUnaryCall< ::keyvaluestore::requestKey, ::keyvaluestore::responseValue, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GET_, context, request, response);
}

void storeManager::Stub::async::GET(::grpc::ClientContext* context, const ::keyvaluestore::requestKey* request, ::keyvaluestore::responseValue* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::keyvaluestore::requestKey, ::keyvaluestore::responseValue, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GET_, context, request, response, std::move(f));
}

void storeManager::Stub::async::GET(::grpc::ClientContext* context, const ::keyvaluestore::requestKey* request, ::keyvaluestore::responseValue* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GET_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::keyvaluestore::responseValue>* storeManager::Stub::PrepareAsyncGETRaw(::grpc::ClientContext* context, const ::keyvaluestore::requestKey& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::keyvaluestore::responseValue, ::keyvaluestore::requestKey, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GET_, context, request);
}

::grpc::ClientAsyncResponseReader< ::keyvaluestore::responseValue>* storeManager::Stub::AsyncGETRaw(::grpc::ClientContext* context, const ::keyvaluestore::requestKey& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGETRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status storeManager::Stub::DEL(::grpc::ClientContext* context, const ::keyvaluestore::requestKey& request, ::keyvaluestore::responseValue* response) {
  return ::grpc::internal::BlockingUnaryCall< ::keyvaluestore::requestKey, ::keyvaluestore::responseValue, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_DEL_, context, request, response);
}

void storeManager::Stub::async::DEL(::grpc::ClientContext* context, const ::keyvaluestore::requestKey* request, ::keyvaluestore::responseValue* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::keyvaluestore::requestKey, ::keyvaluestore::responseValue, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_DEL_, context, request, response, std::move(f));
}

void storeManager::Stub::async::DEL(::grpc::ClientContext* context, const ::keyvaluestore::requestKey* request, ::keyvaluestore::responseValue* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_DEL_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::keyvaluestore::responseValue>* storeManager::Stub::PrepareAsyncDELRaw(::grpc::ClientContext* context, const ::keyvaluestore::requestKey& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::keyvaluestore::responseValue, ::keyvaluestore::requestKey, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_DEL_, context, request);
}

::grpc::ClientAsyncResponseReader< ::keyvaluestore::responseValue>* storeManager::Stub::AsyncDELRaw(::grpc::ClientContext* context, const ::keyvaluestore::requestKey& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncDELRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status storeManager::Stub::PUT(::grpc::ClientContext* context, const ::keyvaluestore::requestKeyValue& request, ::keyvaluestore::responseStatus* response) {
  return ::grpc::internal::BlockingUnaryCall< ::keyvaluestore::requestKeyValue, ::keyvaluestore::responseStatus, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_PUT_, context, request, response);
}

void storeManager::Stub::async::PUT(::grpc::ClientContext* context, const ::keyvaluestore::requestKeyValue* request, ::keyvaluestore::responseStatus* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::keyvaluestore::requestKeyValue, ::keyvaluestore::responseStatus, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_PUT_, context, request, response, std::move(f));
}

void storeManager::Stub::async::PUT(::grpc::ClientContext* context, const ::keyvaluestore::requestKeyValue* request, ::keyvaluestore::responseStatus* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_PUT_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::keyvaluestore::responseStatus>* storeManager::Stub::PrepareAsyncPUTRaw(::grpc::ClientContext* context, const ::keyvaluestore::requestKeyValue& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::keyvaluestore::responseStatus, ::keyvaluestore::requestKeyValue, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_PUT_, context, request);
}

::grpc::ClientAsyncResponseReader< ::keyvaluestore::responseStatus>* storeManager::Stub::AsyncPUTRaw(::grpc::ClientContext* context, const ::keyvaluestore::requestKeyValue& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncPUTRaw(context, request, cq);
  result->StartCall();
  return result;
}

storeManager::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      storeManager_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< storeManager::Service, ::keyvaluestore::requestKey, ::keyvaluestore::responseValue, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](storeManager::Service* service,
             ::grpc::ServerContext* ctx,
             const ::keyvaluestore::requestKey* req,
             ::keyvaluestore::responseValue* resp) {
               return service->GET(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      storeManager_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< storeManager::Service, ::keyvaluestore::requestKey, ::keyvaluestore::responseValue, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](storeManager::Service* service,
             ::grpc::ServerContext* ctx,
             const ::keyvaluestore::requestKey* req,
             ::keyvaluestore::responseValue* resp) {
               return service->DEL(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      storeManager_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< storeManager::Service, ::keyvaluestore::requestKeyValue, ::keyvaluestore::responseStatus, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](storeManager::Service* service,
             ::grpc::ServerContext* ctx,
             const ::keyvaluestore::requestKeyValue* req,
             ::keyvaluestore::responseStatus* resp) {
               return service->PUT(ctx, req, resp);
             }, this)));
}

storeManager::Service::~Service() {
}

::grpc::Status storeManager::Service::GET(::grpc::ServerContext* context, const ::keyvaluestore::requestKey* request, ::keyvaluestore::responseValue* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status storeManager::Service::DEL(::grpc::ServerContext* context, const ::keyvaluestore::requestKey* request, ::keyvaluestore::responseValue* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status storeManager::Service::PUT(::grpc::ServerContext* context, const ::keyvaluestore::requestKeyValue* request, ::keyvaluestore::responseStatus* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace keyvaluestore

