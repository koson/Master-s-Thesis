////
//// Created by cgtybsr on 27.04.18.
////

#include <stdio.h>
#include "../open62541.h"
#include "../commonTestingMethods.h"
#include <time.h>



static void perform_single_value_method_call(UA_Int32 id){
    UA_Client *client = UA_Client_new(UA_ClientConfig_default);
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://10.200.2.14:4840");
    UA_Variant *output;
    size_t outputSize;

        if(retval != UA_STATUSCODE_GOOD) {
       UA_Client_delete(client);
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Could not connect");
            return;
    }
     nodeId = UA_NODEID_STRING(1,"single_value_method");
    parentNodeId =  UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    objectId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    methodId = UA_NODEID_STRING(1, "single_value_method");
    uint64_t start= get_milliseconds();
    UA_Client_call(client,objectId,methodId,0,NULL,&outputSize,&output);
    uint64_t  end = get_milliseconds();
    printTimeDifference(start,end);
}



int main()
{

    int i;
    printf("------Starting Multiple Clients Single Value Test-----\n");

    for(i=1;i < 20; i++){
        perform_single_value_method_call(i);

    }
    printf("------Ending Multiple Clients Single Value Test-----\n");


    /* Clean up */
    return 0;

}

//    printf("------Starting Multiple Clients Multiple Value Test-----\n");
//
//    for(i=1;i <6; i++){
//        printf("For Client: %d\n",i);
//        printf("Multiple Value Method Call");
//        perform_multiple_value_method_call(&elapsed_time);
//        printf("Elapsed Time: %lld\n",elapsed_time);
//    }
//    printf("------Ending Multiple Clients Multiple Value Test-----\n");



// test_case_time = get_seconds();
//  perform_method_call(&elapsed_time);
//   total_time += elapsed_time;
//  printf("Elapsed time: %lld \n",(total_time)/1000);
//   printf("Test case time: %d \n",test_case_time);
// after = get_milliseconds();
// *elapsed_time = (long long int) (after - before);


/* Read the value attribute of the node. UA_Client_readValueAttribute is a
 * wrapper for the raw read service available as UA_Client_Service_read. */


//#include "open62541.h"
//#include <stdio.h>
//#include <time.h>
//#include <math.h>
//#define time_per_test 30
//#define progress_resolution 500
//struct timespec ts, ts2;
//uint64_t get_milliseconds(){
//    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
//    return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
//}
//// -Method to get second resolution timestamp
//uint64_t get_seconds(){
//    clock_gettime(CLOCK_MONOTONIC_RAW, &ts2);
//    return ts2.tv_sec;
//}
//
//
//
//
//
//
//
//int main(void) {
//    printf("------Starting Single Value Test-----\n");
//    UA_Client *client = UA_Client_new(UA_ClientConfig_default);
//    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://192.168.178.59:4840");
//    if(retval != UA_STATUSCODE_GOOD) {
//        UA_Client_delete(client);
//        return (int)retval;
//    }
//
//    /* Read the value attribute of the node. UA_Client_readValueAttribute is a
//     * wrapper for the raw read service available as UA_Client_Service_read. */
//    UA_Variant value; /* Variants can hold scalar values and arrays of any type */
//    UA_Variant_init(&value);
//
//    const UA_NodeId ua_nodeId = UA_NODEID_NUMERIC(1,12345);
//    UA_StatusCode statusCode = UA_Client_readValueAttribute(client,ua_nodeId,&value);
//    if(statusCode ==UA_STATUSCODE_GOOD){
//
//        UA_LOG_INFO(UA_Log_Stdout,UA_LOGCATEGORY_USERLAND,&value);
//
//        printf("%s",value);
//    }
//    else
//        printf("Problem \n");
//
//
//    /* NodeId of the variable holding the current time */
//    const UA_NodeId nodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER_SERVERSTATUS_CURRENTTIME);
//    retval = UA_Client_readValueAttribute(client, nodeId, &value);
//
//    if(retval == UA_STATUSCODE_GOOD &&
//       UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_DATETIME])) {
//        UA_DateTime raw_date = *(UA_DateTime *) value.data;
//        UA_DateTimeStruct dts = UA_DateTime_toStruct(raw_date);
//        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "date is: %u-%u-%u %u:%u:%u.%03u\n",
//                    dts.day, dts.month, dts.year, dts.hour, dts.min, dts.sec, dts.milliSec);
//    }
//
//    /* Clean up */
//    UA_Variant_deleteMembers(&value);
//    UA_Client_delete(client); /* Disconnects the client internally */
//    return UA_STATUSCODE_GOOD;
//}
//
//
//
//
////static void perform_method_call(UA_Client *client,long long int* elapsed_time){
////    __time_t before, after;
////    UA_StatusCode retval;
////    UA_Variant *output;
////
////    before = get_milliseconds();
////    UA_Client_call(client,UA_NODEID_NUMERIC(0,UA_NS0ID_OBJECTSFOLDER)
////            ,UA_NODEID_NUMERIC(1,12345),0,NULL,1,&output);
////    after = get_milliseconds();
////    if(retval == UA_STATUSCODE_GOOD) {
////        printf("Method call was successfull, and %lu returned values available.\n", (unsigned long)1);
////        printf("returned value is of length: %d\n", ((int)((UA_String *) output->data)->length) - 6);
////        UA_Array_delete(output, 1, &UA_TYPES[UA_TYPES_VARIANT]);
////    } else {
////        printf("Method call was unsuccessfull, and %x returned values available.\n", retval);
////    }
////
////    *elapsed_time = (long long int) (after - before);
////
////
////}
////
////
////
////int main(int argc,char *argv[]){
////
////    UA_Client *client = UA_Client_new(UA_ClientConfig_default);
////    UA_StatusCode statusCode = UA_Client_connect(client,"opc.tcp://192.168.178.59:4840");
////
////
////    int num_reqs, test_case_time;
////    long long int total_time,elapsed_time;
////    double rtt;
////    /* For printing progress in a single line with dots */
////    setbuf(stdout, NULL);
////
////
////    struct timespec wait_time;
////    total_time = 0;
////    test_case_time = get_seconds();
////    for(num_reqs = 0; get_seconds() - test_case_time < time_per_test; num_reqs++){
////        printf(".");  // this time we print a dot for every request
////        /* wait between 0-5 seconds */
////        wait_time.tv_sec = rand() % 5;
////        wait_time.tv_nsec = rand() % 1000000000;
////        nanosleep(&wait_time, NULL);
////        perform_method_call(client, &elapsed_time);
////        total_time += elapsed_time;
////    }
////}