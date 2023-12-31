// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: testGrpc.proto
#ifndef GRPC_testGrpc_2eproto__INCLUDED
#define GRPC_testGrpc_2eproto__INCLUDED

#include "testGrpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace testGrpc {

class testGrpcAsync final {
 public:
  static constexpr char const* service_full_name() {
    return "testGrpc.testGrpcAsync";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status hye(::grpc::ClientContext* context, const ::testGrpc::requesthello& request, ::testGrpc::response* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::testGrpc::response>> Asynchye(::grpc::ClientContext* context, const ::testGrpc::requesthello& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::testGrpc::response>>(AsynchyeRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::testGrpc::response>> PrepareAsynchye(::grpc::ClientContext* context, const ::testGrpc::requesthello& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::testGrpc::response>>(PrepareAsynchyeRaw(context, request, cq));
    }
    virtual ::grpc::Status bye(::grpc::ClientContext* context, const ::testGrpc::requestbye& request, ::testGrpc::response* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::testGrpc::response>> Asyncbye(::grpc::ClientContext* context, const ::testGrpc::requestbye& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::testGrpc::response>>(AsyncbyeRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::testGrpc::response>> PrepareAsyncbye(::grpc::ClientContext* context, const ::testGrpc::requestbye& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::testGrpc::response>>(PrepareAsyncbyeRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void hye(::grpc::ClientContext* context, const ::testGrpc::requesthello* request, ::testGrpc::response* response, std::function<void(::grpc::Status)>) = 0;
      virtual void hye(::grpc::ClientContext* context, const ::testGrpc::requesthello* request, ::testGrpc::response* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      virtual void bye(::grpc::ClientContext* context, const ::testGrpc::requestbye* request, ::testGrpc::response* response, std::function<void(::grpc::Status)>) = 0;
      virtual void bye(::grpc::ClientContext* context, const ::testGrpc::requestbye* request, ::testGrpc::response* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::testGrpc::response>* AsynchyeRaw(::grpc::ClientContext* context, const ::testGrpc::requesthello& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::testGrpc::response>* PrepareAsynchyeRaw(::grpc::ClientContext* context, const ::testGrpc::requesthello& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::testGrpc::response>* AsyncbyeRaw(::grpc::ClientContext* context, const ::testGrpc::requestbye& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::testGrpc::response>* PrepareAsyncbyeRaw(::grpc::ClientContext* context, const ::testGrpc::requestbye& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status hye(::grpc::ClientContext* context, const ::testGrpc::requesthello& request, ::testGrpc::response* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::testGrpc::response>> Asynchye(::grpc::ClientContext* context, const ::testGrpc::requesthello& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::testGrpc::response>>(AsynchyeRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::testGrpc::response>> PrepareAsynchye(::grpc::ClientContext* context, const ::testGrpc::requesthello& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::testGrpc::response>>(PrepareAsynchyeRaw(context, request, cq));
    }
    ::grpc::Status bye(::grpc::ClientContext* context, const ::testGrpc::requestbye& request, ::testGrpc::response* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::testGrpc::response>> Asyncbye(::grpc::ClientContext* context, const ::testGrpc::requestbye& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::testGrpc::response>>(AsyncbyeRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::testGrpc::response>> PrepareAsyncbye(::grpc::ClientContext* context, const ::testGrpc::requestbye& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::testGrpc::response>>(PrepareAsyncbyeRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void hye(::grpc::ClientContext* context, const ::testGrpc::requesthello* request, ::testGrpc::response* response, std::function<void(::grpc::Status)>) override;
      void hye(::grpc::ClientContext* context, const ::testGrpc::requesthello* request, ::testGrpc::response* response, ::grpc::ClientUnaryReactor* reactor) override;
      void bye(::grpc::ClientContext* context, const ::testGrpc::requestbye* request, ::testGrpc::response* response, std::function<void(::grpc::Status)>) override;
      void bye(::grpc::ClientContext* context, const ::testGrpc::requestbye* request, ::testGrpc::response* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::testGrpc::response>* AsynchyeRaw(::grpc::ClientContext* context, const ::testGrpc::requesthello& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::testGrpc::response>* PrepareAsynchyeRaw(::grpc::ClientContext* context, const ::testGrpc::requesthello& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::testGrpc::response>* AsyncbyeRaw(::grpc::ClientContext* context, const ::testGrpc::requestbye& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::testGrpc::response>* PrepareAsyncbyeRaw(::grpc::ClientContext* context, const ::testGrpc::requestbye& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_hye_;
    const ::grpc::internal::RpcMethod rpcmethod_bye_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status hye(::grpc::ServerContext* context, const ::testGrpc::requesthello* request, ::testGrpc::response* response);
    virtual ::grpc::Status bye(::grpc::ServerContext* context, const ::testGrpc::requestbye* request, ::testGrpc::response* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_hye : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_hye() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_hye() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status hye(::grpc::ServerContext* /*context*/, const ::testGrpc::requesthello* /*request*/, ::testGrpc::response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requesthye(::grpc::ServerContext* context, ::testGrpc::requesthello* request, ::grpc::ServerAsyncResponseWriter< ::testGrpc::response>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_bye : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_bye() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_bye() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status bye(::grpc::ServerContext* /*context*/, const ::testGrpc::requestbye* /*request*/, ::testGrpc::response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestbye(::grpc::ServerContext* context, ::testGrpc::requestbye* request, ::grpc::ServerAsyncResponseWriter< ::testGrpc::response>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_hye<WithAsyncMethod_bye<Service > > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_hye : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_hye() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::testGrpc::requesthello, ::testGrpc::response>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::testGrpc::requesthello* request, ::testGrpc::response* response) { return this->hye(context, request, response); }));}
    void SetMessageAllocatorFor_hye(
        ::grpc::MessageAllocator< ::testGrpc::requesthello, ::testGrpc::response>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::testGrpc::requesthello, ::testGrpc::response>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_hye() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status hye(::grpc::ServerContext* /*context*/, const ::testGrpc::requesthello* /*request*/, ::testGrpc::response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* hye(
      ::grpc::CallbackServerContext* /*context*/, const ::testGrpc::requesthello* /*request*/, ::testGrpc::response* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_bye : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_bye() {
      ::grpc::Service::MarkMethodCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::testGrpc::requestbye, ::testGrpc::response>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::testGrpc::requestbye* request, ::testGrpc::response* response) { return this->bye(context, request, response); }));}
    void SetMessageAllocatorFor_bye(
        ::grpc::MessageAllocator< ::testGrpc::requestbye, ::testGrpc::response>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(1);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::testGrpc::requestbye, ::testGrpc::response>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_bye() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status bye(::grpc::ServerContext* /*context*/, const ::testGrpc::requestbye* /*request*/, ::testGrpc::response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* bye(
      ::grpc::CallbackServerContext* /*context*/, const ::testGrpc::requestbye* /*request*/, ::testGrpc::response* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_hye<WithCallbackMethod_bye<Service > > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_hye : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_hye() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_hye() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status hye(::grpc::ServerContext* /*context*/, const ::testGrpc::requesthello* /*request*/, ::testGrpc::response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_bye : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_bye() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_bye() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status bye(::grpc::ServerContext* /*context*/, const ::testGrpc::requestbye* /*request*/, ::testGrpc::response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_hye : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_hye() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_hye() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status hye(::grpc::ServerContext* /*context*/, const ::testGrpc::requesthello* /*request*/, ::testGrpc::response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requesthye(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_bye : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_bye() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_bye() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status bye(::grpc::ServerContext* /*context*/, const ::testGrpc::requestbye* /*request*/, ::testGrpc::response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestbye(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_hye : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_hye() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->hye(context, request, response); }));
    }
    ~WithRawCallbackMethod_hye() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status hye(::grpc::ServerContext* /*context*/, const ::testGrpc::requesthello* /*request*/, ::testGrpc::response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* hye(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_bye : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_bye() {
      ::grpc::Service::MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->bye(context, request, response); }));
    }
    ~WithRawCallbackMethod_bye() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status bye(::grpc::ServerContext* /*context*/, const ::testGrpc::requestbye* /*request*/, ::testGrpc::response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* bye(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_hye : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_hye() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::testGrpc::requesthello, ::testGrpc::response>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::testGrpc::requesthello, ::testGrpc::response>* streamer) {
                       return this->Streamedhye(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_hye() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status hye(::grpc::ServerContext* /*context*/, const ::testGrpc::requesthello* /*request*/, ::testGrpc::response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status Streamedhye(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::testGrpc::requesthello,::testGrpc::response>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_bye : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_bye() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler<
          ::testGrpc::requestbye, ::testGrpc::response>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::testGrpc::requestbye, ::testGrpc::response>* streamer) {
                       return this->Streamedbye(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_bye() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status bye(::grpc::ServerContext* /*context*/, const ::testGrpc::requestbye* /*request*/, ::testGrpc::response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status Streamedbye(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::testGrpc::requestbye,::testGrpc::response>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_hye<WithStreamedUnaryMethod_bye<Service > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_hye<WithStreamedUnaryMethod_bye<Service > > StreamedService;
};

}  // namespace testGrpc


#endif  // GRPC_testGrpc_2eproto__INCLUDED
