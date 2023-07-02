# gRPC hello world

This is a minimalistic hello world code example that uses gRPC library to setup communication between server and client

# Prerequites
 - Protobuf 3.21.12
 - gRPC 1.51.1
 - CMake 3.24 or later

# Usage
 - run server `./build/hello-world-grpc-server`
 - run client `./build/hello-world-grpc-client`

# Notes
I recommend using vcpkg to install all required libraries, though it is not mandatory.
See vcpkg official website for install instructions https://vcpkg.io/en/
You can install prerequisites with the following commands
 - `vcpkg install protobuf`
 - `vcpkg install grpc`
 - `vcpkg integrate install`

Also may need to tweak your VSCode setting.json with the following lines.
This will help CMake to find Protobuf and gRPC.
```
    "cmake.configureSettings": {
        "CMAKE_TOOLCHAIN_FILE": "~/vcpkg/scripts/buildsystems/vcpkg.cmake"
    },
```

I'm not part of gRPC, Protobuf, and vcpkg team and am not related to them in any way