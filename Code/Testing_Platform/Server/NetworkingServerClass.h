//
// Created by cgtybsr on 03.06.18.
//

#ifndef MASTER_S_THESIS_NETWORKINGSERVERCLASS_H
#define MASTER_S_THESIS_NETWORKINGSERVERCLASS_H


#include <stdio.h>
#include <signal.h>
#include "open62541.h"
#include "commonServerMethods.h"



static UA_StatusCode echoMethodCallback(UA_Server *server,
                                        const UA_NodeId *sessionId, void *sessionHandle,
                                        const UA_NodeId *methodId, void *methodContext,
                                        const UA_NodeId *objectId, void *objectContext,
                                        size_t inputSize, const UA_Variant *input,
                                        size_t outputSize, UA_Variant *output){
    UA_Variant_setScalarCopy(output, (UA_String*)input->data, &UA_TYPES[UA_TYPES_STRING]);
    return UA_STATUSCODE_GOOD;
}


static void echoMethod(UA_Server *server)
{
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
                            helloAttr, &echoMethodCallback,
                            1, &inputArgument, 1, &outputArgument, NULL, NULL);
}




static UA_StatusCode ackMethodCallback(UA_Server *server,
                                       const UA_NodeId *sessionId, void *sessionHandle,
                                       const UA_NodeId *methodId, void *methodContext,
                                       const UA_NodeId *objectId, void *objectContext,
                                       size_t inputSize, const UA_Variant *input,
                                       size_t outputSize, UA_Variant *output){

    UA_String tmp = UA_STRING_ALLOC("Ack");
    UA_Variant_setScalarCopy(output, &tmp, &UA_TYPES[UA_TYPES_STRING]);
    UA_String_deleteMembers(&tmp);
    return UA_STATUSCODE_GOOD;

}
static void ackMethod(UA_Server *server){
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
                            helloAttr, &ackMethodCallback,
                            1, &inputArgument, 1, &outputArgument, NULL, NULL);


}
static void
updateCurrentTime(UA_Server *server) {
    UA_DateTime now = UA_DateTime_now();
    UA_Variant value;
    UA_Variant_setScalar(&value, &now, &UA_TYPES[UA_TYPES_DATETIME]);
    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "current-time");
    UA_Server_writeValue(server, currentNodeId, value);
}

static void
addCurrentTimeVariable(UA_Server *server) {
    UA_DateTime now = 0;
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "Current time");
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_Variant_setScalar(&attr.value, &now, &UA_TYPES[UA_TYPES_DATETIME]);

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "current-time");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "current-time");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);
    UA_Server_addVariableNode(server, currentNodeId, parentNodeId,
                              parentReferenceNodeId, currentName,
                              variableTypeNodeId, attr, NULL, NULL);

    updateCurrentTime(server);
}
#endif //MASTER_S_THESIS_NETWORKINGSERVERCLASS_H
