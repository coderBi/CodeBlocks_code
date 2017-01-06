#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"
#include "ctemplate.h"
#include <string.h>
#include <io.h>
#include <time.h>
#include "upload.h"
#include <windows.h>

void ShowErrorr(char * errorMsg);
void PrintHeaderContentText();
void GetFiles(char* dir, char *fileKind, TMPL_loop ** loopFiles);
void DownloadFile(char *fullFileName);
void BatchRAR(char* rarPath);
void DeleteNetDiskFile();
void BatchDeleteFiles();
DWORD GetSrcFileSize(char *srcPath);

int cgiMain()
{
    char action[256] = {0};
    char directory[1024] = {0};
    char fileKind[256] = {0};
    strcpy(fileKind,"*.*");
    TMPL_varlist *varlist = 0;
    TMPL_loop *loopFile = 0;
    TMPL_loop *loopHead = 0;
    if(cgiFormSubmitClicked("batchDelete") == cgiFormSuccess){
        strcpy(action,"batchDelete");
    } else if(cgiFormSubmitClicked("batchDownload") == cgiFormSuccess){
        strcpy(action,"batchDownload");
    } else if(cgiFormString("action", action, sizeof(action)) != cgiFormSuccess){
        ShowErrorr("action参数丢失！");
        return 0;
    }
    char *headContent[] = {"选择","文件名","文件大小","创建日期","删除","下载"};
    int i;
    for(i = 0;i < 6; i++){
        loopHead = TMPL_add_varlist(loopHead,TMPL_add_var(0,"name",headContent[i], 0));
    }
    varlist = TMPL_add_loop(varlist,"thead",loopHead);
    if(strcmp(action,"list") == 0){
        varlist = TMPL_add_var(varlist, "title", "全部网盘文件", 0);
        if(cgiFormString("directory", directory,sizeof(directory)) != cgiFormSuccess){
            char currentDir[256] = {0};
            GetCurrentDirectory(sizeof(currentDir),currentDir);
            sprintf(directory,"%s/upload",currentDir);
            //strcpy(directory,"e:\\web\\upload");
        }
        GetFiles(directory,fileKind,&loopFile);
        varlist = TMPL_add_var(varlist,"directory",directory,0);
        varlist = TMPL_add_loop(varlist,"loopFiles",loopFile);
        PrintHeaderContentText();
        TMPL_write("netdisk.html",0,0,varlist,cgiOut,cgiOut);
    }else if(strcmp(action,"addNew") == 0){
        if(cgiFormString("directory",directory,sizeof(directory)) != cgiFormSuccess){
            ShowErrorr("网址错误");
            return 0;
        }
        TMPL_varlist * varlistUpload = 0;
        varlistUpload = TMPL_add_var(varlistUpload,"directory",directory,"title","上传文件",0);
        PrintHeaderContentText();
        TMPL_write("netdiskUploadFile.html",0,0,varlistUpload,cgiOut,cgiOut);
    } else if(strcmp(action,"upload") == 0) {
        if(cgiFormString("directory",directory,sizeof(directory)) != cgiFormSuccess){
            ShowErrorr("网址错误");
            return 0;
        }
        UploadFile(directory);
    } else if(strcmp(action,"delete") == 0){
        DeleteNetDiskFile();
    } else if(strcmp(action,"download") == 0){
        char checkboxValue[256] ={0};
        if(cgiFormString("checkbox",checkboxValue,sizeof(checkboxValue))!=cgiFormSuccess
           || cgiFormString("directory",directory,sizeof(directory))!=cgiFormSuccess){
            ShowErrorr("action=download，附加参数错误！");
            return 0;
        }
        char fullFileName[1024] ={0};
        sprintf(fullFileName,"%s/%s",directory,checkboxValue);
        char currentDir[256] = {0};
        GetCurrentDirectory(sizeof(currentDir),currentDir);

        //char locationStr[1024] = {0};
        //sprintf(locationStr,"%s/%s",directory + strlen(currentDir)+1,checkboxValue);
        fprintf(cgiOut,"Content-Disposition:attachment;filename=%s\r\n",checkboxValue);
        //cgiHeaderLocation(locationStr);

        fprintf(cgiOut,"Content-Type:application/octet-stream\r\n\r\n");
        //PrintHeaderContentText();
        DownloadFile(fullFileName);
    } else if(strcmp(action,"batchDelete") == 0){
        BatchDeleteFiles();
    } else if(strcmp(action,"batchDownload") == 0){
        char rarPath[1024] = {0};
        char rarName[1024] = {0};
        char checkboxValue[1024] = {0};
        if(cgiFormString("checkbox",checkboxValue,sizeof(checkboxValue)) != cgiFormSuccess){
            ShowErrorr("未选择任何文件！");
            return 0;
        }
        _splitpath(checkboxValue,NULL,NULL,rarName,NULL);
        if(cgiFormString("directory",directory,sizeof(directory))!=cgiFormSuccess){
            ShowErrorr("批量下载时directory参数错误！");
            return 0;
        }
        sprintf(rarPath,"%s/%s.rar",directory,rarName);
        remove(rarPath);
        BatchRAR(rarPath);
        fprintf(cgiOut,"Content-Disposition:attachment;filename=%s等文件.rar\r\n",checkboxValue);
        fprintf(cgiOut,"Content-Type:application/octet-stream\r\n\r\n");
        DownloadFile(rarPath);
        remove(rarPath);
    }  else {
        ShowErrorr("action参数错误！");
        return 0;
    }
    return 0;
}

