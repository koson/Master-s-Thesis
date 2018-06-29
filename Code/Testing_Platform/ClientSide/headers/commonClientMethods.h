//
// Created by cgtybsr on 04.06.18.
//

#ifndef MASTER_S_THESIS_COMMONTESTINGMETHODS_H
#define MASTER_S_THESIS_COMMONTESTINGMETHODS_H

#include "open62541.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#define CONNECTION_STRING "opc.tcp://10.200.2.14:4840"

__time_t before, after;
UA_NodeId nodeId,parentNodeId,methodId,objectId;
UA_QualifiedName qualifiedName;
UA_Client *client;
UA_Logger logger = UA_Log_Stdout;
UA_Variant *output;
size_t outputSize;
UA_StatusCode  statusCode;
struct timespec timeSpec;

uint64_t get_milliseconds(){
    clock_gettime(CLOCK_MONOTONIC_RAW, &timeSpec);
    return timeSpec.tv_sec * 1000000 + timeSpec.tv_nsec / 1000;
}
// -Method to get second resolution timestamp
uint64_t get_seconds(){
    clock_gettime(CLOCK_MONOTONIC_RAW, &timeSpec);
    return timeSpec.tv_sec;
}

static void printTimeDifference(uint64_t start,uint64_t finish){
    printf("Process took about %.5f seconds\n",
           ((double)start) -((double)finish));
}
static UA_StatusCode initializeConnection(){
    client = UA_Client_new(UA_ClientConfig_default);
    UA_StatusCode retval = UA_Client_connect(client, CONNECTION_STRING);
    if(retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        UA_LOG_FATAL(logger,UA_LOGCATEGORY_USERLAND,"Error creating Raw Client");
        return retval;
    }

}


static UA_INLINE UA_ByteString
loadFile(const char *const path) {
    UA_ByteString fileContents = UA_STRING_NULL;

    /* Open the file */
    FILE *fp = fopen(path, "rb");
    if(!fp) {
        errno = 0; /* We read errno also from the tcp layer... */
        return fileContents;
    }

    /* Get the file length, allocate the data and read */
    fseek(fp, 0, SEEK_END);
    fileContents.length = (size_t)ftell(fp);
    fileContents.data = (UA_Byte *)UA_malloc(fileContents.length * sizeof(UA_Byte));
    if(fileContents.data) {
        fseek(fp, 0, SEEK_SET);
        size_t read = fread(fileContents.data, sizeof(UA_Byte), fileContents.length, fp);
        if(read != fileContents.length)
            UA_ByteString_deleteMembers(&fileContents);
    } else {
        fileContents.length = 0;
    }
    fclose(fp);

    return fileContents;
}
#endif //MASTER_S_THESIS_COMMONTESTINGMETHODS_H
