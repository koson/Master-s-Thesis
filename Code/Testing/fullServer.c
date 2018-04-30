#include <signal.h>
#include "open62541.h"

UA_Boolean running = true;
static void stopHandler(int sig) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
}

// Adding variables ------------------------------------------------------------------------
static void
addVariable(UA_Server *server) {
    /* Define the attribute of the myInteger variable node */
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Int32 myInteger = 43;
    UA_Variant_setScalar(&attr.value, &myInteger, &UA_TYPES[UA_TYPES_INT32]);
    attr.description = UA_LOCALIZEDTEXT("en-US","the answer, you should look for it");
    attr.displayName = UA_LOCALIZEDTEXT("en-US","the answer lies here");
    attr.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    /* Add the variable node to the information model */
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, "the.answer");          // these are both unique and can be used to
    UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME(1, "the answer");     // identify the variable right??
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_Server_addVariableNode(server, myIntegerNodeId, parentNodeId,
                              parentReferenceNodeId, myIntegerName,
                              UA_NODEID_NULL, attr, NULL, NULL);
}

static void
addVariableOther(UA_Server *server) {
    /* Define the attribute of the myInteger variable node */
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_String myStr = UA_STRING("2dpoint?");
    UA_Variant_setScalar(&attr.value, &myStr, &UA_TYPES[UA_TYPES_STRING]);
    attr.description = UA_LOCALIZEDTEXT("en-US","the other answer, you should look for it");
    attr.displayName = UA_LOCALIZEDTEXT("en-US","the other answer lies here");
    attr.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    /* Add the variable node to the information model */
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, "the.answer.2");          // these are both unique and can be used to
    UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME(1, "the answer 2");     // identify the variable right??
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_Server_addVariableNode(server, myIntegerNodeId, parentNodeId,
                              parentReferenceNodeId, myIntegerName,
                              UA_NODEID_NULL, attr, NULL, NULL);
}

/**
 * Now we change the value with the write service. This uses the same service
 * implementation that can also be reached over the network by an OPC UA client.
 */
static void
writeVariable(UA_Server *server) {
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, "the.answer");  // this is the id that I'm writing to, like a primary key

    /* Write a different integer value */
    UA_Int32 myInteger = 42;
    UA_Variant myVar;
    UA_Variant_init(&myVar);
    UA_Variant_setScalar(&myVar, &myInteger, &UA_TYPES[UA_TYPES_INT32]);    // save the variable to a variant
    UA_Server_writeValue(server, myIntegerNodeId, myVar);                   // write the variant to server with the nodid

    /* Set the status code of the value to an error code. The function
     * UA_Server_write provides access to the raw service. The above         <---- what does this mean ??
     * UA_Server_writeValue is syntactic sugar for writing a specific node
     * attribute with the write service. */
    UA_WriteValue wv;
    UA_WriteValue_init(&wv);
    wv.nodeId = myIntegerNodeId;
    wv.attributeId = UA_ATTRIBUTEID_VALUE;
    wv.value.status = UA_STATUSCODE_BADNOTCONNECTED;
    wv.value.hasStatus = true;
    UA_Server_write(server, &wv);

    /* Reset the variable to a good statuscode with a value */
    wv.value.hasStatus = false;
    wv.value.value = myVar;
    wv.value.hasValue = true;
    UA_Server_write(server, &wv);
}
// -----------------------------------------------------------------------------------------


// Data source -----------------------------------------------------------------------------
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
    UA_NodeId variableTypeNodeId = UA_NODEID_NULL;
    UA_Server_addVariableNode(server, currentNodeId, parentNodeId,
                              parentReferenceNodeId, currentName,
                              variableTypeNodeId, attr, NULL, NULL);

    updateCurrentTime(server);
}

/**
 * Variable Value Callback
 * ^^^^^^^^^^^^^^^^^^^^^^^
 * ?? so this only updates the value when someone tries to make a read request to the value?
 * When a value changes continuously, such as the system time, updating the
 * value in a tight loop would take up a lot of resources. Value callbacks allow
 * to synchronize a variable value with an external representation. They attach
 * callbacks to the variable that are executed before every read and after every
 * write operation. */

