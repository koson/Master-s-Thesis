//
// Created by cgtybsr on 24.04.18.
//

#include "open62541.h"
#include "signal.h"
#include <stdio.h>


UA_NodeId nodeId,parentNodeId,parentReferenceNodeId,variableType;
UA_QualifiedName qualifiedName;
UA_Logger logger = UA_Log_Stdout;


UA_Boolean running = true;
static void stopHandler(int sig) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
}



static void singleValueMethod(UA_Server *server){
    UA_VariableAttributes variableAttributes =UA_VariableAttributes_default;
    variableAttributes.displayName = UA_LOCALIZEDTEXT("en-US","Single Value Method");
    //initializing string
    UA_String string = UA_STRING("Single Value");
    UA_String_init(&string);
    UA_Variant variant ;
    UA_Variant_init(&variant);
    UA_Variant_setScalar(&variant,&string,&UA_TYPES[UA_TYPES_STRING]);

     nodeId = UA_NODEID_STRING(1, "single_value_method");
     parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
     parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
     variableType = UA_NODEID_NULL; /* take the default variable type */
     qualifiedName = UA_QUALIFIEDNAME(1, "single value");

    UA_Server_addVariableNode(server,nodeId,parentNodeId,parentReferenceNodeId,qualifiedName,variableType,variableAttributes,NULL,NULL);
}


static void multipleValueMethod(UA_Server *server){
    UA_VariableAttributes variableAttributes =UA_VariableAttributes_default;
    variableAttributes.displayName = UA_LOCALIZEDTEXT("en-US","Multiple Value Method");
    //initializing array
    UA_String *arr =   UA_Array_new(1000,&UA_TYPES[UA_TYPES_STRING]);

    for (size_t i=0;i<arr->length;i++){
        arr[i]=UA_STRING("*");
    }

    UA_Variant variant ;
    UA_Variant_init(&variant);

    UA_Variant_setScalar(&variant,&arr,&UA_TYPES[UA_TYPES_STRING]);

    nodeId = UA_NODEID_STRING(1, "multiple_value_method");
    parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    variableType = UA_NODEID_NULL; /* take the default variable type */
    qualifiedName = UA_QUALIFIEDNAME(1, "multiple value");
    UA_Server_addVariableNode(server,nodeId,parentNodeId,parentReferenceNodeId,qualifiedName,variableType,variableAttributes,NULL,NULL);

}
static UA_StatusCode strEchoMethodCallback(UA_Server *server,
                                           const UA_NodeId *sessionId, void *sessionHandle,
                                           const UA_NodeId *methodId, void *methodContext,
                                           const UA_NodeId *objectId, void *objectContext,
                                           size_t inputSize, const UA_Variant *input,
                                           size_t outputSize, UA_Variant *output){

    UA_Variant_setScalarCopy(output, (UA_String*)input->data, &UA_TYPES[UA_TYPES_STRING]);
    //UA_String_deleteMembers(&tmp);
    //UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Hello World was called");

    return UA_STATUSCODE_GOOD;
}

static void addEchoMethod(UA_Server *server) {
    UA_Argument inputArgument;
    UA_Argument_init(&inputArgument);
    inputArgument.description = UA_LOCALIZEDTEXT("en-US", "A String");
    inputArgument.name = UA_STRING("MyInput");
    inputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    inputArgument.valueRank = -1; /* scalar */

    UA_Argument outputArgument;
    UA_Argument_init(&outputArgument);
    outputArgument.description = UA_LOCALIZEDTEXT("en-US", "A String");
    outputArgument.name = UA_STRING("MyOutput");
    outputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    outputArgument.valueRank = -1; /* scalar */

    UA_MethodAttributes helloAttr = UA_MethodAttributes_default;
    helloAttr.description = UA_LOCALIZEDTEXT("en-US","str echo");
    helloAttr.displayName = UA_LOCALIZEDTEXT("en-US","str echo");
    helloAttr.executable = true;
    helloAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1,62541),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
                            UA_QUALIFIEDNAME(1, "str echo"),
                            helloAttr, &strEchoMethodCallback,
                            1, &inputArgument, 1, &outputArgument, NULL, NULL);

}

