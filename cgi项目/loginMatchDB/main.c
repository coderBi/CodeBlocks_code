#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"
#include "ctemplate.h"
#include <string.h>
#include <winsock.h>
#include <mysql.h>
#include "excute.h"

int cgiMain()
{
    cgiHeaderContentType("text/html;charse=gbk");
    char name[256] = {0};
    char pwd[256] = {0};
    char errorMsg[256] = {0};
    TMPL_varlist *varlist = 0;
    if(cgiFormSubmitClicked("login") == cgiFormSuccess){
        if(cgiFormSuccess != cgiFormString("name", name, sizeof(name))){
            strcpy(errorMsg, "����д�û�����");
        }
        if(cgiFormSuccess != cgiFormString("pwd", pwd, sizeof(pwd))){
            if(strlen(errorMsg) == 0){
                strcpy(errorMsg, "����д���룡");
            }
        }
        if(strlen(errorMsg) == 0){
            char mysqlStr[1024] = {0};
            sprintf(mysqlStr, "select name, password from t_users where name='%s' and password='%s'",name, pwd);
            MYSQL_RES *result = ExcuteSelect(mysqlStr,errorMsg);
            if(result == 0){
               strcpy(errorMsg, "���ݿ�����ʧ�ܣ�");
            } else {
                if(mysql_num_rows(result) != 0){
                    fprintf(cgiOut,"��½�ɹ���");
                    return 0;
                } else {
                    strcpy(errorMsg, "�û������������");
                }
            }
        }
        varlist = TMPL_add_var(varlist, "name", name, "pwd", pwd, "errorMsg", errorMsg, 0);
    } else {
        varlist = TMPL_add_var(varlist, "name", "", "pwd", "", "errorMsg", "", 0);
    }
    TMPL_write("login.html", 0, 0,varlist, cgiOut, cgiOut);
    return 0;
}
