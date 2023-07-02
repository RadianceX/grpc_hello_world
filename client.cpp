#include <grpc++/grpc++.h>

#include <iostream>
#include <memory>
#include <optional>
#include <string>

#include "helloworld.grpc.pb.h"

class GreeterClient {
public:
    GreeterClient(std::shared_ptr<grpc::Channel> channel)
        : stub_(helloworld::HelloService::NewStub(channel)) {
    }
    std::optional<std::string> SayHello(const std::string& user) {
        helloworld::HelloRequest request;
        request.set_name(user);

        helloworld::HelloResponse response;
        grpc::ClientContext context;
        grpc::Status status = stub_->SayHelloWorld(&context, request, &response);

        if (!status.ok()) {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return std::nullopt;
        }

        return response.message();
    }

private:
    std::unique_ptr<helloworld::HelloService::Stub> stub_;
};

void InterativeGRPC() {
    GreeterClient greeter(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    while (true) {
        std::cout << "Please enter your user name:" << std::endl;
        std::string user;
        std::getline(std::cin, user);

        std::optional<std::string> response = greeter.SayHello(user);
        std::cout << "Server returned: " << response.value_or("gRPC failed") << std::endl;
    }
}

int main(int argc, char** argv) {
    InterativeGRPC();
    return 0;
}