void ShowErrorr(char * errorMsg){
    PrintHeaderContentText();
    TMPL_varlist *varlist = 0;
    varlist = TMPL_add_var(varlist, "title","出错了！","errorMsg",errorMsg, 0);
    TMPL_write("netdisk.html", 0, 0,varlist, cgiOut, cgiOut);
    return;
}

void PrintHeaderContentText(){
    cgiHeaderContentType("text/html;charset=gbk");
    return;
}

void GetFiles(char* dir, char *fileKind, TMPL_loop ** loopFiles){
    long findHandler;
    struct _finddata_t data;
    char fullPath[256] = {0};
    sprintf(fullPath,"%s/%s",dir,fileKind);
    findHandler = _findfirst(fullPath,&data);
    if(findHandler == -1){
        ShowErrorr("没有找到相应目录！");
        return;
    }
    while(!_findnext(findHandler,&data)){
        char name[1024];
        strcpy(name,data.name);
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
        if(strcmp(data.name,"..") != 0){
            if((data.attrib&_A_SUBDIR) == _A_SUBDIR){
                char subDir[256] = {0};
                sprintf(subDir,"%s/%s",dir,data.name);
                sprintf(name,"<a href = 'netDisk.cgi?action=list&directory=%s'>%s</a>",subDir,data.name);
                *loopFiles = TMPL_add_varlist(*loopFiles,TMPL_add_var(0,"name",name,"size",fileSizeText,
                                         "createTime",createTime,0));
                //GetFiles(subDir,fileKind,loopFiles);
            } else {
                *loopFiles = TMPL_add_varlist(*loopFiles,TMPL_add_var(0,"select","","name",name,"size",fileSizeText,
                                         "createTime",createTime,"delete","删除","download","下载",0));
            }
        }

    }
    return;
}

void DeleteNetDiskFile(){
    char checkboxValue[256] ={0};
    char directory[1024] ={0};
    if(cgiFormString("checkbox",checkboxValue,sizeof(checkboxValue))!=cgiFormSuccess
       || cgiFormString("directory",directory,sizeof(directory))!=cgiFormSuccess){
        ShowErrorr("action=delete，附加参数错误！");
        return;
    }
    char fullFileName[1024] ={0};
    sprintf(fullFileName,"%s/%s",directory,checkboxValue);
    remove(fullFileName);
    char locationStr[1024];
    sprintf(locationStr,"netDisk.cgi?action=list&directory=%s",directory);
    cgiHeaderLocation(locationStr);
    return;
}

