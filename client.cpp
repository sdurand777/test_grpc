
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "./proto_files/myproto.grpc.pb.h"
#include <thread>  // Pour std::this_thread::sleep_for

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using myproto::MyService;
using myproto::HelloRequest;
using myproto::HelloReply;



class MyServiceClient 
{
public:
    MyServiceClient(std::shared_ptr<Channel> channel) : stub_(MyService::NewStub(channel)) {}

    std::string SayHello(const std::string& name) {
        HelloRequest request;
        request.set_name(name);

        HelloReply reply;
        ClientContext context;

        Status status = stub_->SayHello(&context, request, &reply);

        if (status.ok()) {
            return reply.message();
        } else {
            std::cout << "RPC failed" << std::endl;
            return "RPC failed";
        }
    }

private:
    std::unique_ptr<MyService::Stub> stub_;
};



// main app to run client
int main(int argc, char** argv) 
{
    MyServiceClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    std::string name;

    // Boucle pour faire des requêtes toutes les 1 seconde
    while (true) {
        // Demander à l'utilisateur de saisir un nouveau message
        std::cout << "Entrez un nom (ou tapez 'quit' pour sortir) : ";
        std::getline(std::cin, name);

        // Condition pour sortir de la boucle
        if (name == "quit") {
            break;
        }

        // Envoyer la requête au serveur
        std::string reply = client.SayHello(name);
        std::cout << "Client received: " << reply << std::endl;

        // Temporisation de 1 seconde
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }


    return 0;
}
