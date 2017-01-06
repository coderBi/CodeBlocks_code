#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"
#include "ctemplate.h"
#include <winsock.h>
#include <mysql.h>
#include "excute.h"
#include "createGuid.h"

void ShowErrorr(char * errorMsg);
void PrintHeaderContentText();
void LoginSys();
void GetSessionUserName(char *userName);
void SetSessionUserName(char *userName);
void TouchSession();

int cgiMain()
{
    TouchSession();
    char userNameInSession[256] = {0};
    GetSessionUserName(userNameInSession);
    if(strlen(userNameInSession)==0){
        LoginSys();
        return 0;
    }
    char mod[20] = {0};
    char action[20] = {0};
    if(cgiFormString("mod",mod,sizeof(mod)) == cgiFormSuccess
       && cgiFormString("action",action,sizeof(action)) == cgiFormSuccess){
       if(strcmp(mod, "teacher") == 0){
            if(strcmp(action,"list") == 0){
                char mysqlErrorMsg[256] ={0};
                TMPL_loop *varloop =0;
                char *mysqlStr = "select * from t_teachers";
                MYSQL_RES *result = ExcuteSelect(mysqlStr,mysqlErrorMsg);
                if(result == 0){
                    PrintHeaderContentText();
                    ShowErrorr(mysqlErrorMsg);
                    return 0;
                }
                MYSQL_ROW row;
                while((row = mysql_fetch_row(result)) != NULL){
                    char* id = row[0];
                    char* name = row[1];
                    char* phone = row[2];
                    varloop = TMPL_add_varlist(varloop,TMPL_add_var(0,"id",id,"name",name,"phone",phone,0));
                }
                mysql_free_result(result);
                TMPL_varlist *varlist = TMPL_add_loop(0, "teachers",varloop);
                PrintHeaderContentText();
                TMPL_write("InformationMS.html", 0, 0,varlist, cgiOut, cgiOut);
            } else if(strcmp(action,"addnew") == 0){
                TMPL_varlist *varlist = 0;
                varlist = TMPL_add_var(varlist,"title","新增教师","action","addnew",0);
                PrintHeaderContentText();
                TMPL_write("addTeacher.html",0,0,varlist,cgiOut,cgiOut);
            } else {
                PrintHeaderContentText();
                ShowErrorr("action输入非法！");
            }

       } else if(strcmp(mod, "student") == 0){
           if(strcmp(action,"list") == 0){
                char mysqlErrorMsg[256] ={0};
                TMPL_loop *varloop =0;
                char *mysqlStr = "select id,name,age,gender from t_students";
                MYSQL_RES *result = ExcuteSelect(mysqlStr,mysqlErrorMsg);
                if(result == 0){
                    PrintHeaderContentText();
                    ShowErrorr(mysqlErrorMsg);
                    return 0;
                }
                MYSQL_ROW row;
                while((row = mysql_fetch_row(result)) != NULL){
                    char* id = row[0];
                    char* name = row[1];
                    char* age = row[2];
                    char* gender = row[3];
                    char genderSelectStr[1024] = {0};
                    char genderText[10] = {0};
                    sprintf(genderSelectStr,"select name from t_genders where id ='%s'",gender);
                    MYSQL_RES * genderRes = ExcuteSelect(genderSelectStr,mysqlErrorMsg);
                    MYSQL_ROW genderRow;
                    if((genderRow = mysql_fetch_row(genderRes)) != NULL){
                        char * genderName = genderRow[0];
                        strcpy(genderText, genderName);
                    }
                    mysql_free_result(genderRes);
                    varloop = TMPL_add_varlist(varloop,TMPL_add_var(0,"id",id,"name",name,"age",age,"gender",genderText,0));
                }
                mysql_free_result(result);
                TMPL_varlist *varlist = TMPL_add_loop(0, "students",varloop);
                PrintHeaderContentText();
                TMPL_write("studentInformation.html", 0, 0,varlist, cgiOut, cgiOut);
            } else if(strcmp(action,"addnew") == 0){
                TMPL_varlist *varlist = 0;
                varlist = TMPL_add_var(varlist,"title","新增学生","action","addnew",0);
                PrintHeaderContentText();
                TMPL_write("addStudent.html",0,0,varlist,cgiOut,cgiOut);
            } else {
                PrintHeaderContentText();
                ShowErrorr("action输入非法！");
            }

       } else if(strcmp(mod, "netdisk") == 0){
            char location[256] ={0};
            sprintf(location,"netDisk.cgi?action=%s",action);
            cgiHeaderLocation(location);
       }else if(strcmp(mod, "homepage") == 0){
            TMPL_varlist *varlistHomePage = 0;
            TMPL_loop *loopHomePage = 0;
            loopHomePage = TMPL_add_varlist(loopHomePage,TMPL_add_var(0,"name","学生信息管理","href","InformationMs.cgi?mod=student&action=list",0));
            loopHomePage = TMPL_add_varlist(loopHomePage,TMPL_add_var(0,"name","教师信息管理","href","InformationMs.cgi?mod=teacher&action=list",0));
            loopHomePage = TMPL_add_varlist(loopHomePage,TMPL_add_var(0,"name","网盘管理","href","InformationMs.cgi?mod=netdisk&action=list",0));
            varlistHomePage = TMPL_add_loop(varlistHomePage,"homePageList", loopHomePage);
            char userName[256] = {0};
            GetSessionUserName(userName);
            varlistHomePage = TMPL_add_var(varlistHomePage,"userName",userName,0);
            PrintHeaderContentText();
            TMPL_write("InformationMSHomePage.html",0,0,varlistHomePage,cgiOut,cgiOut);
       } else {
           ShowErrorr("mod输入非法！");
       }

    } else {
        LoginSys();
    }
    return 0;
}

