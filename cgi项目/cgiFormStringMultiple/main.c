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
    //1������û�а취ͨ��sizeof��cgistr��/sizeof��cgistr��1�����õ����鳤�ȣ���Ϊ����sizeof���ǻ�ȡָ�볤�� Ҳ����ֵΪ4
    //2�� cgiStringMultiple���ص����飬���һ���ǿգ���������ͨ��cgiStr[i] != NULL��̽�߽�
    char msg[1024] = {0};
    if(cgiFormStringMultiple("cgiStr",&cgiStr) != cgiFormSuccess){
        strcpy(msg,"cgiStr��ֵ��");
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
