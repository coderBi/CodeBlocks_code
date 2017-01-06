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
        fprintf(cgiOut,"û���ṩ�κΰ༶id��");
        return 0;
    }
    varlist = TMPL_add_var(varlist,"thead1", "����", "thead2", "ѧ��", 0);
    if(strcmp(id, "1") == 0){
        varloop = TMPL_add_varlist(varloop, TMPL_add_var(0, "name", "С��", "id", "11", 0));
        varloop = TMPL_add_varlist(varloop, TMPL_add_var(0, "name", "����", "id", "12", 0));
        varloop = TMPL_add_varlist(varloop, TMPL_add_var(0, "name", "����", "id", "13", 0));
    } else if(strcmp(id, "2") == 0) {
        varloop = TMPL_add_varlist(varloop, TMPL_add_var(0, "name", "������", "id", "21", 0));
        varloop = TMPL_add_varlist(varloop, TMPL_add_var(0, "name", "�Կ�ط", "id", "22", 0));
        varloop = TMPL_add_varlist(varloop, TMPL_add_var(0, "name", "��Ԫ�", "id", "23", 0));
    } else {
        fprintf(cgiOut,"�޴˰༶");
    }
    varlist = TMPL_add_loop(varlist, "students", varloop);
    TMPL_write("listInformationByid.html", 0, 0, varlist, cgiOut, cgiOut);
    return 0;
}
