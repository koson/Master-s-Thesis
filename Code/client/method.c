/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information. */

#include <stdio.h>
#include "open62541.h"

static void
callMethod(UA_Client *client){
    /* Call a remote method */
    UA_Variant input;
    UA_String argString = UA_STRING("Server!");
    UA_Variant_init(&input);
    UA_Variant_setScalarCopy(&input, &argString, &UA_TYPES[UA_TYPES_STRING]);
    size_t outputSize;
    UA_Variant *output;
    UA_StatusCode retval = UA_Client_call(client, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(1, 62541), 1, &input, &outputSize, &output);
    if(retval == UA_STATUSCODE_GOOD) {
        printf("Method call was successfull, and %lu returned values available.\n",
               (unsigned long)outputSize);
        printf("And that output is: %s", ((UA_String *)output->data)->data);
        UA_Array_delete(output, outputSize, &UA_TYPES[UA_TYPES_VARIANT]);
    } else {
        printf("Method call was unsuccessfull, and %x returned values available.\n", retval);
    }
    UA_Variant_deleteMembers(&input);
}

int main(int argc, char *argv[]) {
    UA_Client *client = UA_Client_new(UA_ClientConfig_default);

    /* Connect to a server */
    /* anonymous connect would be: retval = UA_Client_connect(client, "opc.tcp://localhost:4840"); */
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://192.168.20.125:4840");
    if(retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        return (int)retval;
    }

    callMethod(client);

    UA_Client_disconnect(client);
    UA_Client_delete(client);
    return (int) UA_STATUSCODE_GOOD;
}