static void
beforeReadTime(UA_Server *server,
               const UA_NodeId *sessionId, void *sessionContext,
               const UA_NodeId *nodeid, void *nodeContext,
               const UA_NumericRange *range, const UA_DataValue *data) {
    UA_DateTime now = UA_DateTime_now();
    UA_Variant value;
    UA_Variant_setScalar(&value, &now, &UA_TYPES[UA_TYPES_DATETIME]);
    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "current-time");
    UA_Server_writeValue(server, currentNodeId, value);
}

static void
afterWriteTime(UA_Server *server,
               const UA_NodeId *sessionId, void *sessionContext,
               const UA_NodeId *nodeId, void *nodeContext,
               const UA_NumericRange *range, const UA_DataValue *data) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                "The 'current-time' variable was updated");
}

static void
addValueCallbackToCurrentTimeVariable(UA_Server *server) {
    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "current-time");
    UA_ValueCallback callback ;
    callback.onRead = beforeReadTime;
    callback.onWrite = afterWriteTime;
    UA_Server_setVariableNode_valueCallback(server, currentNodeId, callback);
}

/**
 * Variable Data Sources
 * ^^^^^^^^^^^^^^^^^^^^^
 *
 * With value callbacks, the value is still stored in the variable node.
 * So-called data sources go one step further. The server redirects every read
 * and write request to a callback function. Upon reading, the callback provides
 * copy of the current value. Internally, the data source needs to implement its
 * own memory management. */

static UA_StatusCode
readCurrentTime(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                UA_DataValue *dataValue) {
    UA_DateTime now = UA_DateTime_now();
    UA_Variant_setScalarCopy(&dataValue->value, &now,
                             &UA_TYPES[UA_TYPES_DATETIME]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

static UA_StatusCode
writeCurrentTime(UA_Server *server,
                 const UA_NodeId *sessionId, void *sessionContext,
                 const UA_NodeId *nodeId, void *nodeContext,
                 const UA_NumericRange *range, const UA_DataValue *data) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                "Changing the system time is not implemented");
    return UA_STATUSCODE_BADINTERNALERROR;
}

static void
addCurrentTimeDataSourceVariable(UA_Server *server) {
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "Current time - data source");
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "current-time-datasource");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "current-time-datasource");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NULL;

    UA_DataSource timeDataSource;
    timeDataSource.read = readCurrentTime;
    timeDataSource.write = writeCurrentTime;
    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
                                        parentReferenceNodeId, currentName,
                                        variableTypeNodeId, attr,
                                        timeDataSource, NULL, NULL);
}
// -----------------------------------------------------------------------------------------

// Variable types --------------------------------------------------------------------------
static UA_NodeId pointTypeId;

static void
addVariableType2DPoint(UA_Server *server) {
    UA_VariableTypeAttributes vtAttr = UA_VariableTypeAttributes_default;
    vtAttr.dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
    vtAttr.valueRank = 1; /* array with one dimension */
    UA_UInt32 arrayDims[1] = {2};
    vtAttr.arrayDimensions = arrayDims;
    vtAttr.arrayDimensionsSize = 1;
    vtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "2DPoint Type");

    /* a matching default value is required */
    UA_Double zero[2] = {0.0, 0.0};
    UA_Variant_setArray(&vtAttr.value, zero, 2, &UA_TYPES[UA_TYPES_DOUBLE]);

    UA_Server_addVariableTypeNode(server, UA_NODEID_NULL,
                                  UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                  UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                  UA_QUALIFIEDNAME(1, "2DPoint Type"), UA_NODEID_NULL,
                                  vtAttr, NULL, &pointTypeId);
}

/**
 * Now the new variable type for *2DPoint* can be referenced during the creation
 * of a new variable. If no value is given, the default from the variable type
 * is copied during instantiation.
 */

static UA_NodeId pointVariableId;

static void
addVariable2(UA_Server *server) {
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

/**
 * The constraints of the variable type are enforced when writing the datatype,
 * valuerank and arraydimensions attributes of the variable. This, in turn,
 * constrains the value attribute of the variable. */

static void
writeVariable2(UA_Server *server) {
    UA_StatusCode retval = UA_Server_writeValueRank(server, pointVariableId, 0);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                "Setting the Value Rank failed with Status Code %s",
                UA_StatusCode_name(retval));

}
// -----------------------------------------------------------------------------------------

