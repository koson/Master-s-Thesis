//
// Created by cgtybsr on 24.04.18.
//

#include <signal.h>
#include "open62541.h"

UA_Boolean running = true;
void signalHandler(int sig) {
    running = false;
}

int main(int argc, char** argv)
{
    signal(SIGINT, signalHandler); /* catch ctrl-c */

    /* Create a server listening on port 4840 */
    UA_ServerConfig *config = UA_ServerConfig_new_default();
    UA_Server *server = UA_Server_new(config);

    /* Add a variable node */
    /* 1) Define the node attributes */
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "the answer");
    UA_Int32 myInteger = 42;
    UA_Variant_setScalar(&attr.value, &myInteger, &UA_TYPES[UA_TYPES_INT32]);

    /* 2) Define where the node shall be added with which browsename */
    UA_NodeId newNodeId = UA_NODEID_STRING(1, "the.answer");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableType = UA_NODEID_NULL; /* take the default variable type */
    UA_QualifiedName browseName = UA_QUALIFIEDNAME(1, "the answer");

    /* 3) Add the node */
    UA_Server_addVariableNode(server, newNodeId, parentNodeId, parentReferenceNodeId,
                              browseName, variableType, attr, NULL, NULL);

    /* Run the server loop */
    UA_StatusCode status = UA_Server_run(server, &running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    return status;
}

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

