#include <grpc++/grpc++.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "helloworld.grpc.pb.h"

class GreeterServiceImpl final : public helloworld::HelloService::Service {
    grpc::Status SayHelloWorld(grpc::ServerContext* context, const helloworld::HelloRequest* request,
                               helloworld::HelloResponse* response) override {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        response->set_message("Hello " + request->name() + "!");
        return grpc::Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    GreeterServiceImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "[Server] Listening on " << server_address << std::endl;

    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}