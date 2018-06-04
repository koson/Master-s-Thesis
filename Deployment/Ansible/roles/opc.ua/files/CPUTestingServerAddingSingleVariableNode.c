//
// Created by cgtybsr on 25.05.18.
//t
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include "open62541.h"
#define _POSIX_C_SOURCE 199309L


/**  General Methods*/
__time_t before, after;
struct timespec start, end;



UA_Boolean running = true;
static void stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}

static const UA_NodeId baseDataVariableType = {0, UA_NODEIDTYPE_NUMERIC, {UA_NS0ID_BASEDATAVARIABLETYPE}};
static void
addNode(UA_Server *server, UA_Int32 id) {


    UA_VariableAttributes myVar = UA_VariableAttributes_default;
    myVar.description = UA_LOCALIZEDTEXT("en-US", "the answer");
    myVar.displayName = UA_LOCALIZEDTEXT("en-US", "the answer");
    myVar.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    myVar.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    myVar.valueRank = -1;
    UA_Int32 myInteger = 42;
    UA_Variant_setScalarCopy(&myVar.value, &myInteger, &UA_TYPES[UA_TYPES_INT32]);
    const UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME(1, "the answer");
    const UA_NodeId myIntegerNodeId = UA_NODEID_NUMERIC(1, id);
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_Server_addVariableNode(server, myIntegerNodeId, parentNodeId, parentReferenceNodeId,
                              myIntegerName, baseDataVariableType, myVar, NULL, NULL);
}

static void deleteNode(UA_Server *server,UA_Int32 id)
{
    const UA_NodeId myIntegerNodeId = UA_NODEID_NUMERIC(1, id);
    UA_Server_deleteNode(server,myIntegerNodeId,true);

}


static void callAddNode(UA_Server *server,int j){

    for(int i = 1; i <= j; i++){
        addNode(server, i);
    }
}
static void callDeleteNode(UA_Server *server,int j){

    for(int i=1;i<=j;i++){

        deleteNode(server,i);

    }
}



int main(void) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    UA_ServerConfig *config = UA_ServerConfig_new_default();
    UA_Server *server = UA_Server_new(config);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Starting adding nodes");

    for (int i=1;i<1000000;i*=10){
        clock_gettime(CLOCK_MONOTONIC, &start);
        callAddNode(server,i);
        clock_gettime(CLOCK_MONOTONIC, &end);
        printf("Adding %d nodes took about %.5f seconds\n",i,
               ((double)end.tv_sec + 1.0e-9*end.tv_nsec) -
               ((double)start.tv_sec + 1.0e-9*start.tv_nsec));


        clock_gettime(CLOCK_MONOTONIC, &start);
       callDeleteNode(server,i);
        clock_gettime(CLOCK_MONOTONIC, &end);
        printf("Deleting %d nodes took about %.5f seconds\n",i,
               ((double)end.tv_sec + 1.0e-9*end.tv_nsec) -
               ((double)start.tv_sec + 1.0e-9*start.tv_nsec));
    }



    long long int elapsed_time = (long long int) (after - before);
    printf("%lld",elapsed_time);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "End of adding nodes");
    UA_StatusCode retval = UA_Server_run(server, false);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    return (int)retval;
}
