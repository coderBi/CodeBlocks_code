#include <stdio.h>
#include <stdlib.h>
#include "excute.h"
#include <winsock.h>
#include <mysql.h>
#include <string.h>

char* ConnectDB(MYSQL *mysql,char* errorMsg);

char* ExcuteNoSelect(char * mysqlString,char* errorMsg){
    MYSQL *mysql = mysql_init(0);
    if(strlen(ConnectDB(mysql,errorMsg)) != 0){
        goto end;
    }
    if(mysql_query(mysql, mysqlString)){
        strcpy(errorMsg, mysql_error(mysql));
        goto end;
    }
end:
    mysql_close(mysql);
    return errorMsg;
}

MYSQL_RES* ExcuteSelect(char * mysqlString,char* errorMsg){
    MYSQL *mysql = mysql_init(0);
    MYSQL_RES *result = 0;
    if(strlen(ConnectDB(mysql,errorMsg)) != 0){
        goto end;
    }
    if(mysql_query(mysql, mysqlString)){
        strcpy(errorMsg, mysql_error(mysql));
        goto end;
    }
    result = mysql_store_result(mysql);
end:
    mysql_close(mysql);
    return result;
}

char* ConnectDB(MYSQL *mysql,char* errorMsg){
    if(!mysql_real_connect(mysql, "localhost", "root", "256356", "study1", 0, 0, 0)){
        strcpy(errorMsg, mysql_error(mysql));
    }
    if(mysql_query(mysql, "set names gbk")){
        strcpy(errorMsg, mysql_error(mysql));
    }
    return errorMsg;
}
