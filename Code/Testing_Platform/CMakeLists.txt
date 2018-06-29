cmake_minimum_required(VERSION 2.8.4)

set(PROJECT_NAME OPC_UA_Testing_Platform)

# Define your project and language
project(${PROJECT_NAME})



set(CMAKE_CXX_STANDARD 11)
set(UA_ENABLE_DISCOVERY_SEMAPHORE OFF CACHE BOOL "" FORCE)
set(UA_ENABLE_SUBSCRIPTIONS ON)
set(UA_ENABLE_DISCOVERY ON)
set(UA_ENABLE_ENCRYPTION ON)
set(UA_ENABLE_STATUSCODE_DESCRIPTIONS ON)
set(UA_ENABLE_TYPENAMES ON)
set(UA_ENABLE_AMALGAMATION ON CACHE BOOL "" FORCE)
set(UA_LOGLEVEL 300)
set(UA_NODESET_ENCODE_BINARY_SIZE 1024)

add_subdirectory(open62541)
#option(WIFI_Name "Wifi Name where the controller should log in")
#option(WIFI_PWD "Wifi password where the controller should log in")
#if(NOT WIFI_SSID OR NOT WIFI_PWD)
#    MESSAGE(FATAL_ERROR "You need to define WIFI_SSID and WIFI_PWD using cmake options")
#endif()
#
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY Testing_Platform/certificates)

add_executable(Master_s_Thesis
                ClientSide/headers/commonClientMethods.h
                ClientSide/headers/CPU_Test_Client_Class.h
                ClientSide/headers/Discovery_Test_Client_Class.h
                ClientSide/headers/Encryption_Test_Client_Class.h
                ClientSide/headers/Networking_Test_Client_Class.h
                ClientSide/MainClient.c


        )
#include_directories(Master_s_Thesis Code/Testing_Platform)
target_link_libraries(Master_s_Thesis open62541 ${open62541_LIBRARIES})

#Server Configuration
#        Code/Testing_Platform/ServerSide/headers/commonServerMethods.h
#        Code/Testing_Platform/ServerSide/headers/CpuServerClass.h
#        Code/Testing_Platform/ServerSide/MainServer.c
#        Code/Testing_Platform/ServerSide/headers/custom_datatype.h
#        Code/Testing_Platform/ServerSide/headers/EncryptionServerClass.h
#        Code/Testing_Platform/ServerSide/headers/NetworkingServerClass.h
#        Code/Testing_Platform/ServerSide/headers/DiscoveryServerClass.h


# Client Configuration
#                        Code/Testing_Platform/ClientSide/headers/commonClientMethods.h
#        Code/Testing_Platform/ClientSide/headers/CPU_Test_Client_Class.h
#        Code/Testing_Platform/ClientSide/headers/Discovery_Test_Client_Class.h
#        Code/Testing_Platform/ClientSide/headers/Encryption_Test_Client_Class.h
#        Code/Testing_Platform/ClientSide/headers/Networking_Test_Client_Class.h
#        Code/Testing_Platform/ClientSide/MainClient.c














#cmake_minimum_required(VERSION 2.8.11)
#
#set(PROJECT_NAME OPC_UA_Testing_Platform)
#
## Define your project and language
#project(${PROJECT_NAME})
#
#
#
#set(CMAKE_CXX_STANDARD 11)
#set(UA_ENABLE_DISCOVERY_SEMAPHORE OFF CACHE BOOL "" FORCE)
#set(UA_ENABLE_SUBSCRIPTIONS ON)
#set(UA_ENABLE_DISCOVERY ON)
#set(UA_ENABLE_ENCRYPTION ON)
#set(UA_ENABLE_STATUSCODE_DESCRIPTIONS ON)
#set(UA_ENABLE_TYPENAMES ON)
#set(UA_ENABLE_AMALGAMATION ON CACHE BOOL "" FORCE)
#set(UA_LOGLEVEL 300)
#set(UA_NODESET_ENCODE_BINARY_SIZE 1024)
#
#
#add_subdirectory(open62541)
#
#
#set(${PROJECT_NAME}_ClientSideHeaders Code/Testing_Platform/ClientSide/headers/open62541.h
#        Code/Testing_Platform/ClientSide/headers/commonClientMethods.h
#        Code/Testing_Platform/ClientSide/headers/CPU_Test_Client_Class.h
#        Code/Testing_Platform/ClientSide/headers/Discovery_Test_Client_Class.h
#        Code/Testing_Platform/ClientSide/headers/Encryption_Test_Client_Class.h
#        Code/Testing_Platform/ClientSide/headers/Networking_Test_Client_Class.h
#        )
#set(${PROJECT_NAME}_ServerSideHeaders
#        Code/Testing_Platform/ServerSide/headers/CpuServerClass.h
#        Code/Testing_Platform/ServerSide/headers/NetworkingServerClass.h
#        Code/Testing_Platform/ServerSide/headers/DiscoveryServerClass.h
#        Code/Testing_Platform/ServerSide/headers/EncryptionServerClass.h
#
#        )
#
#
#
##option(WIFI_Name "Wifi Name where the controller should log in")
##option(WIFI_PWD "Wifi password where the controller should log in")
##if(NOT WIFI_SSID OR NOT WIFI_PWD)
##    MESSAGE(FATAL_ERROR "You need to define WIFI_SSID and WIFI_PWD using cmake options")
##endif()
##
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Code/Testing_Platform/certificates)
#include_directories(Master_s_Thesis Code/Testing_Platform)
#
#
#
#add_executable(${PROJECT_NAME}
#        Code/Testing_Platform/ClientSide/MainClient.c
#)
#
#
#
#target_link_libraries(open62541 ${open62541_LIBRARIES})
#
##Server Configuration
##include_directories(Code/Testing_Platform/ServerSide/commonServerMethods.h
##        Code/Testing_Platform/ServerSide/commonServerMethods.h
##        Code/Testing_Platform/ServerSide/CpuServerClass.h
##        Code/Testing_Platform/ServerSide/custom_datatype.h
##        Code/Testing_Platform/ServerSide/EncryptionServerClass.h
##        Code/Testing_Platform/ServerSide/NetworkingServerClass.h
##        Code/Testing_Platform/ServerSide/DiscoveryServerClass.h)
##
##
##add_executable(${PROJECT_NAME}
##        Code/Testing_Platform/ServerSide/MainServer.c
##        )
#
## Client Configuration
#
#
#
#
#
##        Code/Testing_Platform/Client/commonTestingMethods.h
##        Code/Testing_Platform/Client/CPU_Test_Client_Class.h
##        Code/Testing_Platform/Client/MainClient.c
##        Code/Testing_Platform/Client/Discovery_Test_Client_Class.h
##        Code/Testing_Platform/Client/Encryption_Test_Client_Class.h
##        Code/Testing_Platform/Client/Networking_Test_Client_Class.h
