# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.3)

# Define the project name, version, and description
project(libFLNL VERSION 1.0.0 DESCRIPTION "Fast Light Network Library")

# Add a static library target named 'libFLNL' composed of the following source files
add_library(libFLNL STATIC src/baseSocket.cpp src/client.cpp src/server.cpp)

include_directories(include)

# Compile 'main.cpp' into an executable named 'Server'
add_executable(Server src/main.cpp)

# Link the 'libFLNL' static library to the 'Server' executable
target_link_libraries(Server libFLNL)

# Compile 'mainClient.cpp' into an executable named 'Client'
add_executable(Client src/mainClient.cpp)

# Link the 'libFLNL' static library to the 'Client' executable
target_link_libraries(Client libFLNL)
