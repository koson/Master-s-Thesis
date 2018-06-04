
#include <stdio.h>
#include <signal.h>
#include "open62541.h"
#include "open62541.c"

static UA_NodeId pointTypeId;
static UA_NodeId pointVariableId;
UA_Boolean running = true;
//VariableTypeNode to the hierarchy of variable types.
static void addVariableType2DPoint(UA_Server *server){
UA_VariableTypeAttributes variableTypeAttr = UA_VariableTypeAttributes_default;
variableTypeAttr.dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
variableTypeAttr.valueRank =1;
UA_UInt32 arrayDims[1]={2};
variableTypeAttr.arrayDimensions = arrayDims;
variableTypeAttr.arrayDimensionsSize = 1;
variableTypeAttr.displayName = UA_LOCALIZEDTEXT("en-US","2D Point Type");

UA_Double zero[2] = {0.0,0.0};
UA_Variant_setArray(&variableTypeAttr,zero,2,&UA_TYPES[UA_TYPES_DOUBLE]);
UA_Server_addVariableTypeNode(server,UA_NODEID_NULL,UA_NODEID_NUMERIC(0,UA_NS0ID_BASEDATAVARIABLETYPE),UA_NODEID_NUMERIC(0,UA_NS0ID_HASSUBTYPE),
UA_QUALIFIEDNAME(1,"2d Point Type"),UA_NODEID_NULL,variableTypeAttr,NULL,&pointTypeId);


}

//new variable type for 2DPoint can be referenced during the creation of a new variable.
static void addVariable(UA_Server *server) {
    /* Prepare the node attributes */
    UA_VariableAttributes vAttr = UA_VariableAttributes_default;
    vAttr.dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
    vAttr.valueRank = 1; /* array with one dimension */
    UA_UInt32 arrayDims[1] = {2};
    vAttr.arrayDimensions = arrayDims;
    vAttr.arrayDimensionsSize = 1;
    vAttr.displayName = UA_LOCALIZEDTEXT("en-US", "2DPoint Variable");
    vAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    /* vAttr.value is left empty, the server instantiates with the default value */

    /* Add the node */
    UA_Server_addVariableNode(server, UA_NODEID_NULL,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "2DPoint Type"), pointTypeId,
                              vAttr, NULL, &pointVariableId);
}
//The constraints of the variable type are enforced when creating new variable instances of the type.
//In the following function, adding a variable of 2DPoint type with a string value fails because The value does not match the variable type constraints.
static void addVariableFail(UA_Server *server) {
    /* Prepare the node attributes */
    UA_VariableAttributes vAttr = UA_VariableAttributes_default;
    vAttr.dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
    vAttr.valueRank = -1; /* a scalar. this is not allowed per the variable type */
    vAttr.displayName = UA_LOCALIZEDTEXT("en-US", "2DPoint Variable (fail)");
    UA_String s = UA_STRING("2dpoint?");
    UA_Variant_setScalar(&vAttr.value, &s, &UA_TYPES[UA_TYPES_STRING]);

    /* Add the node will return UA_STATUSCODE_BADTYPEMISMATCH*/
    UA_Server_addVariableNode(server, UA_NODEID_NULL,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "2DPoint Type (fail)"), pointTypeId,
                              vAttr, NULL, NULL);
}
//The constraints of the variable type are enforced when writing the datatype, valuerank and arraydimensions attributes of the variable.
//This, in turn, constrains the value attribute of the variable.
static void writeVariable(UA_Server *server) {
    UA_StatusCode retval = UA_Server_writeValueRank(server, pointVariableId, 0);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                "Setting the Value Rank failed with Status Code %s",
                UA_StatusCode_name(retval));

}
//It follows the main server code, making use of the above definitions.
static void stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}

int main(void) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    UA_ServerConfig *config = UA_ServerConfig_new_default();
    UA_Server *server = UA_Server_new(config);

    addVariableType2DPoint(server);
    addVariable(server);
    addVariableFail(server);
    writeVariable(server);

    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    return (int)retval;
}
