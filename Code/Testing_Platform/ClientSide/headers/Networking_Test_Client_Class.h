//
// Created by cgtybsr on 07.06.18.
//

#ifndef OPC_UA_TESTING_PLATFORM_NETWORKING_TEST_CLIENT_CLASS_H
#define OPC_UA_TESTING_PLATFORM_NETWORKING_TEST_CLIENT_CLASS_H
#define time_per_test 30  // 30 second per test case
#define progress_resolution 500  // every 500 requests represented by 1 dot
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "open62541.h"
#include "commonClientMethods.h"



static void methodCall(UA_Client *client, UA_String arg, long long int* elapsed_time, bool echo){
    /* Call a remote method */
    __time_t before, after;
    UA_StatusCode retval;
    UA_Variant input;
    UA_Variant_init(&input);
    UA_Variant_setScalarCopy(&input, &arg, &UA_TYPES[UA_TYPES_STRING]);
    size_t outputSize;
    UA_Variant *output;
    before = get_milliseconds();
    if (echo){
        retval = UA_Client_call(client, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                                UA_NODEID_NUMERIC(1, 62541), 1, &input, &outputSize, &output);
    } else {
        retval = UA_Client_call(client, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                                UA_NODEID_NUMERIC(1, 62542), 1, &input, &outputSize, &output);
    }
    after = get_milliseconds();
    *elapsed_time = (long long int) (after - before);
    if(retval == UA_STATUSCODE_GOOD) {
        //printf("Method call was successfull, and %lu returned values available.\n", (unsigned long)outputSize);
        //printf("returned value is of length: %d\n", ((int)((UA_String *) output->data)->length) - 6);
        UA_Array_delete(output, outputSize, &UA_TYPES[UA_TYPES_VARIANT]);
    } else {
        printf("Method call was unsuccessfull, and %x returned values available.\n", retval);
    }
    UA_Variant_deleteMembers(&input);
}







static UA_StatusCode startNetworkingTest(){
    UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"-----Starting Networking Test-------------------");
    statusCode =  initializeConnection();
    if(statusCode != UA_STATUSCODE_GOOD){
        return statusCode;
    }
    // intialize the large string that will be used for the function calls and set every char to '*'
    UA_Byte mainString[600000];
    for(int i = 0; i < sizeof(mainString); i++){mainString[i] = '*';}
    // init. the struct that will be sent to the server, and the variable that will hold the elapsed time for each call
    UA_String argString = {.data = &mainString[0], .length = 1};
    long long int elapsed_time;
    // create a new client
    UA_Client *client = UA_Client_new(UA_ClientConfig_default);
    // Connect to a server
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://10.200.2.14:4840");
    if(retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        return retval;
    }
    /* Init general purpose variables that will be used by all tests */
    int num_reqs, test_case_time;
    long long int total_time;
    double rtt;
    /* For printing progress in a single line with dots */
    setbuf(stdout, NULL);


    /* ----------------------------------------------------------
                Testing for non-homogeneous workloads
       ---------------------------------------------------------- */
    argString.length = 4;  // let's try with a workload that is ignorable
    struct timespec wait_time;
    total_time = 0;
    test_case_time = get_seconds();
    srand (1); // initialize random seed, to generate same random behavior on all tests
    printf("testing");
    for(num_reqs = 0; get_seconds() - test_case_time < time_per_test; num_reqs++){
        printf(".");  // this time we print a dot for every request
        /* wait between 0-5 seconds */
        wait_time.tv_sec = rand() % 5;
        wait_time.tv_nsec = rand() % 1000000000;
        nanosleep(&wait_time, NULL);
        methodCall(client, argString, &elapsed_time, true);
        total_time += elapsed_time;
    }
    printf(" (%d requests made)", num_reqs);
    rtt = total_time / 1000.0 / num_reqs;
    printf("\nvariable requests average rtt/request=%.2f\n\n", rtt);
    // ----------------------------------------------------------

    /* ----------------------------------------------------------
                Testing throughput when echoing
       ---------------------------------------------------------- */
    for(size_t str_len=2; str_len < pow(2, 20); str_len *= 2){
        argString.length = str_len;
        total_time = 0;
        test_case_time = get_seconds();
        printf("testing");
        for (num_reqs = 0; get_seconds() - test_case_time < time_per_test; num_reqs++){
            if (num_reqs % progress_resolution == 0){ printf("."); }
            methodCall(client, argString, &elapsed_time, true);
            total_time += elapsed_time;
            //printf("%.2f\n", elapsed_time / 1000.0);
        }
        printf(" (%d requests made)\n", num_reqs);
        rtt = total_time / 1000.0 / num_reqs;
        printf("echo_str %6ld average rtt/request=%.2f\n",           str_len, rtt);
        printf("echo_str %6ld messages/s=%.2f\n",                    str_len, 1000.0 / rtt);
        printf("echo_str %6ld %.2f kB/s (bidirectional sum)\n\n",    str_len, 2.0 * str_len / rtt);
    }
    // ----------------------------------------------------------

    /* ----------------------------------------------------------
                Testing throughput without echoing
       ---------------------------------------------------------- */
    for(size_t str_len=2; str_len < pow(2, 20); str_len *= 2){
        argString.length = str_len;
        total_time = 0;
        test_case_time = get_seconds();
        printf("testing");
        for (num_reqs = 0; get_seconds() - test_case_time < time_per_test; num_reqs++){
            if (num_reqs % progress_resolution == 0){ printf("."); }
            methodCall(client, argString, &elapsed_time, false);
            total_time += elapsed_time;
            //printf("%.2f\n", elapsed_time / 1000.0);
        }
        printf(" (%d requests made)\n", num_reqs);
        rtt = total_time / 1000.0 / num_reqs;
        printf("ack_str %6ld average rtt/request=%.2f\n",            str_len, rtt);
        printf("ack_str %6ld messages/s=%.2f\n",                     str_len, 1000.0 / rtt);
        printf("ack_str %6ld %.2f kB/s (one direction)\n\n",         str_len, 1.0 * str_len / rtt);
    }
    // ----------------------------------------------------------

    // bye bye
    UA_Client_disconnect(client);
    UA_Client_delete(client);
    UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"-----Ending Networking Test-------------------");
    return (int) UA_STATUSCODE_GOOD;

}








#endif //OPC_UA_TESTING_PLATFORM_NETWORKING_TEST_CLIENT_CLASS_H
