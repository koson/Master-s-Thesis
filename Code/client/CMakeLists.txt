cmake_minimum_required(VERSION 3.8)
project(client)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(pub publisher.c open62541.c)
add_executable(sub subscriber.c open62541.c)
add_executable(methossd method.c open62541.c)