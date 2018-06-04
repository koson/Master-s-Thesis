//
// Created by cgtybsr on 04.06.18.
//

#ifndef MASTER_S_THESIS_DISCOVERYSERVERCLASS_H
#define MASTER_S_THESIS_DISCOVERYSERVERCLASS_H

#include "open62541.h"
#include "commonServerMethods.h"


static UA_StatusCode
readInteger(UA_Server *server, const UA_NodeId *sessionId,
            void *sessionContext, const UA_NodeId *nodeId,
            void *nodeContext, UA_Boolean includeSourceTimeStamp,
            const UA_NumericRange *range, UA_DataValue *value) {
    UA_Int32 *myInteger = (UA_Int32*)nodeContext;
    value->hasValue = true;
    UA_Variant_setScalarCopy(&value->value, myInteger, &UA_TYPES[UA_TYPES_INT32]);

    // we know the nodeid is a string
    UA_LOG_INFO(logger, UA_LOGCATEGORY_USERLAND, "Node read %.*s",
                (int)nodeId->identifier.string.length,
                nodeId->identifier.string.data);
    UA_LOG_INFO(logger, UA_LOGCATEGORY_USERLAND,
                "read value %i", *(UA_UInt32 *)myInteger);
    return UA_STATUSCODE_GOOD;
}
static UA_StatusCode
writeInteger(UA_Server *server, const UA_NodeId *sessionId,
             void *sessionContext, const UA_NodeId *nodeId,
             void *nodeContext, const UA_NumericRange *range,
             const UA_DataValue *value) {
    UA_Int32 *myInteger = (UA_Int32*)nodeContext;
    if(value->hasValue && UA_Variant_isScalar(&value->value) &&
       value->value.type == &UA_TYPES[UA_TYPES_INT32] && value->value.data)
        *myInteger = *(UA_Int32 *)value->value.data;

    // we know the nodeid is a string
    UA_LOG_INFO(logger, UA_LOGCATEGORY_USERLAND, "Node written %.*s",
                (int)nodeId->identifier.string.length,
                nodeId->identifier.string.data);
    UA_LOG_INFO(logger, UA_LOGCATEGORY_USERLAND,
                "written value %i", *(UA_UInt32 *)myInteger);
    return UA_STATUSCODE_GOOD;
}
static UA_Server* setConfigDiscoveryServer(UA_Server *server){

    UA_ServerConfig *config = UA_ServerConfig_new_default();
    UA_String_deleteMembers(&config->applicationDescription.applicationUri);
    config->applicationDescription.applicationUri =
            UA_String_fromChars("urn:open62541.example.server_register");
    config->mdnsServerName = UA_String_fromChars("Sample Server");

    server = UA_Server_new(config);



    return  server;

}



#endif //MASTER_S_THESIS_DISCOVERYSERVERCLASS_H