// Working with objects and object types ---------------------------------------------------
/**
 * Working with Objects and Object Types
 * -------------------------------------
 *
 * Using objects to structure information models
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * Assume a situation where we want to model a set of pumps and their runtime
 * state in an OPC UA information model. Of course, all pump representations
 * should follow the same basic structure, For example, we might have graphical
 * representation of pumps in a SCADA visualisation that shall be resuable for
 * all pumps.
 *
 * Following the object-oriented programming paradigm, every pump is represented
 * by an object with the following layout:
 *
 * .. graphviz::
 *
 *    digraph tree {
 *
 *    fixedsize=true;
 *    node [width=2, height=0, shape=box, fillcolor="#E5E5E5", concentrate=true]
 *
 *    node_root [label=< <I>ObjectNode</I><BR/>Pump >]
 *
 *    { rank=same
 *      point_1 [shape=point]
 *      node_1 [label=< <I>VariableNode</I><BR/>ManufacturerName >] }
 *    node_root -> point_1 [arrowhead=none]
 *    point_1 -> node_1 [label="hasComponent"]
 *
 *    { rank=same
 *      point_2 [shape=point]
 *      node_2 [label=< <I>VariableNode</I><BR/>ModelName >] }
 *    point_1 -> point_2 [arrowhead=none]
 *    point_2 -> node_2 [label="hasComponent"]
 *
 *    {  rank=same
 *       point_4 [shape=point]
 *       node_4 [label=< <I>VariableNode</I><BR/>Status >] }
 *    point_2 -> point_4 [arrowhead=none]
 *    point_4 -> node_4 [label="hasComponent"]
 *
 *    {  rank=same
 *       point_5 [shape=point]
 *       node_5 [label=< <I>VariableNode</I><BR/>MotorRPM >] }
 *    point_4 -> point_5 [arrowhead=none]
 *    point_5 -> node_5 [label="hasComponent"]
 *
 *    }
 *
 * The following code manually defines a pump and its member variables. We omit
 * setting constraints on the variable values as this is not the focus of this
 * tutorial and was already covered. */

#include <signal.h>
#include "open62541.h"

static void
manuallyDefinePump(UA_Server *server) {
    UA_NodeId pumpId; /* get the nodeid assigned by the server */
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Pump (Manual)");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "Pump (Manual)"), UA_NODEID_NULL,
                            oAttr, NULL, &pumpId);

    UA_VariableAttributes mnAttr = UA_VariableAttributes_default;
    UA_String manufacturerName = UA_STRING("Pump King Ltd.");
    UA_Variant_setScalar(&mnAttr.value, &manufacturerName, &UA_TYPES[UA_TYPES_STRING]);
    mnAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ManufacturerName");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "ManufacturerName"),
                              UA_NODEID_NULL, mnAttr, NULL, NULL);

    UA_VariableAttributes modelAttr = UA_VariableAttributes_default;
    UA_String modelName = UA_STRING("Mega Pump 3000");
    UA_Variant_setScalar(&modelAttr.value, &modelName, &UA_TYPES[UA_TYPES_STRING]);
    modelAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ModelName");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "ModelName"),
                              UA_NODEID_NULL, modelAttr, NULL, NULL);

    UA_VariableAttributes statusAttr = UA_VariableAttributes_default;
    UA_Boolean status = true;
    UA_Variant_setScalar(&statusAttr.value, &status, &UA_TYPES[UA_TYPES_BOOLEAN]);
    statusAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Status");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "Status"),
                              UA_NODEID_NULL, statusAttr, NULL, NULL);

    UA_VariableAttributes rpmAttr = UA_VariableAttributes_default;
    UA_Double rpm = 50.0;
    UA_Variant_setScalar(&rpmAttr.value, &rpm, &UA_TYPES[UA_TYPES_DOUBLE]);
    rpmAttr.displayName = UA_LOCALIZEDTEXT("en-US", "MotorRPM");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "MotorRPMs"),
                              UA_NODEID_NULL, rpmAttr, NULL, NULL);
}

