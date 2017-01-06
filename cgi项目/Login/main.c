#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"
#include "ctemplate.h"
#include <string.h>

int cgiMain()
{
    cgiHeaderContentType("text/html;charse=gbk");
    char name[256] = {0}, *_name = "bww";
    char pwd[256] = {0}, *_pwd = "123";
    char errorMsg[256] = {0};
    TMPL_varlist *varlist = 0;
    if(cgiFormSubmitClicked("login") == cgiFormSuccess){
        if(cgiFormSuccess != cgiFormString("name", name, sizeof(name))){
            strcpy(errorMsg, "ÇëÌîÐ´ÓÃ»§Ãû£¡");
        }
        if(cgiFormSuccess != cgiFormString("pwd", pwd, sizeof(pwd))){
            if(strlen(errorMsg) == 0){
                strcpy(errorMsg, "ÇëÌîÐ´ÃÜÂë£¡");
            }
        }
        if(strlen(errorMsg) == 0 && strcmp(name, _name) == 0 && strcmp(pwd, _pwd) == 0){
            fprintf(cgiOut,"µÇÂ½³É¹¦£¡");
            return 0;
        } else {
            if(strlen(errorMsg) == 0){
                strcpy(errorMsg, "ÓÃ»§Ãû»òÃÜÂë´íÎó£¡");
            }
            varlist = TMPL_add_var(varlist, "name", name, "pwd", pwd, "errorMsg", errorMsg, 0);
        }
    } else {
        varlist = TMPL_add_var(varlist, "name", "", "pwd", "", "errorMsg", "", 0);
    }
    TMPL_write("login.html", 0, 0,varlist, cgiOut, cgiOut);
    return 0;
}
