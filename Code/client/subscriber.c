/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information. */
#define poll_freq 250
#include <stdio.h>
#include "open62541.h"

static UA_Boolean running = true;
static void stopHandler(int sig) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
}

static void
handler_TheAnswerChanged(UA_UInt32 monId, UA_DataValue *value, void *context) {
    UA_Int32 new_value = *(UA_Int32*)value->value.data;
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "The Answer is now %d!\n", new_value);
}

static void
handler_ThePumpChanged(UA_UInt32 monId, UA_DataValue *value, void *context) {
    UA_String *old_value = value->value.data;
    UA_String *new_value = UA_String_new();
    UA_String_copy(old_value, new_value);

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "What is the other answer? %s of course!\n", new_value->data);
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
    //1111111111111111111111111111111111111
    /* Create a subscription */
    UA_UInt32 subId = 0;
    UA_Client_Subscriptions_new(client, UA_SubscriptionSettings_default, &subId);
    if(subId)
        printf("Create subscription succeeded, id %u\n", subId);

    /* Add a MonitoredItem */
    UA_NodeId monitorThis = UA_NODEID_STRING(1, "the.answer");
    UA_UInt32 monId = 0;
    UA_Client_Subscriptions_addMonitoredItem(client, subId, monitorThis, UA_ATTRIBUTEID_VALUE,
                                             &handler_TheAnswerChanged, NULL, &monId, poll_freq);
    if (monId)
        printf("Monitoring 'the.answer', id %u\n", subId);
    //2222222222222222222222222222222222222
    /* Create another subscription */
    UA_UInt32 subId2 = 0;
    UA_Client_Subscriptions_new(client, UA_SubscriptionSettings_default, &subId2);
    if(subId2)
        printf("Create another subscription succeeded, id %u\n", subId2);

    /* Add another MonitoredItem */
    UA_NodeId monitorThis2 = UA_NODEID_STRING(1, "the.answer.2");
    UA_UInt32 monId2 = 0;
    UA_Client_Subscriptions_addMonitoredItem(client, subId2, monitorThis2, UA_ATTRIBUTEID_VALUE,
                                             &handler_ThePumpChanged, NULL, &monId2, poll_freq);
    if (monId2)
        printf("Monitoring 'the.answer.2', id %u\n", subId2);
    // -----------------------------------


    /* The first publish request should return the initial value of the variable */
    while (running)
        UA_Client_Subscriptions_manuallySendPublishRequest(client);

    /* Delete the subscription */
    if(!UA_Client_Subscriptions_remove(client, subId))
        printf("Subscription removed\n");

    /* Delete the subscription */
    if(!UA_Client_Subscriptions_remove(client, subId2))
        printf("Subscription removed\n");

    UA_Client_disconnect(client);
    UA_Client_delete(client);
    return (int) UA_STATUSCODE_GOOD;
}