/**
 * Object types, type hierarchies and instantiation
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * Building up each object manually requires us to write a lot of code.
 * Furthermore, there is no way for clients to detect that an object represents
 * a pump. (We might use naming conventions or similar to detect pumps. But
 * that's not exactly a clean solution.) Furthermore, we might have more devices
 * than just pumps. And we require all devices to share some common structure.
 * The solution is to define ObjectTypes in a hierarchy with inheritance
 * relations.
 *
 * .. graphviz::
 *
 *    digraph tree {
 *
 *    fixedsize=true;
 *    node [width=2, height=0, shape=box, fillcolor="#E5E5E5", concentrate=true]
 *
 *    node_root [label=< <I>ObjectTypeNode</I><BR/>Device >]
 *
 *    { rank=same
 *      point_1 [shape=point]
 *      node_1 [label=< <I>VariableNode</I><BR/>ManufacturerName<BR/>(mandatory) >] }
 *    node_root -> point_1 [arrowhead=none]
 *    point_1 -> node_1 [label="hasComponent"]
 *
 *    { rank=same
 *      point_2 [shape=point]
 *      node_2 [label=< <I>VariableNode</I><BR/>ModelName >] }
 *    point_1 -> point_2 [arrowhead=none]
 *    point_2 -> node_2 [label="hasComponent"]
 *
 *    {  rank=same
 *       point_3 [shape=point]
 *       node_3 [label=< <I>ObjectTypeNode</I><BR/>Pump >] }
 *    point_2 -> point_3 [arrowhead=none]
 *    point_3 -> node_3 [label="hasSubtype"]
 *
 *    {  rank=same
 *       point_4 [shape=point]
 *       node_4 [label=< <I>VariableNode</I><BR/>Status<BR/>(mandatory) >] }
 *    node_3 -> point_4 [arrowhead=none]
 *    point_4 -> node_4 [label="hasComponent"]
 *
 *    {  rank=same
 *       point_5 [shape=point]
 *       node_5 [label=< <I>VariableNode</I><BR/>MotorRPM >] }
 *    point_4 -> point_5 [arrowhead=none]
 *    point_5 -> node_5 [label="hasComponent"]
 *
 *    }
 *
 * Children that are marked mandatory are automatically instantiated together
 * with the parent object. This is indicated by a `hasModellingRule` reference
 * to an object that representes the `mandatory` modelling rule. */

/* predefined identifier for later use */
UA_NodeId pumpTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1001}};

static void
defineObjectTypes(UA_Server *server) {
    /* Define the object type for "Device" */
    UA_NodeId deviceTypeId; /* get the nodeid assigned by the server */
    UA_ObjectTypeAttributes dtAttr = UA_ObjectTypeAttributes_default;
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "DeviceType");
    UA_Server_addObjectTypeNode(server, UA_NODEID_NULL,
                                UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                                UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(1, "DeviceType"), dtAttr,
                                NULL, &deviceTypeId);

    UA_VariableAttributes mnAttr = UA_VariableAttributes_default;
    mnAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ManufacturerName");
    UA_NodeId manufacturerNameId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, deviceTypeId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "ManufacturerName"),
                              UA_NODEID_NULL, mnAttr, NULL, &manufacturerNameId);
    /* Make the manufacturer name mandatory */
    UA_Server_addReference(server, manufacturerNameId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);


    UA_VariableAttributes modelAttr = UA_VariableAttributes_default;
    modelAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ModelName");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, deviceTypeId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "ModelName"),
                              UA_NODEID_NULL, modelAttr, NULL, NULL);

    /* Define the object type for "Pump" */
    UA_ObjectTypeAttributes ptAttr = UA_ObjectTypeAttributes_default;
    ptAttr.displayName = UA_LOCALIZEDTEXT("en-US", "PumpType");
    UA_Server_addObjectTypeNode(server, pumpTypeId,
                                deviceTypeId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                UA_QUALIFIEDNAME(1, "PumpType"), ptAttr,
                                NULL, NULL);

    UA_VariableAttributes statusAttr = UA_VariableAttributes_default;
    statusAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Status");
    statusAttr.valueRank = -1;
    UA_NodeId statusId;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpTypeId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "Status"),
                              UA_NODEID_NULL, statusAttr, NULL, &statusId);
    /* Make the status variable mandatory */
    UA_Server_addReference(server, statusId,
                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                           UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY), true);

    UA_VariableAttributes rpmAttr = UA_VariableAttributes_default;
    rpmAttr.displayName = UA_LOCALIZEDTEXT("en-US", "MotorRPM");
    rpmAttr.valueRank = -1;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, pumpTypeId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "MotorRPMs"),
                              UA_NODEID_NULL, rpmAttr, NULL, NULL);
}