static UA_StatusCode strAckMethodCallback(UA_Server *server,
                                          const UA_NodeId *sessionId, void *sessionHandle,
                                          const UA_NodeId *methodId, void *methodContext,
                                          const UA_NodeId *objectId, void *objectContext,
                                          size_t inputSize, const UA_Variant *input,
                                          size_t outputSize, UA_Variant *output) {
    UA_String tmp = UA_STRING_ALLOC("Ack");
    UA_Variant_setScalarCopy(output, &tmp, &UA_TYPES[UA_TYPES_STRING]);
    UA_String_deleteMembers(&tmp);
    //UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Hello World was called");
    return UA_STATUSCODE_GOOD;
}
static void addAckMethod(UA_Server *server){
    UA_Argument inputArgument;
    UA_Argument_init(&inputArgument);
    inputArgument.description = UA_LOCALIZEDTEXT("en-US", "A String");
    inputArgument.name = UA_STRING("MyInput");
    inputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    inputArgument.valueRank = -1; /* scalar */

    UA_Argument outputArgument;
    UA_Argument_init(&outputArgument);
    outputArgument.description = UA_LOCALIZEDTEXT("en-US", "A String");
    outputArgument.name = UA_STRING("MyOutput");
    outputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    outputArgument.valueRank = -1; /* scalar */

    UA_MethodAttributes helloAttr = UA_MethodAttributes_default;
    helloAttr.description = UA_LOCALIZEDTEXT("en-US","str ack");
    helloAttr.displayName = UA_LOCALIZEDTEXT("en-US","str ack");
    helloAttr.executable = true;
    helloAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1,62542),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
                            UA_QUALIFIEDNAME(1, "str ack"),
                            helloAttr, &strAckMethodCallback,
                            1, &inputArgument, 1, &outputArgument, NULL, NULL);
}

UA_Int32 compareFunction (const void * a, const void * b) {
    return ( *(UA_Int32 *)a - *(UA_Int32 *)b );
}
static void sortArray(UA_Int32 *inputArray,size_t inputSize,UA_Variant *output){

    UA_Int32 *outputArray = (UA_Int32*)output->data;
    qsort(inputArray,inputSize, sizeof(UA_Int32),compareFunction);

    for(size_t i = 0; i < inputSize; i++)
        outputArray[i] = inputArray[i];

}


static UA_StatusCode strSortedArrayMethodCallback(UA_Server *server,
                                                  const UA_NodeId *sessionId, void *sessionHandle,
                                                  const UA_NodeId *methodId, void *methodContext,
                                                  const UA_NodeId *objectId, void *objectContext,
                                                  size_t inputSize, const UA_Variant *input,
                                                  size_t outputSize, UA_Variant *output){

    UA_Int32 *inputArray = (UA_Int32*)input[0].data;



    /* Copy the input array */
    UA_StatusCode retval = UA_Variant_setArrayCopy(output, inputArray, input[0].arrayLength,
                                                   &UA_TYPES[UA_TYPES_INT32]);
    if(retval != UA_STATUSCODE_GOOD)
        return retval;

    /* Sort the array */
    sortArray(inputArray,input[0].arrayLength,output);
    return UA_STATUSCODE_GOOD;



}
static void addSortedArray(UA_Server *server){
    /* Two input arguments */
    UA_Argument inputArgument;
    UA_Argument_init(&inputArgument);
    inputArgument.description = UA_LOCALIZEDTEXT("en-US", "Int32 array");
    inputArgument.name = UA_STRING("Input Int32 array");
    inputArgument.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    inputArgument.valueRank = 1;

    /* One output argument */
    UA_Argument outputArgument;
    UA_Argument_init(&outputArgument);
    outputArgument.description = UA_LOCALIZEDTEXT("en-US", "int32 array");
    outputArgument.name = UA_STRING("Output Int32 Array");
    outputArgument.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    outputArgument.valueRank = 1;
    UA_UInt32 pOutputDimension = 5;
    outputArgument.arrayDimensionsSize = 1;
    outputArgument.arrayDimensions = &pOutputDimension;

    /* Add the method node */
    UA_MethodAttributes incAttr = UA_MethodAttributes_default;
    incAttr.description = UA_LOCALIZEDTEXT("en-US", "sorted_array_method");
    incAttr.displayName = UA_LOCALIZEDTEXT("en-US", "sorted_array_method");
    incAttr.executable = true;
    incAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_STRING(1, "sorted_array_method"),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                            UA_QUALIFIEDNAME(1, "IncInt32ArrayValues"),
                            incAttr, &strSortedArrayMethodCallback,
                            1, &inputArgument, 1, &outputArgument,
                            NULL, NULL);
}
static UA_StatusCode readVariable(UA_Server *server,const UA_NodeId *sessionId,void *sessionContext,
                                  const UA_NodeId *nodeId, void *nodeContext, UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                                  UA_DataValue *dataValue)
{

}


