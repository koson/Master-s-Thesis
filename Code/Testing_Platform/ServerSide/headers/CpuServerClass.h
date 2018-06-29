//
// Created by cgtybsr on 03.06.18.
//

#ifndef MASTER_S_THESIS_CPUSERVERCLASS_H
#define MASTER_S_THESIS_CPUSERVERCLASS_H

#include "../open62541.h"
#include "custom_datatype.h"
#include "commonServerMethods.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

struct timespec start, end;
UA_NodeId nodeId,parentNodeId,parentReferenceNodeId,variableType;
UA_QualifiedName qualifiedName;



static void
addSingleVariableNode(UA_Server *server, UA_Int32 id) {

    UA_NodeId baseDataVariableType = {0, UA_NODEIDTYPE_NUMERIC, {UA_NS0ID_BASEDATAVARIABLETYPE}};
    UA_VariableAttributes myVar = UA_VariableAttributes_default;
    myVar.description = UA_LOCALIZEDTEXT("en-US", "the answer");
    myVar.displayName = UA_LOCALIZEDTEXT("en-US", "the answer");
    myVar.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    myVar.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    myVar.valueRank = -1;
    UA_Int32 myInteger = 42;
    UA_Variant_setScalarCopy(&myVar.value, &myInteger, &UA_TYPES[UA_TYPES_INT32]);
    const UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME(1, "the answer");
    nodeId = UA_NODEID_NUMERIC(1, id);
    parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_Server_addVariableNode(server, nodeId, parentNodeId, parentReferenceNodeId,
                              myIntegerName, baseDataVariableType, myVar, NULL, NULL);
}
static void addArrayNode(UA_Server *server,UA_Int32 id){
    UA_VariableTypeAttributes vtAttr = UA_VariableTypeAttributes_default;
    UA_NodeId pointTypeId;
    vtAttr.dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
    vtAttr.valueRank = 1; /* array with one dimension */
    UA_UInt32 arrayDims[1] = {2};
    vtAttr.arrayDimensions = arrayDims;
    vtAttr.arrayDimensionsSize = 1;
    vtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "2DPoint Type");

    /* a matching default value is required */
    UA_Double zero[2] = {0.0, 0.0};
    UA_Variant_setArray(&vtAttr.value, zero, 2, &UA_TYPES[UA_TYPES_DOUBLE]);
    nodeId = UA_NODEID_NUMERIC(1, id);
    UA_Server_addVariableTypeNode(server, nodeId,
                                  UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                  UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                  UA_QUALIFIEDNAME(1, "2DPoint Type"), UA_NODEID_NULL,
                                  vtAttr, NULL, &pointTypeId);
}

static void deleteNode(UA_Server *server,UA_Int32 id)
{
    const UA_NodeId myIntegerNodeId = UA_NODEID_NUMERIC(1, id);
    UA_Server_deleteNode(server,myIntegerNodeId,true);

}

static void startAddingSingleVariableNodeTest(UA_Server *server,UA_Int32 size){
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 1; i <= size; i++){
        addSingleVariableNode(server, i);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Adding %d nodes took about %.5f seconds\n",size,
           ((double)end.tv_sec + 1.0e-9*end.tv_nsec) -
           ((double)start.tv_sec + 1.0e-9*start.tv_nsec));

    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i=1;i<=size;i++){
        deleteNode(server,i);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Deleting %d nodes took about %.5f seconds\n",size,
           ((double)end.tv_sec + 1.0e-9*end.tv_nsec) -
           ((double)start.tv_sec + 1.0e-9*start.tv_nsec));

}

static void startAddingArrayNodeTest(UA_Server *server,UA_Int32 size){

    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 1; i <= size; i++){
        addArrayNode(server, i);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Adding %d array variable nodes took about %.5f seconds\n",size,
           ((double)end.tv_sec + 1.0e-9*end.tv_nsec) -
           ((double)start.tv_sec + 1.0e-9*start.tv_nsec));

    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i=1;i<=size;i++){
        deleteNode(server,i);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Deleting %d array variable nodes took about %.5f seconds\n",size,
           ((double)end.tv_sec + 1.0e-9*end.tv_nsec) -
           ((double)start.tv_sec + 1.0e-9*start.tv_nsec));
}


