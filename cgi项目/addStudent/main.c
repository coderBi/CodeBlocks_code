#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"
#include "ctemplate.h"
#include <winsock.h>
#include <mysql.h>
#include <mysql.h>
#include "excute.h"
#include <string.h>

void ShowErrorr(char * errorMsg);

int cgiMain()
{
    if(cgiFormSubmitClicked("save") == cgiFormSuccess){
        char action[20] = {0};
        char name[20] ={0};
        char age[20] = {0};
        char gender[10] = {0};
        char genderInt[10] ={0};
        char mysqlStr[1024] = {0};
        char errorMsg[1024] = {0};
        if(cgiFormString("action",action,sizeof(action)) != cgiFormSuccess || cgiFormString("name", name, sizeof(name)) != cgiFormSuccess
           || cgiFormString("age", age, sizeof(age)) != cgiFormSuccess || cgiFormString("gender", gender, sizeof(gender)) != cgiFormSuccess){
            cgiHeaderContentType("text/html;charset=gbk");
            ShowErrorr("action未提供 或者学生信息不全！");
            return 0;
        }
        if(strcmp(gender,"女") == 0 || strcmp(gender,"男") == 0 || strcmp(gender,"未知性别") == 0){
            char genderSelectStr[1024] = {0};
            sprintf(genderSelectStr,"select id from t_genders where name ='%s'",gender);
            MYSQL_RES* result = ExcuteSelect(genderSelectStr,errorMsg);
            MYSQL_ROW row;
            if(row = mysql_fetch_row(result)){
                char *genderId = row[0];
                strcpy(genderInt,genderId);
            }
            mysql_free_result(result);
        } else {
            cgiHeaderContentType("text/html;charset=gbk");
            ShowErrorr("性别填写错误！");
            return 0;
        }
        if(strcmp(action,"addnew") == 0){
            sprintf(mysqlStr,"insert into t_students(name,age,gender) values('%s','%s','%s')",name,age,genderInt);
            ExcuteNoSelect(mysqlStr,errorMsg);
        } else if(strcmp(action,"edit") == 0){
            char id[20] = {0};
            if(cgiFormString("id", id, sizeof(id))==cgiFormSuccess){
                sprintf(mysqlStr,"update t_students set name='%s', age='%s', gender='%s' where id='%s'",name,age,genderInt,id);
                ExcuteNoSelect(mysqlStr,errorMsg);
            } else{
                cgiHeaderContentType("text/html;charset=gbk");
                ShowErrorr("mod=edit是 没有提供id！");
                return 0;
            }
        } else {
            cgiHeaderContentType("text/html;charset=gbk");
            ShowErrorr("action错误！");
            return 0;
        }

        cgiHeaderLocation("InformationMS.cgi?mod=student&action=list");
    } else {
        TMPL_varlist *varlist =0;
        TMPL_loop *varloop = {0};
        char action[20] = {0};
        char listGenderStr[1024] = {0};
        char listGenderErrorMsg[1024] = {0};

        if(cgiFormString("action", action,sizeof(action)) != cgiFormSuccess){
            cgiHeaderContentType("text/html;charset=gbk");
            ShowErrorr("缺少action参数");
            return 0;
        } else if(strcmp(action,"addnew") == 0){
            varlist = TMPL_add_var(varlist, "action",action,"title","新增学生",0);
            sprintf(listGenderStr,"select name from t_genders");
            MYSQL_RES *listGenderRes = ExcuteSelect(listGenderStr,listGenderErrorMsg);
            MYSQL_ROW listGenderRow;
            while(listGenderRow = mysql_fetch_row(listGenderRes)){
                char* optionName = listGenderRow[0];
                varloop = TMPL_add_varlist(varloop,TMPL_add_var(0,"name",optionName,0));
            }
            varlist = TMPL_add_loop(varlist,"genderOptions",varloop);
            mysql_free_result(listGenderRes);
            cgiHeaderContentType("text/html;charset=gbk");
            TMPL_write("addStudent.html",0,0,varlist,cgiOut, cgiOut);
        } else if(strcmp(action,"edit") == 0){
            cgiHeaderContentType("text/html;charset=gbk");
            char id[20] ={0};
            char mysqlStr[1024] ={0};
            char errorMsg[1024] = {0};
            if(cgiFormString("id", id, sizeof(id))!= cgiFormSuccess){
                ShowErrorr("缺少id参数！");
                return 0;
            }
            varlist = TMPL_add_var(varlist,"title","学生信息修改",0);
            sprintf(mysqlStr,"select id,name, age,gender from t_students where id='%s'", id);
            MYSQL_RES *result = ExcuteSelect(mysqlStr, errorMsg);
            MYSQL_ROW row;
            if(row = mysql_fetch_row(result)){
                char* name = row[1];
                char* age = row[2];
                char* gender = row[3];
                char genderText[10] ={0};
                sprintf(mysqlStr,"select name from t_genders where id ='%s'",gender);
                MYSQL_RES * genderRes = ExcuteSelect(mysqlStr,errorMsg);
                MYSQL_ROW genderRow;
                if(genderRow = mysql_fetch_row(genderRes)){
                    char * genderName = genderRow[0];
                    strcpy(genderText, genderName);
                }
                mysql_free_result(genderRes);
                varlist = TMPL_add_var(varlist,"action",action,"id",id,"name",name,"age",age,"gender",genderText,0);
                sprintf(listGenderStr,"select name from t_genders");
                MYSQL_RES *listGenderRes = ExcuteSelect(listGenderStr,listGenderErrorMsg);
                MYSQL_ROW listGenderRow;
                while(listGenderRow = mysql_fetch_row(listGenderRes)){
                    char* optionName = listGenderRow[0];
                    if(strcmp(optionName,genderText) == 0){
                        varloop = TMPL_add_varlist(varloop,TMPL_add_var(0,"optionSelected","Selected","name",optionName,0));
                    } else {
                        varloop = TMPL_add_varlist(varloop,TMPL_add_var(0,"name",optionName,0));
                    }
                }
                varlist = TMPL_add_loop(varlist,"genderOptions",varloop);
                mysql_free_result(listGenderRes);
            }
            mysql_free_result(result);
            TMPL_write("addStudent.html",0,0,varlist,cgiOut, cgiOut);
        } else if(strcmp(action,"delete") == 0){
            char id[20] ={0};
            char mysqlStr[1024] ={0};
            char errorMsg[1024] = {0};
            if(cgiFormString("id", id, sizeof(id))!= cgiFormSuccess){
                cgiHeaderContentType("text/html;charset=gbk");
                ShowErrorr("缺少id参数！");
                return 0;
            }
            sprintf(mysqlStr,"delete from t_students where id = '%s'",id);
            ExcuteNoSelect(mysqlStr,errorMsg);
            cgiHeaderLocation("InformationMS.cgi?mod=student&action=list");
        } else {
            ShowErrorr("action错误！");
            return 0;
        }
    }
    return 0;
}

void ShowErrorr(char * errorMsg){
    TMPL_varlist *varlist = 0;
    varlist = TMPL_add_var(varlist, "errorMsg", errorMsg, "title", "出错了！", 0);
    TMPL_write("addStudent.html", 0, 0,varlist, cgiOut, cgiOut);
    return;
}