/**
 * Now we add the derived ObjectType for the pump that inherits from the device
 * object type. The resulting object contains all mandatory child variables.
 * These are simply copied over from the object type. The object has a reference
 * of type ``hasTypeDefinition`` to the object type, so that clients can detect
 * the type-instance relation at runtime.
 */

static void
addPumpObjectInstance(UA_Server *server, char *name) {
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", name);
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, name),
                            pumpTypeId, /* this refers to the object type
                                           identifier */
                            oAttr, NULL, NULL);
}

/**
 * Often times, we want to run a constructor function on a new object. This is
 * especially useful when an object is instantiated at runtime (with the
 * AddNodes service) and the integration with an underlying process canot?? be
 * manually defined. In the following constructor example, we simply set the
 * pump status to on.
 */

static UA_StatusCode
pumpTypeConstructor(UA_Server *server, const UA_NodeId *sessionId, void *sessionContext, const UA_NodeId *typeId, void *typeContext, const UA_NodeId *nodeId, void **nodeContext) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "New pump created");

    /* Find the NodeId of the status child variable */
    UA_RelativePathElement rpe;
    UA_RelativePathElement_init(&rpe);
    rpe.referenceTypeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT);
    rpe.isInverse = false;
    rpe.includeSubtypes = false;
    rpe.targetName = UA_QUALIFIEDNAME(1, "Status");

    UA_BrowsePath bp;
    UA_BrowsePath_init(&bp);
    bp.startingNode = *nodeId;
    bp.relativePath.elementsSize = 1;
    bp.relativePath.elements = &rpe;

    UA_BrowsePathResult bpr =
            UA_Server_translateBrowsePathToNodeIds(server, &bp);
    if(bpr.statusCode != UA_STATUSCODE_GOOD ||
       bpr.targetsSize < 1)
        return bpr.statusCode;

    /* Set the status value */
    UA_Boolean status = true;
    UA_Variant value;
    UA_Variant_setScalar(&value, &status, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, value);
    UA_BrowsePathResult_deleteMembers(&bpr);

    /* At this point we could replace the node context .. */

    return UA_STATUSCODE_GOOD;
}

static void
addPumpTypeConstructor(UA_Server *server) {
    UA_NodeTypeLifecycle lifecycle;
    lifecycle.constructor = pumpTypeConstructor;
    lifecycle.destructor = NULL;
    UA_Server_setNodeTypeLifecycle(server, pumpTypeId, lifecycle);
}

// -----------------------------------------------------------------------------------------

// Adding methods to objects ---------------------------------------------------------------
static UA_StatusCode
strEchoMethodCallback(UA_Server *server,
                      const UA_NodeId *sessionId, void *sessionHandle,
                      const UA_NodeId *methodId, void *methodContext,
                      const UA_NodeId *objectId, void *objectContext,
                      size_t inputSize, const UA_Variant *input,
                      size_t outputSize, UA_Variant *output) {
    UA_Variant_setScalarCopy(output, (UA_String*)input->data, &UA_TYPES[UA_TYPES_STRING]);
    //UA_String_deleteMembers(&tmp);
    //UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Hello World was called");
    return UA_STATUSCODE_GOOD;
}

