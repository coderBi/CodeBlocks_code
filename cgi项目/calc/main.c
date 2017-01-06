#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"
#include "ctemplate.h"
#include <string.h>

int cgiMain()
{
    TMPL_varlist *varlist = 0;
    char num1[256] = {0};
    char num2[256] = {0};
    char num3[256] = {0};
    cgiHeaderContentType("text/html;charset=gbk");
    if(cgiFormSubmitClicked("calc") == cgiFormSuccess){
        char errorMsg[256] = {0};
        if(cgiFormString("num1", num1, sizeof(num1)) != cgiFormSuccess){
            strcpy(errorMsg, "第一位数字没有输入");
        }
        if(cgiFormString("num2", num2, sizeof(num2)) != cgiFormSuccess){
            if(strlen(errorMsg) == 0){
                strcpy(errorMsg, "第二位数字没有输入");
            }
        }
        if(strlen(errorMsg) != 0){
            varlist = TMPL_add_var(varlist, "num1", num1, "num2", num2, "num3", "", "errorMsg", errorMsg, 0);
        } else {
            int res = atoi(num1) + atoi(num2);
            itoa(res, num3, 10);
            varlist = TMPL_add_var(varlist, "num1", num1, "num2", num2, "num3", num3, "errorMsg", errorMsg, 0);
        }
    } else {
        varlist = TMPL_add_var(0, "num1", "", "num2", "", num3, "", "errorMsg", "", 0);
    }

    TMPL_write("calc.html", 0, 0, varlist, cgiOut, cgiOut);
    return 0;
}
