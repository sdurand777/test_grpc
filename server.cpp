
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "./proto_files/myproto.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using myproto::MyService;
using myproto::HelloRequest;
using myproto::HelloReply;

// Implémentation du service
class MyServiceImpl final : public MyService::Service 
{
    Status SayHello(ServerContext* context, const HelloRequest* request, HelloReply* reply) override {
        std::string prefix("Hello ");
        reply->set_message(prefix + request->name());
        return Status::OK;
    }
};


// run server method
void RunServer() 
{
    std::string server_address("0.0.0.0:50051");
    MyServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}


// main app to run serveur
int main(int argc, char** argv) 
{
    RunServer();
    return 0;
}