static UA_StatusCode  updateVariable(){
    nodeId = UA_NODEID_STRING(1,"update_variable_key");


}




//150 Variable nodes
//20 clients
//1000 variables

static UA_StatusCode strStefansMethodCallback(){

}
static void addStefansMethod(){

}

static void startUDPServer(UA_Server *server){
//    UA_ServerConfig *config = UA_ServerConfig_new_default();
//    UA_ServerNetworkLayer nl;
//    nl = UA_ServerNetworkLayerUDP(UA_ConnectionConfig_standard, 4840);
//    config.networkLayers = &nl;
//    config.networkLayersSize = 1;
//    UA_Server *server = UA_Server_new(config);
}

static void addCertificateToServer(){

}


int main(){
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);




    UA_ServerConfig *config = UA_ServerConfig_new_default();
    UA_Server *server = UA_Server_new(config);

    //Methods
    singleValueMethod(server);
    multipleValueMethod(server);
    addEchoMethod(server);
    addAckMethod(server);
    addSortedArray(server);
    startUDPServer(server);



    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    return (int)retval;
}



//static UA_StatusCode singleEchoMethodCallback(UA_Server *server,
//                                              const UA_NodeId *sessionId, void *sessionHandle,
//                                              const UA_NodeId *methodId, void *methodContext,
//                                              const UA_NodeId *objectId, void *objectContext,
//                                              size_t inputSize, const UA_Variant *input,
//                                              size_t outputSize, UA_Variant *output){
//    UA_String s;
//    UA_String_init(&s);
//    char *str ="Single Value";
//    s.length =strlen(str);
//    s.data = (UA_Byte*) str;
//
//    UA_Variant variant;
//    UA_Variant_setScalar(&variant,&s,&UA_TYPES[UA_TYPES_STRING]);
//    UA_Variant_copy(&variant,output);
//    UA_LOG_INFO(UA_Log_Stdout,UA_LOGCATEGORY_SERVER,"Single Echo Method Called");
//
//    return UA_STATUSCODE_GOOD;
//}
//static void addSingleEchoMethod(UA_Server *server){
//
//
//    UA_Argument outputArg;
//    UA_Argument_init(&outputArg);
//    outputArg.description= UA_LOCALIZEDTEXT("en-EN","A String");
//    outputArg.name = UA_STRING("data");
//    outputArg.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
//    outputArg.valueRank = -1;
//
//    UA_MethodAttributes methodAttributes = UA_MethodAttributes_default;
//
//    methodAttributes.description = UA_LOCALIZEDTEXT("en-EN","Get the data from server");
//    methodAttributes.displayName = UA_LOCALIZEDTEXT("en-EN","getData");
//    methodAttributes.executable = true;
//    methodAttributes.userExecutable = true;
//
////    UA_Server_addVariableNode(server,UA_NODEID_NUMERIC(1,12345),
////                              UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
////                              UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
////                              UA_QUALIFIEDNAME(1,"browseName"),UA_NODEID_NULL,&singleEchoMethodCallback,NULL,NULL);
//
//
//
//    UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1,12345),
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
//                            UA_QUALIFIEDNAME(1, "Get Data from server"),
//                            methodAttributes, &singleEchoMethodCallback,     0, NULL, 1, &outputArg, NULL, NULL);
//}
//
//
//static void singleVariableMethod(UA_Server *server){
//
//    //Node Attributes
//    UA_VariableAttributes variableAttributes = UA_VariableAttributes_default;
//    variableAttributes.displayName=UA_LOCALIZEDTEXT("en-Us","Head of Horse");
//    UA_Int32 integer = 06;
//    UA_Variant_setScalar(&variableAttributes.value,&integer,&UA_TYPES[UA_TYPES_INT32]);
//
//    //Where node will be added with which browse name
//
//    UA_Server_addVariableNode(server,UA_NODEID_NUMERIC(0,12345)
//    ,UA_NODEID_NUMERIC(0,UA_NS0ID_OBJECTSFOLDER),
//    UA_NODEID_NUMERIC(0,UA_NS0ID_ORGANIZES),
//    UA_QUALIFIEDNAME(1,"hop"),UA_NODEID_NULL,variableAttributes,NULL,NULL);
//
//
//}
//    addEchoMethod(server);
//    addAckMethod(server);
//    addSortedArrayMethod(server);

