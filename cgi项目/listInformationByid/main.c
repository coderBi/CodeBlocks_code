#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"
#include "ctemplate.h"
#include <string.h>

int cgiMain()
{
    cgiHeaderContentType("text/html;charset=gbk");
    TMPL_varlist *varlist = 0;
    TMPL_loop *varloop = 0;
    char id[10] = {0};

    if(cgiFormString("id", id, sizeof(id)) != cgiFormSuccess){
        fprintf(cgiOut,"没有提供任何班级id！");
        return 0;
    }
    varlist = TMPL_add_var(varlist,"thead1", "姓名", "thead2", "学号", 0);
    if(strcmp(id, "1") == 0){
        varloop = TMPL_add_varlist(varloop, TMPL_add_var(0, "name", "小明", "id", "11", 0));
        varloop = TMPL_add_varlist(varloop, TMPL_add_var(0, "name", "张三", "id", "12", 0));
        varloop = TMPL_add_varlist(varloop, TMPL_add_var(0, "name", "李四", "id", "13", 0));
    } else if(strcmp(id, "2") == 0) {
        varloop = TMPL_add_varlist(varloop, TMPL_add_var(0, "name", "李世明", "id", "21", 0));
        varloop = TMPL_add_varlist(varloop, TMPL_add_var(0, "name", "赵匡胤", "id", "22", 0));
        varloop = TMPL_add_varlist(varloop, TMPL_add_var(0, "name", "朱元璋", "id", "23", 0));
    } else {
        fprintf(cgiOut,"无此班级");
    }
    varlist = TMPL_add_loop(varlist, "students", varloop);
    TMPL_write("listInformationByid.html", 0, 0, varlist, cgiOut, cgiOut);
    return 0;
}