void ShowErrorr(char * errorMsg){
    TMPL_varlist *varlist = 0;
    varlist = TMPL_add_var(varlist, "errorMsg", errorMsg, 0);
    TMPL_write("InformationMS.html", 0, 0,varlist, cgiOut, cgiOut);
    return;
}

void PrintHeaderContentText(){
    cgiHeaderContentType("text/html;charset=gbk");
    return;
}

void LoginSys(){
    if(cgiFormSubmitClicked("login") != cgiFormSuccess){
        PrintHeaderContentText();
        TMPL_write("InformationMSLogin.html",0,0,0,cgiOut,cgiOut);
    } else {
        char userName[256]={0};
        char password[256]={0};
        char errorMsg[1024] = {0};
        TMPL_varlist *varlist = 0;
        if(cgiFormString("userName",userName,sizeof(userName))!=cgiFormSuccess){
            strcpy(errorMsg,"请填写用户名");
        } else if(cgiFormString("password",password,sizeof(password))!=cgiFormSuccess){
            strcpy(errorMsg,"请填写密码");
        } else {
            char mysqlStr[1024] = {0};
            char mysqlErrorMsg[1024] ={0};
            sprintf(mysqlStr,"select count(*) from t_users where name='%s' and password ='%s'",userName,password);
            MYSQL_RES *res = ExcuteSelect(mysqlStr,mysqlErrorMsg);
            if(res == 0){
                strcpy(errorMsg,mysqlErrorMsg);
            } else {
                MYSQL_ROW row = mysql_fetch_row(res);
                if(row == NULL){
                    strcpy(errorMsg,"未知错误，请刷新页面");
                } else {
                    int count;
                    count = atoi(row[0]);
                    if(count > 0){
                        char locationStr[1024] = {0};
                        sprintf(locationStr,"InformationMS.cgi?mod=homepage&action=list");
                        SetSessionUserName(userName);
                        cgiHeaderLocation(locationStr);

                        return;
                    } else {
                        strcpy(errorMsg,"用户名或密码错误");
                    }
                }
            }
        }
        varlist=TMPL_add_var(varlist,"userName",userName,"password",password,0);
        varlist=TMPL_add_var(varlist,"errorMsg",errorMsg,0);
        PrintHeaderContentText();
        TMPL_write("InformationMSLogin.html",0,0,varlist,cgiOut,cgiOut);
    }
}

void GetSessionUserName(char *userName){
    char sessionId[64] = {0};
    if(cgiCookieString("SessionId",sessionId,sizeof(sessionId)) == cgiFormSuccess){
        char mysqlStr[256] = {0};
        char mysqlErrorMsg[1024] = {0};
        sprintf(mysqlStr,"select userName from t_sessions where id='%s'",sessionId);
        MYSQL_RES *res = ExcuteSelect(mysqlStr,mysqlErrorMsg);
        MYSQL_ROW row = mysql_fetch_row(res);
        if(row != NULL){
            strcpy(userName,row[0]);
        }
    }
}

void SetSessionUserName(char *userName){
    char sessionId[64] ={0};
    int needCreate = 0;
    if(cgiCookieString("SessionId",sessionId,sizeof(sessionId)) != cgiFormSuccess){
        needCreate = 1;
    } else {
        char mysqlStr[256] ={0};
        char mysqlErrorMsg[1024] ={0};
        sprintf(mysqlStr,"select count(*) from t_sessions where id='%s'",sessionId);
        MYSQL_RES *res = ExcuteSelect(mysqlStr,mysqlErrorMsg);
        MYSQL_ROW row = mysql_fetch_row(res);
        int count = atoi(row[0]);
        if(count > 0){
            sprintf(mysqlStr,"update t_sessions set userName='%s' where id='%s'",userName,sessionId);
            ExcuteNoSelect(mysqlStr,mysqlErrorMsg);
        } else {
            needCreate = 1;
        }
        mysql_free_result(res);
    }
    if(needCreate == 1){
        strcpy(sessionId,CreateGuid());
        cgiHeaderCookieSetString("SessionId",sessionId,20*60,0,"localhost");
        char mysqlStr[256] ={0};
        char mysqlErrorMsg[1024] = {0};
        sprintf(mysqlStr,"insert into t_sessions(id,userName,updateTime) values('%s','%s',now())",sessionId,userName);
        ExcuteNoSelect(mysqlStr,mysqlErrorMsg);
    }
    return;
}

void TouchSession(){
    char mysqlStr[256] = {0};
    char mysqlErrorMsg[1024] = {0};
    char sessionId[256] ={0};
    if(cgiCookieString("SessionId",sessionId,sizeof(sessionId)) != cgiFormSuccess){
        return;
    }
    cgiHeaderCookieSetString("SessionId",sessionId,20*60,"","localhost");

    sprintf(mysqlStr,"delete from t_sessions where id='%s' and (unix_timestamp(now()) - unix_timestamp(updateTime)) > 20*60",sessionId);
    ExcuteNoSelect(mysqlStr,mysqlErrorMsg);
    sprintf(mysqlStr,"update t_sessions set updateTime=now() where id='%s'",sessionId);
    ExcuteNoSelect(mysqlStr,mysqlErrorMsg);
    return;
}