static  UA_StatusCode multipleObjectMethodCallback(UA_Server *server,
                                                  const UA_NodeId *sessionId, void *sessionHandle,
                                                  const UA_NodeId *methodId, void *methodContext,
                                                  const UA_NodeId *objectId, void *objectContext,
                                                  size_t inputSize, const UA_Variant *input,
                                                  size_t outputSize, UA_Variant *output){
    UA_Int32 *size = (UA_Int32*)input->data;
    Point p[*size];
    for(int i=0;i<*size;i++){
        p[i].x = *size;
        p[i].y = *size;
        p[i].z = *size;
    }
    UA_Variant_setScalar(output,&p,&PointType);
}

static UA_StatusCode multipleCustomObjectMethod(UA_Server *server){
    UA_Argument inputArgument;
    UA_Argument_init(&inputArgument);
    inputArgument.description = UA_LOCALIZEDTEXT("en-US", "An Integer of Object Size");
    inputArgument.name = UA_STRING("MyInput");
    inputArgument.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    inputArgument.valueRank = -1; /* scalar */

    UA_Argument outputArgument;
    UA_Argument_init(&outputArgument);
    outputArgument.description = UA_LOCALIZEDTEXT("en-US", "An array of Objects");
    outputArgument.name = UA_STRING("MyOutput");
    outputArgument.dataType = PointType.typeId;
    outputArgument.valueRank = -1; /* scalar */


    nodeId = UA_NODEID_STRING(1, "multiple_object_node");
    parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT);
    variableType = UA_NODEID_NULL; /* take the default variable type */
    qualifiedName = UA_QUALIFIEDNAME(1, "multiple_object_method");

    UA_MethodAttributes methodAttributes = UA_MethodAttributes_default;
    methodAttributes.description = UA_LOCALIZEDTEXT("en-US","multiple object");
    methodAttributes.displayName = UA_LOCALIZEDTEXT("en-US","multiple object");
    methodAttributes.executable = true;
    methodAttributes.userExecutable = true;

    UA_Server_addMethodNode(server,nodeId,
                            parentNodeId,parentReferenceNodeId,
                            qualifiedName,
                            methodAttributes, &multipleObjectMethodCallback,
                            1,&inputArgument,1,&outputArgument,NULL,NULL);
}


static UA_StatusCode
writeVariableMethodCallback(UA_Server *server,
                            const UA_NodeId *sessionId, void *sessionHandle,
                            const UA_NodeId *methodId, void *methodContext,
                            const UA_NodeId *objectId, void *objectContext,
                            size_t inputSize, const UA_Variant *input,
                            size_t outputSize, UA_Variant *output) {
    /* Write a input string value */
    UA_String *inputStr = (UA_String*)input->data;
    UA_Variant variant;
    UA_Variant_init(&variant);
    UA_Variant_setScalar(&variant,&inputStr,&UA_TYPES[UA_TYPES_STRING]);
    UA_Server_writeValue(server,nodeId,variant);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Input Method is called");


}

static UA_StatusCode writeVariableMethod(UA_Server *server){
    UA_Argument inputArgument;
    UA_Argument_init(&inputArgument);
    inputArgument.description = UA_LOCALIZEDTEXT("en-US", "A Character");
    inputArgument.name = UA_STRING("My Input");
    inputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    inputArgument.valueRank = -1; /* scalar */


    nodeId = UA_NODEID_STRING(1, "input_method");
    parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT);
    variableType = UA_NODEID_NULL; /* take the default variable type */
    qualifiedName = UA_QUALIFIEDNAME(1, "input method");

    UA_MethodAttributes methodAttributes = UA_MethodAttributes_default;
    methodAttributes.description = UA_LOCALIZEDTEXT("en-US","input_method");
    methodAttributes.displayName = UA_LOCALIZEDTEXT("en-US","input method");
    methodAttributes.executable = true;
    methodAttributes.userExecutable = true;

    UA_Server_addMethodNode(server,nodeId,
                            parentNodeId,parentReferenceNodeId,
                            qualifiedName,
                            methodAttributes, &writeVariableMethodCallback,
                            1,&inputArgument,0,NULL ,NULL,NULL);

    return UA_STATUSCODE_GOOD;
}


