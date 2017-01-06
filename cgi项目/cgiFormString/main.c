#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"
#include <string.h>

int cgiMain()
{
    cgiHeaderContentType("text/html;charset=gbk");
    char name[256] = {0}, pwd[256] = {0};
    char *_name = "bww", *_pwd = "123";
    if(cgiFormString("name", name, sizeof(name)) != cgiFormSuccess){
        fprintf(cgiOut,"请提供用户名");
        return 0;
    }
    if(cgiFormString("pwd", pwd, sizeof(pwd)) != cgiFormSuccess){
        fprintf(cgiOut,"密码为空");
        return 0;
    }
    if(strcmp(name, _name) == 0 && strcmp(pwd, _pwd) == 0){
        fprintf(cgiOut,"<html><head></head><body>登陆成功！<br>name = %s<br> password = %s</body></html>", name, pwd);
    } else {
        fprintf(cgiOut,"<html><head></head><body>用户名或密码错误！</body></html>");
    }
    return 0;
}
