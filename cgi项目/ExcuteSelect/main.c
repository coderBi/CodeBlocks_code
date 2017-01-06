#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <mysql.h>
#include <string.h>

int main()
{
    char errorMsg[256] = {0};
    char* sqlString1 = "update t_users set name = '¸Õ' where id = 5 or id = 7";
    char* sqlString2 = "select name, password from t_users where name = 'ÁõÏè'";
    MYSQL_RES* result = 0;
    if(strlen(ExcuteNoSelect(sqlString1,errorMsg)) != 0){
        printf("Óï¾äÖ´ÐÐ³ö´í:%s\n", errorMsg);
    }
    if((result = ExcuteSelect(sqlString2,errorMsg)) == 0){
        printf("Óï¾äÖ´ÐÐ³ö´í:%s\n", errorMsg);
    } else {
        MYSQL_ROW row;
        while(row = mysql_fetch_row(result)){
            char* name = row[0];
            char* password = row[1];
            printf("%s, %s\n", name,password);
        }
        mysql_free_result(result);
    }
    return 0;
}
