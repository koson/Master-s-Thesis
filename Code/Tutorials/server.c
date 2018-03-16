#include <stdio.h>
#include "open62541.h"
#include "open62541.c"
#include  <signal.h>
 
UA_Boolean running = true;
static void stopHandler(int signalType){
    UA_LOG_INFO(UA_Log_Stdout,UA_LOGCATEGORY_USERLAND,"received ctrl-c");
    running = false;
}



int main(int argc, char **argv)
{
    signal(SIGINT,stopHandler);
    signal(SIGTERM,stopHandler);
    UA_ServerConfig *config = UA_ServerConfig_new_default();
    UA_Server *server = UA_Server_new(config);
    
    UA_StatusCode statusCode=UA_Server_run(server,&running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    
    
	//printf("hello world\n");
	return (int)statusCode;
}
