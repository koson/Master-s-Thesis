#include <stdio.h>
#include "open62541.c"
#include "open62541.h"
#include <assert.h>


static void variables_basic(void){
      /* Int32 */
    UA_Int32 i = 5;
    UA_Int32 j;
    UA_Int32_copy(&i, &j);

    UA_Int32 *ip = UA_Int32_new();
    UA_Int32_copy(&i, ip);
    UA_Int32_delete(ip);

    /* String */
    UA_String s;
    UA_String_init(&s); /* _init zeroes out the entire memory of the datatype */
    char *test = "test";
    s.length = strlen(test);
    s.data = (UA_Byte*)test;

    UA_String s2;
    UA_String_copy(&s, &s2);
    UA_String_deleteMembers(&s2); /* Copying heap-allocated the dynamic content */

    UA_String s3 = UA_STRING("test2");
    UA_String s4 = UA_STRING_ALLOC("test2"); /* Copies the content to the heap */
    UA_Boolean eq = UA_String_equal(&s3, &s4);
    UA_String_deleteMembers(&s4);
    if(!eq)
        return;

    /* Structured Type */
    UA_CallRequest cr;
    UA_init(&cr, &UA_TYPES[UA_TYPES_CALLREQUEST]); /* Generic method */
    UA_CallRequest_init(&cr); /* Shorthand for the previous line */

    cr.requestHeader.timestamp = UA_DateTime_now(); /* Members of a structure */

    cr.methodsToCall = (UA_CallMethodRequest *)UA_Array_new(5, &UA_TYPES[UA_TYPES_CALLMETHODREQUEST]);
    cr.methodsToCallSize = 5; /* Array size needs to be made known */

    UA_CallRequest *cr2 = UA_CallRequest_new();
    UA_copy(&cr, cr2, &UA_TYPES[UA_TYPES_CALLREQUEST]);
    UA_CallRequest_deleteMembers(&cr);
    UA_CallRequest_delete(cr2);
}
static void
variables_nodeids(void) {
    UA_NodeId id1 = UA_NODEID_NUMERIC(1, 1234);
    id1.namespaceIndex = 3;

    UA_NodeId id2 = UA_NODEID_STRING(1, "testid"); /* the string is static */
    UA_Boolean eq = UA_NodeId_equal(&id1, &id2);
    if(eq)
        return;

    UA_NodeId id3;
    UA_NodeId_copy(&id2, &id3);
    UA_NodeId_deleteMembers(&id3);

    UA_NodeId id4 = UA_NODEID_STRING_ALLOC(1, "testid"); /* the string is copied
                                                            to the heap */
    UA_NodeId_deleteMembers(&id4);
}

static void
variables_variants(void) {
    /* Set a scalar value */
    UA_Variant v;
    UA_Int32 i = 42;
    UA_Variant_setScalar(&v, &i, &UA_TYPES[UA_TYPES_INT32]);

    /* Make a copy */
    UA_Variant v2;
    UA_Variant_copy(&v, &v2);
    UA_Variant_deleteMembers(&v2);

    /* Set an array value */
    UA_Variant v3;
    UA_Double d[9] = {1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0};
    UA_Variant_setArrayCopy(&v3, d, 9, &UA_TYPES[UA_TYPES_DOUBLE]);

    /* Set array dimensions */
    v3.arrayDimensions = (UA_UInt32 *)UA_Array_new(2, &UA_TYPES[UA_TYPES_UINT32]);
    v3.arrayDimensionsSize = 2;
    v3.arrayDimensions[0] = 3;
    v3.arrayDimensions[1] = 3;
    UA_Variant_deleteMembers(&v3);
}



int main(int argc, char **argv)
{
	variables_basic();
    variables_nodeids();
    variables_variants();
	return 0;
}
