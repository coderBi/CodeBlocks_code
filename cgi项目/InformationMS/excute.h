#ifndef _EXCUTE_H_

#define _EXCUTE_H_
#include <winsock.h>
#include <mysql.h>

#endif // EXCUTE_H

char* ExcuteNoSelect(char * mysqlString,char* errorMsg);
MYSQL_RES* ExcuteSelect(char * mysqlString,char* errorMsg);
