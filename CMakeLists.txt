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
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Code/Testing_Platform/certificates)

add_executable(Master_s_Thesis
        Code/Testing_Platform/Server/commonServerMethods.h
                Code/Testing_Platform/Server/CpuServerClass.h
                Code/Testing_Platform/Server/MainServer.c
                Code/Testing_Platform/Server/custom_datatype.h
                Code/Testing_Platform/Server/EncryptionServerClass.h
                Code/Testing_Platform/Server/NetworkingServerClass.h
                Code/Testing_Platform/Server/DiscoveryServerClass.h

  )
include_directories(Master_s_Thesis Code/Testing_Platform)
target_link_libraries(Master_s_Thesis open62541 ${open62541_LIBRARIES})

#Server Configuration
#Code/Testing/Server/commonServerMethods.h
#        Code/Testing/Server/CpuServerClass.h
#        Code/Testing/Server/MainServer.c
#        Code/Testing/Server/custom_datatype.h
#        Code/Testing/Server/EncryptionServerClass.h
#        Code/Testing/Server/NetworkingServerClass.h
#        Code/Testing/Server/DiscoveryServerClass.h


# Client Configuration
#                Code/Testing/Clients/CPU_Tests/multiple_clients_single_value_test.c
#                Code/Testing/Clients/CPU_Tests/multiple_client_multiple_value_test.c
#                Code/Testing/Clients/CPU_Tests/sorting_test.c
#                Code/Testing/Clients/CPU_Tests/filesize_test.c
#                Code/Testing/Clients/Encryption_Tests/encryption_test_basic128rsa15.c
#                Code/Testing/Clients/Encryption_Tests/encryption_test_basic256sha256.c
#                Code/Testing/Clients/CPU_Tests/call_per_second_test.c
#                Code/Testing/Clients/commonTestingMethods.h
#                Code/Testing/Clients/Multithreading_Tests/multithreading_test.c
#                Code/Testing/Clients/Networking_Tests/networking_test.c
#                Code/Testing/Clients/Discovery_Tests/find_servers_test.c
