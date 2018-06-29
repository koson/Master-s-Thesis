//
// Created by cgtybsr on 03.05.18.
//

#include <stdio.h>
#include "../Testing_Platform/Clients/commonTestingMethods.h"
#include "../Testing_Platform/Clients/open62541.h"



static void perform_multiple_value_method_call(UA_Int32 id){
    UA_Client *client = UA_Client_new(UA_ClientConfig_default);
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://10.200.2.14:4840");
    UA_Variant *output;
    size_t outputSize;

    if(retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Could not connect");
        return;
    }

    nodeId = UA_NODEID_STRING(1,"multiple_value_node");
    parentNodeId =  UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    objectId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);


//    printf("For Client %d getting took about %.5f seconds\n",id,
//           ((double)end.tv_sec + 1.0e-9*end.tv_nsec) -
//           ((double)start.tv_sec + 1.0e-9*start.tv_nsec));

    UA_Variant input;
    UA_Variant_init(&input);
    UA_Variant value;
    UA_Variant_init(&value);
    methodId = UA_NODEID_STRING(1,"multiple_value_method");
    objectId =  UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);


//    clock_gettime(CLOCK_MONOTONIC, &start);
    uint64_t  start = get_milliseconds();
    UA_Client_call(client,objectId,methodId,0,NULL,&outputSize,&output);
    uint64_t  end = get_milliseconds();
    printTimeDifference(start,end);
  //  clock_gettime(CLOCK_MONOTONIC, &end);

}


int main(){

    int i;
    printf("------Starting Multiple Client Multiple Value Test-----\n");

    for(i=1;i < 20; i++){
        perform_multiple_value_method_call(i);

    }
    printf("------Ending Multiple Client Multiple Value Test-----\n");

    return 0;
}