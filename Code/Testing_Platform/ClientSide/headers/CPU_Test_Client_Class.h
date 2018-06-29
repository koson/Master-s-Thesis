//
// Created by cgtybsr on 07.06.18.
//

#ifndef OPC_UA_TESTING_PLATFORM_CPU_TEST_CLIENT_CLASS_H
#define OPC_UA_TESTING_PLATFORM_CPU_TEST_CLIENT_CLASS_H

#include "open62541.h"
#include "commonClientMethods.h"



static UA_StatusCode startGettingSingleValueTest(){

    UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"-----Starting CPU Single Value Test-------------------");
    statusCode =  initializeConnection();
    if(statusCode != UA_STATUSCODE_GOOD){
        return statusCode;
    }
    nodeId = UA_NODEID_STRING(1,"single_value_method");
    parentNodeId =  UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    objectId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    methodId = UA_NODEID_STRING(1, "single_value_method");
    uint64_t start_time= get_milliseconds();
    UA_Client_call(client,objectId,methodId,0,NULL,&outputSize,&output);
    uint64_t  end_time = get_milliseconds();
    printTimeDifference(start_time,end_time);
    UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"-----Ending CPU Single Value Test-------------------");
    return statusCode;
}

static UA_StatusCode startGettingMultipleValueTest(){
    UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"-----Starting CPU Multiple Value Test-------------------");
    statusCode =  initializeConnection();
    if(statusCode != UA_STATUSCODE_GOOD){
        return statusCode;
    }
    nodeId = UA_NODEID_STRING(1,"multiple_value_node");
    parentNodeId =  UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    objectId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    methodId = UA_NODEID_STRING(1,"multiple_value_method");
    objectId =  UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    uint64_t  start_time = get_milliseconds();
    UA_Client_call(client,objectId,methodId,0,NULL,&outputSize,&output);
    uint64_t end_time = get_milliseconds();
    printTimeDifference(start_time,end_time);
    UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"-----Ending CPU Multiple Value Test-------------------");
    return statusCode;

}
static UA_StatusCode startGettingMultipleCustomObjectTest(){

    UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"-----Starting CPU Multiple Custom Object Test-------------------");
    statusCode =  initializeConnection();
    if(statusCode != UA_STATUSCODE_GOOD){
        return statusCode;
    }
    nodeId = UA_NODEID_STRING(1,"multiple_object_node");
    parentNodeId =  UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    objectId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    methodId = UA_NODEID_STRING(1,"multiple_object_method");
    objectId =  UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    uint64_t  start_time = get_milliseconds();
    UA_Client_call(client,objectId,methodId,0,NULL,&outputSize,&output);
    uint64_t end_time = get_milliseconds();
    printTimeDifference(start_time,end_time);
    UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"-----Ending CPU Multiple Custom Object Test-------------------");
    return statusCode;

}

static UA_StatusCode startWritingValueTest() {
    UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"-----Starting Writing Value Test-------------------");
    statusCode =  initializeConnection();
    if(statusCode != UA_STATUSCODE_GOOD){
        return statusCode;
    }
    nodeId = UA_NODEID_STRING(1, "input_method");
    parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    objectId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_Int32 value = 45;
    UA_Variant *myVariant = UA_Variant_new();
    UA_Variant_setScalarCopy(myVariant, &value, &UA_TYPES[UA_TYPES_INT32]);
    uint64_t start_time = get_milliseconds();
    UA_Client_call(client, objectId, methodId, 1, myVariant, 0, NULL);
    uint64_t end_time = get_milliseconds();
    printTimeDifference(start_time, end_time);
    UA_Variant_delete(myVariant);
    UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"-----Ending CPU Writing Value Test-------------------");

    return  statusCode;
}



static UA_StatusCode startSortingTest(){
    UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"-----Starting CPU Sorting Test-------------------");
    statusCode =  initializeConnection();

    if(statusCode != UA_STATUSCODE_GOOD){
        return statusCode;
    }
    int i;
    UA_Double randomArray[100000],sortedArray[100000];
    srand((unsigned int) time(NULL));
    for(i=0;i<100000;i++){
        randomArray[i]= (rand()%100);
    }
    size_t size = sizeof(randomArray)/ sizeof(randomArray[0]);

    UA_Variant input;
    UA_Variant_init(&input);
    UA_Variant_setArray(&input,&randomArray,size,&UA_TYPES[UA_TYPES_DOUBLE]);

//    UA_Variant *output;
//    UA_Variant_init(output);
//    UA_Variant_setArray(output,&sortedArray,size,&UA_TYPES[UA_TYPES_DOUBLE]);
//

    uint64_t  start_time = get_milliseconds();
    UA_Client_call(client,UA_NODEID_NUMERIC(0,UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(1,77777),size,&input,&size,&output);
    uint64_t end_time = get_milliseconds();
    printTimeDifference(start_time,end_time);
    UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"-----Ending CPU Sorting Test-------------------");
    return statusCode;
}







#endif //OPC_UA_TESTING_PLATFORM_CPU_TEST_CLIENT_CLASS_H