static UA_StatusCode
singleValueMethodCallback(UA_Server *server,
                          const UA_NodeId *sessionId, void *sessionHandle,
                          const UA_NodeId *methodId, void *methodContext,
                          const UA_NodeId *objectId, void *objectContext,
                          size_t inputSize, const UA_Variant *input,
                          size_t outputSize, UA_Variant *output) {

    UA_String tmp = UA_STRING_ALLOC("*");
    UA_Variant_setScalarCopy(output, &tmp, &UA_TYPES[UA_TYPES_STRING]);
    UA_String_deleteMembers(&tmp);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Single Value Method was called");
    return UA_STATUSCODE_GOOD;
}




static void singleValueMethod(UA_Server *server){


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


    nodeId = UA_NODEID_STRING(1, "single_value_method");
    parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT);
    variableType = UA_NODEID_NULL; /* take the default variable type */
    qualifiedName = UA_QUALIFIEDNAME(1, "single value method");

    UA_MethodAttributes methodAttributes = UA_MethodAttributes_default;
    methodAttributes.description = UA_LOCALIZEDTEXT("en-US","single_value");
    methodAttributes.displayName = UA_LOCALIZEDTEXT("en-US","single value");
    methodAttributes.executable = true;
    methodAttributes.userExecutable = true;

    UA_Server_addMethodNode(server,nodeId,
                            parentNodeId,parentReferenceNodeId,
                            qualifiedName,
                            methodAttributes, &singleValueMethodCallback,
                            0,NULL,1,&outputArgument,NULL,NULL);
}
static UA_StatusCode
multipleValueMethodCallback(UA_Server *server,
                            const UA_NodeId *sessionId, void *sessionHandle,
                            const UA_NodeId *methodId, void *methodContext,
                            const UA_NodeId *objectId, void *objectContext,
                            size_t inputSize, const UA_Variant *input,
                            size_t outputSize, UA_Variant *output) {
    UA_Int32 *size = (UA_Int32*)input->data;
    UA_String arr[*size];
    for (size_t i=0;i<sizeof(arr)/sizeof(UA_String);i++){
        arr[i]=UA_STRING("*");
    }
    UA_Variant_setArrayCopy(output,arr,sizeof(arr)/sizeof(UA_String),&UA_TYPES[UA_TYPES_STRING]);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Multiple Value Method was called");
    return UA_STATUSCODE_GOOD;
}




static void multipleValueMethod(UA_Server *server){
    UA_VariableAttributes variableAttributes =UA_VariableAttributes_default;
    variableAttributes.displayName = UA_LOCALIZEDTEXT("en-US","Multiple Value Method");

    UA_Argument inputArgument;
    UA_Argument_init(&inputArgument);
    inputArgument.description = UA_LOCALIZEDTEXT("en-US", "Input size of array");
    inputArgument.name = UA_STRING("My Input");
    inputArgument.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    inputArgument.valueRank = -1; /* scalar */

    nodeId = UA_NODEID_STRING(1, "multiple_value_node");
    parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT);
    variableType = UA_NODEID_NULL; /* take the default variable type */
    qualifiedName = UA_QUALIFIEDNAME(1, "multiple_value_node");


    UA_Argument outputArgument;
    UA_Argument_init(&outputArgument);
    outputArgument.description = UA_LOCALIZEDTEXT("en-US", "A String Array with the size of input parameters");
    outputArgument.name = UA_STRING("MyOutput");
    outputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    outputArgument.valueRank = -1; /* scalar */




    UA_MethodAttributes methodAttributes = UA_MethodAttributes_default;
    methodAttributes.description = UA_LOCALIZEDTEXT("en-US","multiple_value");
    methodAttributes.displayName = UA_LOCALIZEDTEXT("en-US","multiple value");
    methodAttributes.executable = true;
    methodAttributes.userExecutable = true;

    UA_Server_addMethodNode(server,nodeId,
                            parentNodeId,parentReferenceNodeId,
                            qualifiedName,
                            methodAttributes, &multipleValueMethodCallback,
                            1,&inputArgument,1,&outputArgument,NULL,NULL);


    //  UA_Server_addVariableNode(server,nodeId,parentNodeId,parentReferenceNodeId,qualifiedName,variableType,variableAttributes,NULL,NULL);

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
static void sortingArrayTest(UA_Server *server){
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
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
                            UA_QUALIFIEDNAME(1, "IncInt32ArrayValues"),
                            incAttr, &strSortedArrayMethodCallback,
                            1, &inputArgument, 1, &outputArgument,
                            NULL, NULL);
}


#endif //MASTER_S_THESIS_CPUSERVERCLASS_H
