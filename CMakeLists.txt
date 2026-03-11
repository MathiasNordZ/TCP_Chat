cmake_minimum_required(VERSION 4.1)
project(TCP_Chat)

set(CMAKE_CXX_STANDARD 26)

include_directories(include)

add_executable(client src/client/client.cc)
add_executable(server src/server/server.cc)