static UA_StatusCode
strAckMethodCallback(UA_Server *server,
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

static void
addEchoMethod(UA_Server *server) {
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

static void
addAckMethod(UA_Server *server) {
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



/**
 * Increase Array Values Method
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * The method takes an array of 5 integers and a scalar as input. It returns a
 * copy of the array with every entry increased by the scalar. */

static UA_StatusCode
IncInt32ArrayMethodCallback(UA_Server *server,
                            const UA_NodeId *sessionId, void *sessionContext,
                            const UA_NodeId *methodId, void *methodContext,
                            const UA_NodeId *objectId, void *objectContext,
                            size_t inputSize, const UA_Variant *input,
                            size_t outputSize, UA_Variant *output) {
    UA_Int32 *inputArray = (UA_Int32*)input[0].data;
    UA_Int32 delta = *(UA_Int32*)input[1].data;

    /* Copy the input array */
    UA_StatusCode retval = UA_Variant_setArrayCopy(output, inputArray, 5,
                                                   &UA_TYPES[UA_TYPES_INT32]);
    if(retval != UA_STATUSCODE_GOOD)
        return retval;

    /* Increate the elements */
    UA_Int32 *outputArray = (UA_Int32*)output->data;
    for(size_t i = 0; i < input->arrayLength; i++)
        outputArray[i] = inputArray[i] + delta;

    return UA_STATUSCODE_GOOD;
}

static void
addIncInt32ArrayMethod(UA_Server *server) {
    /* Two input arguments */
    UA_Argument inputArguments[2];
    UA_Argument_init(&inputArguments[0]);
    inputArguments[0].description = UA_LOCALIZEDTEXT("en-US", "int32[5] array");
    inputArguments[0].name = UA_STRING("int32 array");
    inputArguments[0].dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    inputArguments[0].valueRank = 1;
    UA_UInt32 pInputDimension = 5;
    inputArguments[0].arrayDimensionsSize = 1;
    inputArguments[0].arrayDimensions = &pInputDimension;

    UA_Argument_init(&inputArguments[1]);
    inputArguments[1].description = UA_LOCALIZEDTEXT("en-US", "int32 delta");
    inputArguments[1].name = UA_STRING("int32 delta");
    inputArguments[1].dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    inputArguments[1].valueRank = -1; /* scalar */

    /* One output argument */
    UA_Argument outputArgument;
    UA_Argument_init(&outputArgument);
    outputArgument.description = UA_LOCALIZEDTEXT("en-US", "int32[5] array");
    outputArgument.name = UA_STRING("each entry is incremented by the delta");
    outputArgument.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    outputArgument.valueRank = 1;
    UA_UInt32 pOutputDimension = 5;
    outputArgument.arrayDimensionsSize = 1;
    outputArgument.arrayDimensions = &pOutputDimension;

    /* Add the method node */
    UA_MethodAttributes incAttr = UA_MethodAttributes_default;
    incAttr.description = UA_LOCALIZEDTEXT("en-US", "IncInt32ArrayValues");
    incAttr.displayName = UA_LOCALIZEDTEXT("en-US", "IncInt32ArrayValues");
    incAttr.executable = true;
    incAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_STRING(1, "IncInt32ArrayValues"),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                            UA_QUALIFIEDNAME(1, "IncInt32ArrayValues"),
                            incAttr, &IncInt32ArrayMethodCallback,
                            2, inputArguments, 1, &outputArgument,
                            NULL, NULL);
}
// -----------------------------------------------------------------------------------------

// Benchmarking ----------------------------------------------------------------------------
UA_ByteString dataPackage;


static UA_StatusCode
setDataSizeMethodCallback(UA_Server *server,
                          const UA_NodeId *sessionId, void *sessionHandle,
                          const UA_NodeId *methodId, void *methodContext,
                          const UA_NodeId *objectId, void *objectContext,
                          size_t inputSize, const UA_Variant *input,
                          size_t outputSize, UA_Variant *output) {
    UA_UInt32 *newSize = (UA_UInt32 *)input->data;

    if (dataPackage.length > 0)
        UA_ByteString_deleteMembers(&dataPackage);

    UA_ByteString_allocBuffer(&dataPackage, (*newSize)*1024);
    for (size_t i=0; i<dataPackage.length; i++)
        dataPackage.data[i] = (UA_Byte) rand();

    return UA_STATUSCODE_GOOD;
}

static void
addSetDataSizeMethod(UA_Server *server) {
    UA_Argument inputArgument;
    UA_Argument_init(&inputArgument);
    inputArgument.description = UA_LOCALIZEDTEXT("en-US", "Desired package size in KB");
    inputArgument.name = UA_STRING("Size");
    inputArgument.dataType = UA_TYPES[UA_TYPES_UINT32].typeId;
    inputArgument.valueRank = -1; /* scalar */

    UA_MethodAttributes helloAttr = UA_MethodAttributes_default;
    helloAttr.description = UA_LOCALIZEDTEXT("en-US","Say `Hello World`");
    helloAttr.displayName = UA_LOCALIZEDTEXT("en-US","Hello World");
    helloAttr.executable = true;
    helloAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1,6000),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
                            UA_QUALIFIEDNAME(1, "setSize"),
                            helloAttr, &setDataSizeMethodCallback,
                            1, &inputArgument,0, NULL, NULL, NULL);
}