//void swap(int *xp, int *yp)
//{
//    int temp = *xp;
//    *xp = *yp;
//    *yp = temp;
//}
//
//static void addSingleStringMethod(){
//
//}
//
//
//static UA_Int32* sortingFunc(UA_Int32 *inputArray,size_t size){
//   int i,j;
//    for (i=0;i<(size-1);i++){
//        for(j=0;j<size-i-1;j++)
//            if(inputArray[j]>inputArray[j+1])
//                swap(&inputArray[j],&inputArray[j+1]);
//
//    }
//
//
//}
//
//
//static void printArray(UA_Int32 *inputArray,size_t inputSize){
//    for(size_t i = 0; i < inputSize ; i++)
//        printf("%d ",inputArray[i]);
//
//}
//
//static UA_StatusCode strSortedArrayCallback(UA_Server *server,
//                                            const UA_NodeId *sessionId, void *sessionContext,
//                                            const UA_NodeId *methodId, void *methodContext,
//                                            const UA_NodeId *objectId, void *objectContext,
//                                            size_t inputSize, const UA_Variant *input,
//                                            size_t outputSize, UA_Variant *output){
//    UA_Int32 *inputArray = (UA_Int32*)input[0].data;
//    UA_Int32 delta = *(UA_Int32*)input[1].data;
//
//    /* Copy the input array */
//    UA_StatusCode retval = UA_Variant_setArrayCopy(output, inputArray, inputSize,
//                                                   &UA_TYPES[UA_TYPES_INT32]);
//    if(retval != UA_STATUSCODE_GOOD)
//        return retval;
//    printf("Incoming array");
//    printArray(inputArray,inputSize);
//
//    /* In create the elements */
//
//
//        inputArray = sortingFunc(inputArray,inputSize);
//
//    UA_Int32 *outputArray = (UA_Int32*)output->data;
//
//
//
//    for(size_t i = 0; i < input->arrayLength; i++)
//        outputArray[i] = inputArray[i] + delta;
//       //   outputArray[i] = inputArray[i];
//
//  //  UA_Int32 *outputArr = sortingFunc(inputArray);
//
//    //printf("Sorted array");
//   // outputArray = sortingFunc(inputArray);
//   // printArray(outputArray,outputSize);
//
//
//    for(size_t i = 0; i < input->arrayLength; i++)
//        outputArray[i] = inputArray[i] + delta;
//
//    return UA_STATUSCODE_GOOD;
//}
//
//
//static void addSortedArrayMethod(UA_Server *server){
//    UA_Argument inputArguments[2];
//    UA_Argument_init(&inputArguments[0]);
//    inputArguments[0].description = UA_LOCALIZEDTEXT("en-US", "int32[1000] array");
//    inputArguments[0].name = UA_STRING("int32 array");
//    inputArguments[0].dataType = UA_TYPES[UA_TYPES_INT32].typeId;
//    inputArguments[0].valueRank = 1;
//    UA_UInt32 pInputDimension = 5;
//    inputArguments[0].arrayDimensionsSize = 1;
//    inputArguments[0].arrayDimensions = &pInputDimension;
//
//
//    UA_Argument_init(&inputArguments[1]);
//    inputArguments[1].description = UA_LOCALIZEDTEXT("en-US", "int32 delta");
//    inputArguments[1].name = UA_STRING("int32 delta");
//    inputArguments[1].dataType = UA_TYPES[UA_TYPES_INT32].typeId;
//    inputArguments[1].valueRank = -1; /* scalar */
//
//    UA_Argument outputArgument;
//    UA_Argument_init(&outputArgument);
//    outputArgument.description = UA_LOCALIZEDTEXT("en-US", "int32[1000] array");
//    outputArgument.name = UA_STRING("each entry is sorted ");
//    outputArgument.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
//    outputArgument.valueRank = 1;
//    UA_UInt32 pOutputDimension = 5;
//    outputArgument.arrayDimensionsSize = 1;
//    outputArgument.arrayDimensions = &pOutputDimension;
//
//    UA_MethodAttributes incAttr = UA_MethodAttributes_default;
//    incAttr.description = UA_LOCALIZEDTEXT("en-US", "IncInt32ArrayValues");
//    incAttr.displayName = UA_LOCALIZEDTEXT("en-US", "IncInt32ArrayValues");
//    incAttr.executable = true;
//    incAttr.userExecutable = true;
//    UA_Server_addMethodNode(server, UA_NODEID_STRING(1, "IncInt32ArrayValues"),
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
//                            UA_QUALIFIEDNAME(1, "IncInt32ArrayValues"),
//                            incAttr, &strSortedArrayCallback,
//                            2, inputArguments, 1, &outputArgument,
//                            NULL, NULL);
//
//
//}
//
//
//
//static UA_StatusCode
//strEchoMethodCallback(UA_Server *server,
//                      const UA_NodeId *sessionId, void *sessionHandle,
//                      const UA_NodeId *methodId, void *methodContext,
//                      const UA_NodeId *objectId, void *objectContext,
//                      size_t inputSize, const UA_Variant *input,
//                      size_t outputSize, UA_Variant *output) {
//    UA_Variant_setScalarCopy(output, (UA_String*)input->data, &UA_TYPES[UA_TYPES_STRING]);
//    //UA_String_deleteMembers(&tmp);
//    //UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Hello World was called");
//    return UA_STATUSCODE_GOOD;
//}
//
//static UA_StatusCode
//strAckMethodCallback(UA_Server *server,
//                     const UA_NodeId *sessionId, void *sessionHandle,
//                     const UA_NodeId *methodId, void *methodContext,
//                     const UA_NodeId *objectId, void *objectContext,
//                     size_t inputSize, const UA_Variant *input,
//                     size_t outputSize, UA_Variant *output) {
//    UA_String tmp = UA_STRING_ALLOC("Ack");
//    UA_Variant_setScalarCopy(output, &tmp, &UA_TYPES[UA_TYPES_STRING]);
//    UA_String_deleteMembers(&tmp);
//    //UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Hello World was called");
//    return UA_STATUSCODE_GOOD;
//}
//static void
//addEchoMethod(UA_Server *server) {
//    UA_Argument inputArgument;
//    UA_Argument_init(&inputArgument);
//    inputArgument.description = UA_LOCALIZEDTEXT("en-US", "A String");
//    inputArgument.name = UA_STRING("MyInput");
//    inputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
//    inputArgument.valueRank = -1; /* scalar */
//
//    UA_Argument outputArgument;
//    UA_Argument_init(&outputArgument);
//    outputArgument.description = UA_LOCALIZEDTEXT("en-US", "A String");
//    outputArgument.name = UA_STRING("MyOutput");
//    outputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
//    outputArgument.valueRank = -1; /* scalar */
//
//    UA_MethodAttributes helloAttr = UA_MethodAttributes_default;
//    helloAttr.description = UA_LOCALIZEDTEXT("en-US","str echo");
//    helloAttr.displayName = UA_LOCALIZEDTEXT("en-US","str echo");
//    helloAttr.executable = true;
//    helloAttr.userExecutable = true;
//    UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1,62541),
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
//                            UA_QUALIFIEDNAME(1, "str echo"),
//                            helloAttr, &strEchoMethodCallback,
//                            1, &inputArgument, 1, &outputArgument, NULL, NULL);
//}
//
//static void
//addAckMethod(UA_Server *server) {
//    UA_Argument inputArgument;
//    UA_Argument_init(&inputArgument);
//    inputArgument.description = UA_LOCALIZEDTEXT("en-US", "A String");
//    inputArgument.name = UA_STRING("MyInput");
//    inputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
//    inputArgument.valueRank = -1; /* scalar */
//
//    UA_Argument outputArgument;
//    UA_Argument_init(&outputArgument);
//    outputArgument.description = UA_LOCALIZEDTEXT("en-US", "A String");
//    outputArgument.name = UA_STRING("MyOutput");
//    outputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
//    outputArgument.valueRank = -1; /* scalar */
//
//    UA_MethodAttributes helloAttr = UA_MethodAttributes_default;
//    helloAttr.description = UA_LOCALIZEDTEXT("en-US","str ack");
//    helloAttr.displayName = UA_LOCALIZEDTEXT("en-US","str ack");
//    helloAttr.executable = true;
//    helloAttr.userExecutable = true;
//    UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1,62542),
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
//                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
//                            UA_QUALIFIEDNAME(1, "str ack"),
//                            helloAttr, &strAckMethodCallback,
//                            1, &inputArgument, 1, &outputArgument, NULL, NULL);
//}
//
//
