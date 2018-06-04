//
// Created by cgtybsr on 03.06.18.
//

#include "CpuServerClass.h"
#include "NetworkingServerClass.h"
#include "EncryptionServerClass.h"
#include <stdlib.h>
#include <string.h>




UA_ServerConfig *config;
UA_Server *server;


void printMemoryUsage(){



}

void printCurrentTime(){



}
void setupTime(){

}

void setupWifi(){



}

void setupServer(char *string) {
    setupTime();
    setupWifi();

    if(strcmp("None",string) ==0){
        config = UA_ServerConfig_new_default();
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "No Encryption");
        server = UA_Server_new(config);
    }
    if (strcmp("128rsa15",string) == 0){
        config = startEncryptionConfigurationBasic128rsa15();
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "128rsa15 Encryption");
        server = UA_Server_new(config);
    }
    if(strcmp("256sha256",string) == 0){
        config = startEncryptionConfigurationBasic256sha256();
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "256sha256 Encryption");
        server = UA_Server_new(config);

    }


    UA_DataType type = PointType;
    config->customDataTypes = &type;
    config->customDataTypesSize = 1;



    //CPU Server
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Starting CPU Tests");
    startAddingSingleVariableNodeTest(server,10000);
    startAddingArrayNodeTest(server,10000);
    multipleCustomObjectMethod(server);
    writeVariableMethod(server);
    singleValueMethod(server);
    multipleValueMethod(server);
    sortingArrayTest(server);
    UA_StatusCode retvalNone = UA_Server_run(server, &running);
    //Networking Tests
            echoMethod(server);
            ackMethod(server);
            updateCurrentTime(server);


    if (retvalNone != UA_STATUSCODE_GOOD) {
        printf("Creating OPC UA Server failed with code: ");
        printf(UA_StatusCode_name(retvalNone));

    }


    printf("OPC UA initialized");

    UA_Server_delete(server);
    UA_ServerConfig_delete(config);



}

int main(int argc,char **argv){
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    //192.168.178.59

    if(argc < 2) {
        UA_LOG_FATAL(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                     "Missing arguments. Arguments are "
                     "Server Encryption Type : None,128rsa15,256sha256");
        return 1;
    }
    char* input = argv[1];


    setupServer(input);


}