static UA_StatusCode
getDataMethodCallback(UA_Server *server,
                      const UA_NodeId *sessionId, void *sessionHandle,
                      const UA_NodeId *methodId, void *methodContext,
                      const UA_NodeId *objectId, void *objectContext,
                      size_t inputSize, const UA_Variant *input,
                      size_t outputSize, UA_Variant *output) {
    UA_Variant_setScalarCopy(output, &dataPackage, &UA_TYPES[UA_TYPES_BYTESTRING]);
    //UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Sending data");
    return UA_STATUSCODE_GOOD;
}

static void
addGetDataMethod(UA_Server *server) {
    UA_Argument outputArgument;
    UA_Argument_init(&outputArgument);
    outputArgument.description = UA_LOCALIZEDTEXT("en-US", "The Data");
    outputArgument.name = UA_STRING("data");
    outputArgument.dataType = UA_TYPES[UA_TYPES_BYTESTRING].typeId;
    outputArgument.valueRank = -1; /* scalar */

    UA_MethodAttributes helloAttr = UA_MethodAttributes_default;
    helloAttr.description = UA_LOCALIZEDTEXT("en-US","Get the data from the server");
    helloAttr.displayName = UA_LOCALIZEDTEXT("en-US","getData");
    helloAttr.executable = true;
    helloAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1,6001),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
                            UA_QUALIFIEDNAME(1, "getData"),
                            helloAttr, &getDataMethodCallback,
                            0, NULL, 1, &outputArgument, NULL, NULL);
}
// -----------------------------------------------------------------------------------------
int main(void) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    UA_ServerConfig *config = UA_ServerConfig_new_default();
    UA_Server *server = UA_Server_new(config);
    // For Benchmarking ------------------------------------------------------------------------
    addSetDataSizeMethod(server);
    addGetDataMethod(server);
    // -----------------------------------------------------------------------------------------

    // Server instantiation --------------------------------------------------------------------
    {
        /* Create a rudimentary objectType
         *
         * BaseObjectType
         * |
         * +- (OT) MamalType    id=10000
         *    + (V) age         id=10001
         *    + (OT) DogType    id=10002
         *      |
         *      + (V) Name      id=10003
         *    + (OT) CatType    id=10004
         *      |
         *      + (V) Name      id=10005
         */
        UA_ObjectTypeAttributes otAttr = UA_ObjectTypeAttributes_default;
        otAttr.description = UA_LOCALIZEDTEXT("en-US", "A mamal");
        otAttr.displayName = UA_LOCALIZEDTEXT("en-US", "MamalType");
        UA_Server_addObjectTypeNode(server, UA_NODEID_NUMERIC(1, 10000),
                                    UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                                    UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                    UA_QUALIFIEDNAME(1, "MamalType"), otAttr, NULL, NULL);

        UA_VariableAttributes vAttr = UA_VariableAttributes_default;
        vAttr.description =  UA_LOCALIZEDTEXT("en-US", "This mamals Age in months");
        vAttr.displayName =  UA_LOCALIZEDTEXT("en-US", "Age");
        UA_UInt32 ageVar = 0;
        UA_Variant_setScalar(&vAttr.value, &ageVar, &UA_TYPES[UA_TYPES_UINT32]);
        UA_Server_addVariableNode(server, UA_NODEID_NUMERIC(1, 10001),
                                  UA_NODEID_NUMERIC(1, 10000), UA_NODEID_NUMERIC(0, UA_NS0ID_HASPROPERTY),
                                  UA_QUALIFIEDNAME(1, "Age"), UA_NODEID_NULL, vAttr, NULL, NULL);
        // Dog subtype
        otAttr = UA_ObjectTypeAttributes_default;
        otAttr.description = UA_LOCALIZEDTEXT("en-US", "A dog, subtype of mamal");
        otAttr.displayName = UA_LOCALIZEDTEXT("en-US", "DogType");
        UA_Server_addObjectTypeNode(server, UA_NODEID_NUMERIC(1, 10002),
                                    UA_NODEID_NUMERIC(1, 10000), UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                    UA_QUALIFIEDNAME(1, "DogType"), otAttr, NULL, NULL);

        vAttr = UA_VariableAttributes_default;
        vAttr.description =  UA_LOCALIZEDTEXT("en-US", "This mamals Name");
        vAttr.displayName =  UA_LOCALIZEDTEXT("en-US", "Name");
        UA_String defaultDogName = UA_STRING("unnamed dog");
        UA_Variant_setScalar(&vAttr.value, &defaultDogName, &UA_TYPES[UA_TYPES_STRING]);
        UA_Server_addVariableNode(server, UA_NODEID_NUMERIC(1, 10003),
                                  UA_NODEID_NUMERIC(1, 10002), UA_NODEID_NUMERIC(0, UA_NS0ID_HASPROPERTY),
                                  UA_QUALIFIEDNAME(1, "Name"), UA_NODEID_NULL, vAttr, NULL, NULL);

        // Cat subtype
        otAttr = UA_ObjectTypeAttributes_default;
        otAttr.description = UA_LOCALIZEDTEXT("en-US", "A cat, subtype of mamal");
        otAttr.displayName = UA_LOCALIZEDTEXT("en-US", "CatType");
        UA_Server_addObjectTypeNode(server, UA_NODEID_NUMERIC(1, 10004),
                                    UA_NODEID_NUMERIC(1, 10000), UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                    UA_QUALIFIEDNAME(1, "CatType"), otAttr, NULL, NULL);

        vAttr = UA_VariableAttributes_default;
        vAttr.description =  UA_LOCALIZEDTEXT("en-US", "This mamals Name");
        vAttr.displayName =  UA_LOCALIZEDTEXT("en-US", "Name");
        UA_String defaultCatName = UA_STRING("unnamed cat");
        UA_Variant_setScalar(&vAttr.value, &defaultCatName, &UA_TYPES[UA_TYPES_STRING]);
        UA_Server_addVariableNode(server, UA_NODEID_NUMERIC(1, 10005),
                                  UA_NODEID_NUMERIC(1, 10004), UA_NODEID_NUMERIC(0, UA_NS0ID_HASPROPERTY),
                                  UA_QUALIFIEDNAME(1, "Name"), UA_NODEID_NULL, vAttr, NULL, NULL);

        /* Instatiate a dog named bello:
         * (O) Objects
         *   + O Bello <DogType>
         *     + Age
         *     + Name
         */
        UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;                // where is the age defined
        oAttr.description = UA_LOCALIZEDTEXT("en-US", "A dog named Bello");
        oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Bello");
        UA_Server_addObjectNode(server, UA_NODEID_NUMERIC(1, 0),
                                UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),   // ??
                                UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),    // ??
                                UA_QUALIFIEDNAME(1, "Bello"), UA_NODEID_NUMERIC(1, 10002),
                                oAttr, NULL, NULL);

        /* Instatiate a cat named garfield:
         * (O) Objects
         *   + O Garfield <DogType>
         *     + Age
         *     + Name
         */
        oAttr = UA_ObjectAttributes_default;                // where is the age defined
        oAttr.description = UA_LOCALIZEDTEXT("en-US", "A cat named Garfield");
        oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Garfield");
        UA_Server_addObjectNode(server, UA_NODEID_NUMERIC(1, 0),
                                UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),   // ??
                                UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),    // ??
                                UA_QUALIFIEDNAME(1, "Garfield"), UA_NODEID_NUMERIC(1, 10004),
                                oAttr, NULL, NULL);
    }
    // -----------------------------------------------------------------------------------------

    // Adding variables ------------------------------------------------------------------------
    {
        addVariable(server);
        addVariableOther(server);
        writeVariable(server);
    }
    // -----------------------------------------------------------------------------------------

    // Data source -----------------------------------------------------------------------------
    {
        addCurrentTimeVariable(server);
        addValueCallbackToCurrentTimeVariable(server);
        addCurrentTimeDataSourceVariable(server);
    }
    // -----------------------------------------------------------------------------------------

    // Variable types --------------------------------------------------------------------------
    {
        addVariableType2DPoint(server);
        addVariable2(server);
        writeVariable2(server);
    }
    // -----------------------------------------------------------------------------------------

    // Working with objects and object types --------------------------------------------------
    {
        manuallyDefinePump(server);
        defineObjectTypes(server);
        addPumpObjectInstance(server, "pump2");
        addPumpObjectInstance(server, "pump3");
        addPumpTypeConstructor(server);
        addPumpObjectInstance(server, "pump4");
        addPumpObjectInstance(server, "pump5");
    }
    // -----------------------------------------------------------------------------------------

    // Adding methods to objects ---------------------------------------------------------------
    {
        addEchoMethod(server);
        addAckMethod(server);
        addIncInt32ArrayMethod(server);
    }
    // -----------------------------------------------------------------------------------------

    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    return (int)retval;
}