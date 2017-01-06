#include <stdio.h>
#include <string.h>
#include <objbase.h>
#include "createGuid.h"

char* CreateGuid(){
    static char buffer[64] ={0};
    GUID guid;
    while(S_OK != CoCreateGuid(&guid)){}
    snprintf(buffer,sizeof(buffer),"{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}"
            , guid.Data1
            , guid.Data2
            , guid.Data3
            , guid.Data4[0], guid.Data4[1]
            , guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
            , guid.Data4[6], guid.Data4[7]);
    return buffer;
}
