//
// Created by cgtybsr on 24.04.18.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../Testing_Platform/Client/open62541.h"

UA_Double randomArray[1000],sortedArray[1000];
UA_Client *client;
UA_Logger logger = UA_Log_Stdout;
UA_StatusCode retval;
// -Method to get millisecond resolution timestamp
struct timespec ts, ts2;
uint64_t get_milliseconds(){
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}
// -Method to get second resolution timestamp
uint64_t get_seconds(){
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts2);
    return ts2.tv_sec;
}


static void initializeArray(){
int i;
srand((unsigned int) time(NULL));
    for(i=0;i<1000;i++){
        randomArray[i]= (rand()%100);
    }
}

static void connectToServer(){
    client = UA_Client_new(UA_ClientConfig_default);
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://10.200.2.14:4840");
    if(retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        UA_LOG_FATAL(logger,UA_LOGCATEGORY_USERLAND,"Error creating Raw Client");
    }
}
static void sendArrayToServer(){
    __time_t before,after;
    before=get_milliseconds();
    retval = UA_Client_call(client,UA_NODEID_NUMERIC(0,UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(1,77777),1000,randomArray,1000,sortedArray);
}




int main(){


    initializeArray();
    connectToServer();

    return 0;
}