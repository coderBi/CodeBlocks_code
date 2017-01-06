#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <time.h>

void ListFiles(char* dir, char *fileKind, int spaceNum);
void ListFiles1(char* dir, char *fileKind, int spaceNum);
void PrintSpace(int spaceNum);

int main()
{
    char *dir ="E:\\web\\upload";
    char *fileKind = "*.*";
    ListFiles1(dir,fileKind,0);
    printf("\n---------------------------------------------------------------\n");
    ListFiles(dir,fileKind,0);
    return 0;
}

void ListFiles(char* dir, char *fileKind, int spaceNum){
    long findHandler;
    struct _finddata_t data;
    char fullPath[256] = {0};
    sprintf(fullPath,"%s/%s",dir,fileKind);
    findHandler = _findfirst(fullPath,&data);
    if(findHandler == -1){
        printf("没有找到相应目录！");
        return;
    }
    while(!_findnext(findHandler,&data)){
        PrintSpace(spaceNum);
        if((data.attrib&_A_SUBDIR) == _A_SUBDIR){
            printf("%s\n",data.name);
            if(strcmp(data.name,"..") != 0){
                char subDir[256] = {0};
                sprintf(subDir,"%s/%s",dir,data.name);
                ListFiles(subDir,fileKind,spaceNum+2);
            }
        } else {
            char *name = data.name;
            char createTime[256] = {0};
            double fileSize = data.size;
            char fileSizeText[256] = {0};
            time_t time = data.time_create;

            if(fileSize < 1024){
                sprintf(fileSizeText,"%.1f字节",fileSize);
            } else if(fileSize < 1024*1024){
                sprintf(fileSizeText,"%.1fKB",fileSize/1024);
            } else if(fileSize < 1024*1024){
                sprintf(fileSizeText,"%.1fMB",fileSize/1024/1024);
            } else{
                sprintf(fileSizeText,"%.1fGB",fileSize/1024/1024/1024);
            }
            strftime(createTime,sizeof(createTime),"%Y-%m-%d %H:%M:%S",localtime(&time));
            printf("name = %s, size = %s, time = %s\n", name, fileSizeText, createTime);
        }
    }
    return;
}

void ListFiles1(char* dir, char *fileKind, int spaceNum){
    long findHandler;
    struct _finddata_t data;
    char fullPath[256] = {0};
    sprintf(fullPath,"%s/%s",dir,fileKind);
    findHandler = _findfirst(fullPath,&data);
    if(findHandler == -1){
        printf("没有找到相应目录！");
        return;
    }
    while(!_findnext(findHandler,&data)){
        PrintSpace(spaceNum);
        if((data.attrib&_A_SUBDIR) == _A_SUBDIR){
            printf("%s\n",data.name);
            if(strcmp(data.name,"..") != 0){
                char subDir[256] = {0};
                sprintf(subDir,"%s/%s",dir,data.name);
                ListFiles(subDir,fileKind,spaceNum+2);
            }
        }
        char *name = data.name;
        char createTime[256] = {0};
        double fileSize = data.size;
        char fileSizeText[256] = {0};
        time_t time = data.time_create;

        if(fileSize < 1024){
            sprintf(fileSizeText,"%.1f字节",fileSize);
        } else if(fileSize < 1024*1024){
            sprintf(fileSizeText,"%.1fKB",fileSize/1024);
        } else if(fileSize < 1024*1024){
            sprintf(fileSizeText,"%.1fMB",fileSize/1024/1024);
        } else{
            sprintf(fileSizeText,"%.1fGB",fileSize/1024/1024/1024);
        }
        strftime(createTime,sizeof(createTime),"%Y-%m-%d %H:%M:%S",localtime(&time));
        printf("name = %s, size = %s, time = %s\n", name, fileSizeText, createTime);
    }
    return;
}

void PrintSpace(int spaceNum){
    int i;
    for(i = 0; i < spaceNum; i++){
        //printf("space = %d\n",spaceNum);
        printf("  ");
    }
    return;
}
