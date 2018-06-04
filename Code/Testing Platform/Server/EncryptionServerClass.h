//
// Created by cgtybsr on 03.06.18.
//

#ifndef MASTER_S_THESIS_ENCRYPTIONSERVERCLASS_H
#define MASTER_S_THESIS_ENCRYPTIONSERVERCLASS_H

#include "open62541.h"
#include "commonServerMethods.h"


static UA_ServerConfig * startEncryptionConfigurationBasic128rsa15(){

    UA_ByteString certificate = loadFile("../certificates/server_cert.der");
    UA_ByteString privateKey = loadFile("../certificates/server_key.der");
    size_t trustListSize = 0;
    UA_ByteString *revocationList = NULL;
    size_t revocationListSize = 0;
    UA_STACKARRAY(UA_ByteString, trustList, trustListSize);

    UA_ServerConfig *config = UA_ServerConfig_new_basic128rsa15(4840,&certificate,&privateKey,trustList,trustListSize,revocationList,revocationListSize);
    UA_ByteString_deleteMembers(&certificate);
    UA_ByteString_deleteMembers(&privateKey);
    for(size_t i = 0; i < trustListSize; i++)
        UA_ByteString_deleteMembers(&trustList[i]);

    return config;
}
static UA_ServerConfig * startEncryptionConfigurationBasic256sha256(){
    UA_ByteString certificate = loadFile("../certificates/server_cert.der");
    UA_ByteString privateKey = loadFile("../certificates/server_key.der");
    size_t trustListSize = 0;
    UA_ByteString *revocationList = NULL;
    size_t revocationListSize = 0;
    UA_STACKARRAY(UA_ByteString, trustList, trustListSize);

    UA_ServerConfig *config = UA_ServerConfig_new_basic256sha256(4840,&certificate,&privateKey,trustList,trustListSize,revocationList,revocationListSize);
    UA_ByteString_deleteMembers(&certificate);
    UA_ByteString_deleteMembers(&privateKey);
    for(size_t i = 0; i < trustListSize; i++)
        UA_ByteString_deleteMembers(&trustList[i]);

    return config;
}






#endif //MASTER_S_THESIS_ENCRYPTIONSERVERCLASS_H
