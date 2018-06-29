//
// Created by cgtybsr on 07.06.18.
//
#include "headers/Networking_Test_Client_Class.h"
#include "headers/CPU_Test_Client_Class.h"
#include "headers/commonClientMethods.h"
#include "headers/Discovery_Test_Client_Class.h"
#include <open62541.h>
//#include "Encryption_Test_Client_Class.h"

static void getResult(UA_StatusCode statusCode){
    if(statusCode != UA_STATUSCODE_GOOD){
        UA_LOG_FATAL(logger,UA_LOGCATEGORY_CLIENT,"Test Failed");
    }
}

int main(){

    getResult(startNetworkingTest());
    getResult(startGettingSingleValueTest());
    getResult(startGettingMultipleValueTest());
    getResult(startGettingMultipleCustomObjectTest());
    getResult(startWritingValueTest());
    getResult(startSortingTest());
    getResult(startFindServersOnNetworkTest());
//    getResult(startbasic128rsa15Test());
//    getResult(startbasic256rsa256Test());


}