void BatchDeleteFiles(){
    char **checkboxArray = 0;
    char directory[1024] ={0};
    if(cgiFormStringMultiple("checkbox",&checkboxArray)!=cgiFormSuccess
       || cgiFormString("directory",directory,sizeof(directory))!=cgiFormSuccess){
        ShowErrorr("action=delete，附加参数错误！");
        return;
    }
    int i;
    for(i= 0; checkboxArray[i] != 0; i++){
        char fullFileName[1024] ={0};
        sprintf(fullFileName,"%s/%s",directory,checkboxArray[i]);
        remove(fullFileName);
    }
    char locationStr[1024];
    sprintf(locationStr,"netDisk.cgi?action=list&directory=%s",directory);
    cgiHeaderLocation(locationStr);
    return;
}

DWORD GetSrcFileSize(char *srcPath){
    HANDLE handle = CreateFile(srcPath,FILE_READ_EA,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
    if(handle == INVALID_HANDLE_VALUE){
        return 0;
    }
    DWORD lowSize, highSize;
    lowSize = GetFileSize(handle,&highSize);
    return lowSize;
}

void DownloadFile(char *fullFileName){
    DWORD fileSize = GetSrcFileSize(fullFileName);
    FILE *downloadFilePtr = fopen(fullFileName,"rb");
    char c;
    while(fileSize-- > 0){
        c = fgetc(downloadFilePtr);
        putchar(c);
    }
    fclose(downloadFilePtr);
    return;
}

/*
//这里的执行的压缩工作，没有执行完但是ShellExecute执行完了，所以会去调用函数的地方接着执行
//由于rar操作没完成，可能出现这时候读取文件不全
//改写void BatchRAR(char *rarPath)的方法是 调用ShellExecuteEx(SHELLEXECUTEINFO) 等待SHELLEXECUTEINFO.hProcess被释放

void BatchRAR(char *rarPath){
    char **checkboxArray = 0;
    char directory[1024] ={0};
    if(cgiFormStringMultiple("checkbox",&checkboxArray)!=cgiFormSuccess
       || cgiFormString("directory",directory,sizeof(directory))!=cgiFormSuccess){
        ShowErrorr("批量下载出错！");
        return;
    }
    int i;
    char param[1024] ={0};
    sprintf(param,"a -ep %s ",rarPath);
    for(i= 0; checkboxArray[i] != 0; i++){
        char fullFileName[1024] ={0};
        //char execStr[1024] ={0};
        sprintf(fullFileName,"%s/%s ",directory,checkboxArray[i]);
        //sprintf(execStr,"\"C:\\Program Files\\WinRAR\\Rar.exe\" a -ep %s %s",rarPath,fullFileName);
        //system(execStr);
        strcat(param,fullFileName);
    }
    ShellExecute(NULL,"open","C:\\Program Files\\WinRAR\\Rar.exe",param,NULL,SW_HIDE);
    return;
}
*/

void BatchRAR(char *rarPath){
    char **checkboxArray = 0;
    char directory[1024] ={0};
    if(cgiFormStringMultiple("checkbox",&checkboxArray)!=cgiFormSuccess
       || cgiFormString("directory",directory,sizeof(directory))!=cgiFormSuccess){
        ShowErrorr("批量下载出错！");
        return;
    }
    int i;
    char param[1024] ={0};
    sprintf(param,"a -ep %s ",rarPath);
    for(i= 0; checkboxArray[i] != 0; i++){
        char fullFileName[1024] ={0};
        //char execStr[1024] ={0};
        sprintf(fullFileName,"%s/%s ",directory,checkboxArray[i]);
        //sprintf(execStr,"\"C:\\Program Files\\WinRAR\\Rar.exe\" a -ep %s %s",rarPath,fullFileName);
        //system(execStr);
        strcat(param,fullFileName);
    }
    SHELLEXECUTEINFO shellexcuteInfo;
    memset(&shellexcuteInfo, 0, sizeof(shellexcuteInfo));
    shellexcuteInfo.cbSize = sizeof(shellexcuteInfo);
    shellexcuteInfo.hwnd = NULL;
    shellexcuteInfo.lpVerb = "open";
    shellexcuteInfo.lpFile = "C:\\Program Files\\WinRAR\\Rar.exe";
    shellexcuteInfo.lpParameters = param;
    shellexcuteInfo.nShow = SW_HIDE;
    shellexcuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShellExecuteEx(&shellexcuteInfo);
    WaitForSingleObject(shellexcuteInfo.hProcess,INFINITE);
    return;
}
