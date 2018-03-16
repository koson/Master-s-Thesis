//
// Created by ayhun on 01/02/18.
//
/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information. */
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "open62541.h"

#define num_tries 1000
// -Method to get millisecond resolution timestamp
struct timespec ts;
__time_t
get_time(){
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}

static void
echo_str(UA_Client *client, UA_String arg, long long int* elapsed_time){
    /* Call a remote method */
    __time_t before, after;
    UA_Variant input;
    UA_Variant_init(&input);
    UA_Variant_setScalarCopy(&input, &arg, &UA_TYPES[UA_TYPES_STRING]);
    size_t outputSize;
    UA_Variant *output;
    before = get_time();
    UA_StatusCode retval = UA_Client_call(client, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                                          UA_NODEID_NUMERIC(1, 62541), 1, &input, &outputSize, &output);
    after = get_time();
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

int main(int argc, char *argv[]) {
    // intialize the large string that will be used for the function calls and set every char to '*'
    UA_Byte mainString[600000];
    for(int i = 0; i < sizeof(mainString); i++){mainString[i] = '*';}
    // init. the struct that will be sent to the server, and the variable that will hold the elapsed time for each call
    UA_String argString = {.data = &mainString[0], .length = 1};
    long long int elapsed_time;
    // create a new client
    UA_Client *client = UA_Client_new(UA_ClientConfig_default);
    // Connect to a server
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://raspberrypi:4840");
    if(retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        return (int)retval;
    }
    long long int total_time;
    double rtt;
    // Run the echo string test with strings that are exponentially increasing in size
    for(size_t str_len=1; str_len < pow(2, 20); str_len *= 2){
        argString.length = str_len;
        total_time = 0;
        for(int i = 0; i < num_tries; i++) {
            echo_str(client, argString, &elapsed_time);
            total_time += elapsed_time;
            //printf("%.2f\n", elapsed_time / 1000.0);
        }
        rtt = total_time / 1000.0 / num_tries;
        printf("echo_str %6zu average rtt/request=%.2f\n", str_len, rtt);
        printf("echo_str %6zu messages/s=%.2f\n", str_len, 1000.0 / rtt);
        printf("echo_str %6zu kbps=%.2f\n\n", str_len, 2.0 * str_len / rtt);
    }

    // bye bye
    UA_Client_disconnect(client);
    UA_Client_delete(client);
    return (int) UA_STATUSCODE_GOOD;
}