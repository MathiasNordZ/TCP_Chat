cmake_minimum_required(VERSION 4.0.2)
project(TCP_Chat)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(client src/client/client.cc)
add_executable(server src/server/server.cc
        src/server/server.h)
