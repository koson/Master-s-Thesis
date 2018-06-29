//
// Created by cgtybsr on 07.06.18.
//

#ifndef OPC_UA_TESTING_PLATFORM_ENCRYPTION_TEST_CLIENT_CLASS_H
#define OPC_UA_TESTING_PLATFORM_ENCRYPTION_TEST_CLIENT_CLASS_H

#include "open62541.h"
#include "commonClientMethods.h"

static void cleanupClient(UA_Client* client, UA_ByteString* remoteCertificate) {
    UA_ByteString_delete(remoteCertificate); /* Dereference the memory */
    UA_Client_delete(client); /* Disconnects the client internally */
}

UA_EndpointDescription *endPointArray = NULL;
size_t endPointArraySize = 0;
UA_ByteString *trustList = NULL;
size_t trustListSize = 0;
UA_ByteString *revocationList = NULL;
size_t revocationListSize = 0;
UA_ByteString certificate,privateKey,*remoteCertificate;


static void getEndPoints(){
    client = UA_Client_new(UA_ClientConfig_default);
    certificate = loadFile("../certificates/server_cert.der");
    privateKey = loadFile("../certificates/server_key.der");
    remoteCertificate = UA_ByteString_new();
    statusCode = UA_Client_getEndpoints(client, CONNECTION_STRING, &endPointArraySize, &endPointArray);
    if(statusCode != UA_STATUSCODE_GOOD) {
        UA_Array_delete(endPointArray, endPointArraySize,
                        &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);
        cleanupClient(client, remoteCertificate);
        UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"Could not get end points");

    }
}
static void getURLOfEndPoints(UA_String *string){
    printf("%i endpoints found\n", (int) endPointArraySize);
    for (size_t endPointCount = 0; endPointCount < endPointArraySize; endPointCount++) {
        printf("URL of endpoint %i is %.*s / %.*s\n", (int) endPointCount,
               (int) endPointArray[endPointCount].endpointUrl.length,
               endPointArray[endPointCount].endpointUrl.data,
               (int) endPointArray[endPointCount].securityPolicyUri.length,
               endPointArray[endPointCount].securityPolicyUri.data);

        if (endPointArray[endPointCount].securityMode != UA_MESSAGESECURITYMODE_SIGNANDENCRYPT)
            continue;

        if (UA_String_equal(&endPointArray[endPointCount].securityPolicyUri, &string)) {
            UA_ByteString_copy(&endPointArray[endPointCount].serverCertificate, remoteCertificate);
            break;
        }
    }
}

static void secureClientInitialization(UA_SecurityPolicy_Func securityPolicy){
    client = UA_Client_secure_new(UA_ClientConfig_default,
                                  certificate, privateKey,
                                  remoteCertificate,
                                  trustList, trustListSize,
                                  revocationList, revocationListSize,
                                  securityPolicy);
    if(client == NULL) {
        UA_ByteString_delete(remoteCertificate); /* Dereference the memory */
        UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"Could not connect to server");
    }
    UA_ByteString_deleteMembers(&certificate);
    UA_ByteString_deleteMembers(&privateKey);
    for(size_t deleteCount = 0; deleteCount < trustListSize; deleteCount++) {
        UA_ByteString_deleteMembers(&trustList[deleteCount]);
    }
}
static void establishConnection(){
    uint64_t start_time = get_milliseconds();
    statusCode = UA_Client_connect(client, CONNECTION_STRING);
    uint64_t end_time = get_milliseconds();
    printTimeDifference(start_time,end_time);
    if(statusCode != UA_STATUSCODE_GOOD) {
        cleanupClient(client, remoteCertificate);
        UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"Connection failed");

    }
}
static UA_StatusCode startbasic128rsa15Test() {
    UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"-----Starting Encryption Basic128rsa15 Test-------------------");
    getEndPoints();
    if(statusCode != UA_STATUSCODE_GOOD){
        return statusCode;
    }
    UA_String securityPolicyUri = UA_STRING("http://opcfoundation.org/UA/SecurityPolicy#Basic128Rsa15");
    getURLOfEndPoints(&securityPolicyUri);
    if(UA_ByteString_equal(remoteCertificate, &UA_BYTESTRING_NULL)) {
        UA_LOG_FATAL(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                     "Server does not support Security Basic128Rsa15 Mode of"
                     " UA_MESSAGESECURITYMODE_SIGNANDENCRYPT");
        cleanupClient(client, remoteCertificate);
    }
    UA_Array_delete(endPointArray, endPointArraySize,
                    &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);

    secureClientInitialization(UA_SecurityPolicy_Basic128Rsa15);
    establishConnection();
    UA_Client_delete(client);
    cleanupClient(client,remoteCertificate);
    UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"-----Ending Encryption Basic128rsa15 Test-------------------");
    return statusCode;
}

static UA_StatusCode startbasic256rsa256Test(){
    UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"-----Starting Encryption Basic256rsa256 Test------------------");
    getEndPoints();
    if(statusCode != UA_STATUSCODE_GOOD){
        return statusCode;
    }
    UA_String securityPolicyUri = UA_STRING("http://opcfoundation.org/UA/SecurityPolicy#Basic256Sha256");
    getURLOfEndPoints(&securityPolicyUri);
    if(UA_ByteString_equal(remoteCertificate, &UA_BYTESTRING_NULL)) {
        UA_LOG_FATAL(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                     "Server does not support Security Basic256Sha256 Mode of"
                     " UA_MESSAGESECURITYMODE_SIGNANDENCRYPT");
        cleanupClient(client, remoteCertificate);
    }
    UA_Array_delete(endPointArray, endPointArraySize,
                    &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);


    secureClientInitialization(UA_SecurityPolicy_Basic256Sha256);
    establishConnection();
    UA_Client_delete(client);
    cleanupClient(client,remoteCertificate);
    UA_LOG_INFO(logger,UA_LOGCATEGORY_CLIENT,"-----Ending Encryption Basic256rsa256 Test------------------");
    return statusCode;

}






#endif //OPC_UA_TESTING_PLATFORM_ENCRYPTION_TEST_CLIENT_CLASS_H
