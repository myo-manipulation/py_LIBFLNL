# Compiling and Running the C++ Client-Server Example

This sample project consists of a simple C++ Client and a C++ Server that communicate through a pipeline. Below are instructions on how to compile and run both programs.

## Compile the Program with CMake

First, make sure you have the g++ compiler installed on your system. Then, follow these steps to compile the program using CMake:

```shell
# Open a terminal and navigate to the root directory of the project.
mkdir build
cd build

# Use CMake to generate the build files. Replace <path_to_source> with the actual path to the project's source code:
cmake ..

# Build the project using Make:
make
```

## Run the Server and Client

```shell
# Run the server first
./Server 
# Then run the client
./Client
```

## Use pipeline to Replace the Client
If you wish to use a Python script instead of the C++ Client to communicate with the Server, you can use pipeline.py. 

**Note: This is a quite dirty fix.**

Here's how to use pipeline.py:

```shell
# Install the required Python modules:
pip install subprocess

# Open a terminal and navigate to the root directory of the project.
# Run the `pipeline.py` script:
python pipeline.py
```