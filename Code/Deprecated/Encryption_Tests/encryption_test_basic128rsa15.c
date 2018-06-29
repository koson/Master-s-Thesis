#include <stdio.h>
#include <errno.h> // errno, EINTR
#include <stdlib.h>
#include "../../Testing_Platform/Client/open62541.h"
#include "../../Testing_Platform/Client/commonClientMethods.h"
#include <time.h>


#define CONNECTION_STRING "opc.tcp://10.200.2.14:4840"
#define time_per_test 30
#define progress_resolution 500

UA_Client *client;
UA_StatusCode retval;
// -Method to get millisecond resolution timestamp
struct timespec ts, ts2;
uint64_t get_milliseconds(){
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}
// -Method to get second resolution timestamp
uint64_t get_seconds(){
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts2);
    return ts2.tv_sec;
}
static void cleanUpClient(UA_ByteString *removeCertificate){

    UA_ByteString_delete(removeCertificate);
    UA_Client_delete(client);
}

static void setNormalClient(){
 client = UA_Client_new(UA_ClientConfig_default);
    retval = UA_Client_connect(client,CONNECTION_STRING );
    if(retval != UA_STATUSCODE_GOOD)
    {
        UA_LOG_INFO(logger,UA_LOGCATEGORY_USERLAND,"Error creating Raw Client");
        UA_Client_delete(client);
    } else
        UA_LOG_INFO(logger,UA_LOGCATEGORY_USERLAND,"Raw Client is created!");
}


static void setEncryptedClient(){
    client = UA_Client_new(UA_ClientConfig_default);
    UA_ByteString certificate = loadFile("../certificates/server_cert.der");
    UA_ByteString privateKey = loadFile("../certificates/server_key.der");
    UA_EndpointDescription * endPointArray =NULL;
    size_t endPointArraySize =0;
    UA_ByteString *trustList          = NULL;
    size_t trustListSize      = 0;
    UA_ByteString *revocationList     = NULL;
    size_t revocationListSize = 0;
    UA_ByteString *remoteCertificate = UA_ByteString_new();
    retval = UA_Client_getEndpoints(client,CONNECTION_STRING,&endPointArraySize,&endPointArray);

    if(retval != UA_STATUSCODE_GOOD){
        UA_Array_delete(endPointArray,endPointArraySize,&UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);
        UA_LOG_INFO(logger,UA_LOGCATEGORY_USERLAND,"Error getting end points");
        char str[12];
        UA_LOG_INFO(logger,UA_LOGCATEGORY_USERLAND,sprintf(str, "%d", retval));
        cleanUpClient(remoteCertificate);
    }
    UA_String securityPolicyUri = UA_STRING("http://opcfoundation.org/UA/SecurityPolicy#Basic256Sha256");
    printf("%i endpoints found\n", (int)endPointArraySize);
    for(size_t endPointCount=0;endPointCount<endPointArraySize;endPointCount++){
        printf("URL of endpoint %i is %.*s / %.*s\n", (int)endPointCount,
               (int)endPointArray[endPointCount].endpointUrl.length,
               endPointArray[endPointCount].endpointUrl.data,
               (int)endPointArray[endPointCount].securityPolicyUri.length,
               endPointArray[endPointCount].securityPolicyUri.data);

        if(endPointArray[endPointCount].securityMode != UA_MESSAGESECURITYMODE_SIGNANDENCRYPT)
            continue;

        if(UA_String_equal(&endPointArray[endPointCount].securityPolicyUri, &securityPolicyUri)) {
            UA_ByteString_copy(&endPointArray[endPointCount].serverCertificate, remoteCertificate);
            break;
        }
    }
    if(UA_ByteString_equal(remoteCertificate, &UA_BYTESTRING_NULL)) {
        UA_LOG_FATAL(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                     "Server does not support Security Basic256Sha256 Mode of"
                             " UA_MESSAGESECURITYMODE_SIGNANDENCRYPT");
        cleanUpClient(remoteCertificate);

    }
    client = UA_Client_secure_new(UA_ClientConfig_default,
                                  certificate, privateKey,
                                  remoteCertificate,
                                  trustList, trustListSize,
                                  revocationList, revocationListSize,
                                  UA_SecurityPolicy_Basic256Sha256);
    if(client == NULL) {
        UA_ByteString_delete(remoteCertificate); /* Dereference the memory */
        UA_LOG_INFO(logger,UA_LOGCATEGORY_USERLAND,"Client can not started");
    }
    UA_ByteString_deleteMembers(&certificate);
    UA_ByteString_deleteMembers(&privateKey);
    for(size_t deleteCount = 0; deleteCount < trustListSize; deleteCount++) {
        UA_ByteString_deleteMembers(&trustList[deleteCount]);
    }

    /* Secure client connect */
    retval = UA_Client_connect(client, CONNECTION_STRING);
    if(retval != UA_STATUSCODE_GOOD) {
        cleanUpClient(remoteCertificate);
        UA_LOG_INFO(logger,UA_LOGCATEGORY_USERLAND,"Client can not started");

    }

}



static void perform_call(UA_Client *client, UA_String arg, long long int* elapsed_time, bool echo){
    /* Call a remote method */
    __time_t before, after;
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
        printf("Method call was successfull, and %lu returned values available.\n", (unsigned long)outputSize);
        printf("returned value is of length: %d\n", ((int)((UA_String *) output->data)->length) - 6);
        UA_Array_delete(output, outputSize, &UA_TYPES[UA_TYPES_VARIANT]);
    } else {
        printf("Method call was unsuccessfull, and %x returned values available.\n", retval);
    }
    UA_Variant_deleteMembers(&input);
}

static void startTesting(){
    int num_reqs, test_case_time;
    long long int total_time;
    double rtt;
    long long int elapsed_time;
    UA_Byte arr[600000];
    for(int i = 0; i < sizeof(arr); i++){arr[i] = '*';}
    UA_String argString = {.data = &arr[0], .length = 1};
    /* For printing progress in a single line with dots */
    setbuf(stdout, NULL);
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
        perform_call(client, argString, &elapsed_time, true);
        total_time += elapsed_time;
    }
    printf(" (%d requests made)", num_reqs);
    rtt = total_time / 1000.0 / num_reqs;
    printf("\nvariable requests average rtt/request=%.2f\n\n", rtt);
}



int main(void){

    printf("---------Testing with Raw Connection-----------------");
    setNormalClient();
    startTesting();
    printf("---------Testing with Secure Connection--------------");
    setEncryptedClient();
    startTesting();
    UA_Client_disconnect(client);
    UA_Client_delete(client);
    return (int) UA_STATUSCODE_GOOD;
}