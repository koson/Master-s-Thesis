//
// Created by cgtybsr on 07.06.18.
//

#ifndef OPC_UA_TESTING_PLATFORM_CPU_TEST_CLIENT_CLASS_H
#define OPC_UA_TESTING_PLATFORM_CPU_TEST_CLIENT_CLASS_H

#include "../open62541.h"
#include "../commonTestingMethods.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


static void startGettingSingleValueTest(){
    nodeId = UA_NODEID_STRING(1,"single_value_method");
    parentNodeId =  UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    objectId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    methodId = UA_NODEID_STRING(1, "single_value_method");
    uint64_t start_time= get_milliseconds();
    UA_Client_call(client,objectId,methodId,0,NULL,&outputSize,&output);
    uint64_t  end_time = get_milliseconds();
    printTimeDifference(start_time,end_time);
}

static void startGettingMultipleValueTest(){
    nodeId = UA_NODEID_STRING(1,"multiple_value_node");
    parentNodeId =  UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    objectId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    methodId = UA_NODEID_STRING(1,"multiple_value_method");
    objectId =  UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    uint64_t  start_time = get_milliseconds();
    UA_Client_call(client,objectId,methodId,0,NULL,&outputSize,&output);
    uint64_t end_time = get_milliseconds();
    printTimeDifference(start_time,end_time);

}
static void startGettingMultipleCustomObjectTest(){
    nodeId = UA_NODEID_STRING(1,"multiple_object_node");
    parentNodeId =  UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    objectId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    methodId = UA_NODEID_STRING(1,"multiple_object_method");
    objectId =  UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    uint64_t  start_time = get_milliseconds();
    UA_Client_call(client,objectId,methodId,0,NULL,&outputSize,&output);
    uint64_t end_time = get_milliseconds();
    printTimeDifference(start_time,end_time);

}

static void startWritingValueTest(){
    nodeId = UA_NODEID_STRING(1,"input_method");
    parentNodeId =  UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    objectId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_Int32 value =45;
    UA_Variant *myVariant = UA_Variant_new();
    UA_Variant_setScalarCopy(myVariant, &value, &UA_TYPES[UA_TYPES_INT32]);
    uint64_t  start_time = get_milliseconds();
    UA_Client_call(client,objectId,methodId,1,myVariant,0,NULL);
    uint64_t end_time = get_milliseconds();
    printTimeDifference(start_time,end_time);
    UA_Variant_delete(myVariant);


}




static void startSortingTest(){
    int i;
    UA_Double randomArray[100000],sortedArray[100000];
    srand((unsigned int) time(NULL));
    for(i=0;i<100000;i++){
        randomArray[i]= (rand()%100);
    }

    UA_Variant variant;
    UA_Variant_init(&variant);
    UA_Variant_setArray(&variant,&randomArray,100000,&UA_TYPES[UA_TYPES_DOUBLE]);
    uint64_t  start_time = get_milliseconds();
    UA_Client_call(client,UA_NODEID_NUMERIC(0,UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(1,77777),100000,&randomArray,100000,sortedArray);
    uint64_t end_time = get_milliseconds();
    printTimeDifference(start_time,end_time);
}







#endif //OPC_UA_TESTING_PLATFORM_CPU_TEST_CLIENT_CLASS_H
