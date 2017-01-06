#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"
#include "ctemplate.h"
#include <winsock.h>
#include <mysql.h>

int cgiMain()
{
    cgiHeaderContentType("text/html;charset=gbk");
    TMPL_varlist *varlist = 0;
    TMPL_loop *varloop = 0;
    char* mysqlStr = "select name,password from t_users";
    char errorMsg[256] = {0};

    varlist = TMPL_add_var(varlist, "thead1", "√˚◊÷","thead2","√‹¬Î",0);
    MYSQL_RES *result = ExcuteSelect(mysqlStr,errorMsg);
    if(result == 0){
        varlist = TMPL_add_var(varlist,"errorMsg", "mysql”Ôæ‰÷¥–– ß∞‹£°", 0);
    } else {
        MYSQL_ROW row;
        while(row = mysql_fetch_row(result)){
            char* name = row[0];
            char* password = row[1];
            varloop = TMPL_add_varlist(varloop, TMPL_add_var(0, "name", name, "password", password, 0));
        }
        //varlist = TMPL_add_var("")
        varlist = TMPL_add_loop(varlist, "users", varloop);
    }
    mysql_free_result(result);
    TMPL_write("mysqlCgi1.html", 0, 0, varlist, cgiOut, cgiOut);
    return 0;
}
