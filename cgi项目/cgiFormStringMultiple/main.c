#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"
#include "ctemplate.h"
#include <string.h>
#include <memory.h>

void PrintMesssage(char * msg);

int cgiMain()
{
    char **cgiStr = 0;
    /*cgiStr = (char**)malloc(10*sizeof(char*));
    int i;
    for(i = 0; i < 10; i++){
        cgiStr[i] = (char*)malloc(256*sizeof(char));
        memset(cgiStr[i],0,256);
    }*/
    //1，下面没有办法通过sizeof（cgistr）/sizeof（cgistr【1】）得到数组长度，因为两个sizeof都是获取指针长度 也就是值为4
    //2， cgiStringMultiple返回的数组，最后一个是空，这样可以通过cgiStr[i] != NULL试探边界
    char msg[1024] = {0};
    if(cgiFormStringMultiple("cgiStr",&cgiStr) != cgiFormSuccess){
        strcpy(msg,"cgiStr无值！");
    } else {
        int i;
        for(i = 0; cgiStr[i] != NULL; i++){
            char value[256] = {0};
            sprintf(value,"value%d=%s;",i,cgiStr[i]);
            strcat(msg,value);
        }
    }
    PrintMesssage(msg);
    return 0;
}

void PrintMesssage(char * msg){
   cgiHeaderContentType("text/html;charset=gbk");
   fprintf(cgiOut,"<html><head></head><body>msg=%s</body></html>",msg);
   return;
}
