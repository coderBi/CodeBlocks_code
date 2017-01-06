#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"
#include "ctemplate.h"
#include <winsock.h>
#include <mysql.h>
#include "excute.h"
#include <string.h>

void ShowErrorr(char * errorMsg);

int cgiMain()
{
    if(cgiFormSubmitClicked("save") == cgiFormSuccess){
        char action[20] = {0};
        char name[20] ={0};
        char phone[20] = {0};
        if(cgiFormString("action",action,sizeof(action)) != cgiFormSuccess || cgiFormString("name", name, sizeof(name)) != cgiFormSuccess
           || cgiFormString("phone", phone, sizeof(phone)) != cgiFormSuccess){
            cgiHeaderContentType("text/html;charset=gbk");
            ShowErrorr("mod未提供 或者 name 或 phone 为空！");
            return 0;
        }
        char mysqlStr[1024] = {0};
        char errorMsg[1024] = {0};
        if(strcmp(action,"addnew") == 0){
            sprintf(mysqlStr,"insert into t_teachers(name,phone) values('%s','%s')",name,phone);
            ExcuteNoSelect(mysqlStr,errorMsg);
        } else if(strcmp(action,"edit") == 0){
            char id[20] = {0};
            if(cgiFormString("id", id, sizeof(id))==cgiFormSuccess){
                sprintf(mysqlStr,"update t_teachers set name='%s', phone='%s' where id='%s'",name,phone,id);
                ExcuteNoSelect(mysqlStr,errorMsg);
            } else{
                cgiHeaderContentType("text/html;charset=gbk");
                ShowErrorr("mod=edit是 没有提供id！");
                return 0;
            }
        } else {
            cgiHeaderContentType("text/html;charset=gbk");
            ShowErrorr("mod错误！");
            return 0;
        }

        cgiHeaderLocation("InformationMS.cgi?mod=teacher&action=list");
    } else {
        TMPL_varlist *varlist =0;
        char action[20] = {0};
        if(cgiFormString("action", action,sizeof(action)) != cgiFormSuccess){
            cgiHeaderContentType("text/html;charset=gbk");
            ShowErrorr("缺少action参数");
            return 0;
        } else if(strcmp(action,"addnew") == 0){
            varlist = TMPL_add_var(varlist, "action",action,"title","新增教师",0);
            TMPL_write("addTeacher.html",0,0,varlist,cgiOut, cgiOut);
        } else if(strcmp(action,"edit") == 0){
            cgiHeaderContentType("text/html;charset=gbk");
            char id[20] ={0};
            char mysqlStr[1024] ={0};
            char errorMsg[1024] = {0};
            if(cgiFormString("id", id, sizeof(id))!= cgiFormSuccess){
                ShowErrorr("缺少id参数！");
                return 0;
            }
            varlist = TMPL_add_var(varlist,"title","教师信息修改",0);
            sprintf(mysqlStr,"select id,name, phone from t_teachers where id='%s'", id);
            MYSQL_RES *result = ExcuteSelect(mysqlStr, errorMsg);
            MYSQL_ROW row;
            if(row = mysql_fetch_row(result)){
                char* name = row[1];
                char* phone = row[2];
                varlist = TMPL_add_var(varlist,"action",action,"id",id,"name",name,"phone",phone,0);
            }
            TMPL_write("addTeacher.html",0,0,varlist,cgiOut, cgiOut);
        }else if(strcmp(action,"delete") == 0){
            char id[20] ={0};
            char mysqlStr[1024] ={0};
            char errorMsg[1024] = {0};
            if(cgiFormString("id", id, sizeof(id))!= cgiFormSuccess){
                cgiHeaderContentType("text/html;charset=gbk");
                ShowErrorr("缺少id参数！");
                return 0;
            }
            sprintf(mysqlStr,"delete from t_teachers where id = '%s'",id);
            ExcuteNoSelect(mysqlStr,errorMsg);
            cgiHeaderLocation("InformationMS.cgi?mod=teacher&action=list");
        } else {
            ShowErrorr("action错误！");
            return 0;
        }
    }
    return 0;
}

void ShowErrorr(char * errorMsg){
    TMPL_varlist *varlist = 0;
    varlist = TMPL_add_var(varlist, "errorMsg", errorMsg, 0);
    TMPL_write("addTeacher.html", 0, 0,varlist, cgiOut, cgiOut);
    return;
}
