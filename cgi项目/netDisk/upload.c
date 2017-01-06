#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "upload.h"
#include "cgic.h"
#include "ctemplate.h"
#include <windows.h>

extern void PrintHeaderContentText();
void PrintPage(TMPL_varlist *varlist);

void UploadFile(char *directory){
    TMPL_varlist *varlist = 0;
    varlist = TMPL_add_var(varlist,"directory",directory,0);
    char fileName[256] = {0};
    if(cgiFormFileName("fileName", fileName, sizeof(fileName)) == cgiFormSuccess){
        int fileSize;
        cgiFormFileSize("fileName", &fileSize);
        if(fileSize > 1024*1024){
            varlist = TMPL_add_var(varlist, "errorMsg", "文件超过1M！", 0);
            PrintPage(varlist);
            return;
        } else {
            char ext[20];
            _splitpath(fileName,NULL,NULL, NULL, ext);
            if(stricmp(ext,".jpg") != 0 && stricmp(ext,".png") != 0
               && stricmp(ext,".gif") != 0 && stricmp(ext,".zip") != 0){
                   varlist = TMPL_add_var(varlist, "errorMsg", "文件类型只能是：jpg，png，gif，zip", 0);
                   PrintPage(varlist);
                   return;
               }

        }
        cgiFilePtr uploadFilePtr;
        cgiFormFileOpen("fileName", &uploadFilePtr);
        char localPath[256] = {0};
        //GetCurrentDirectory(sizeof(localPath), localPath);
        strcat(localPath, directory);
        strcat(localPath,"/");
        strcat(localPath, fileName);
        FILE *targetFile = fopen(localPath, "wb");
        char buffer[1024] = {0};
        int len;
        while(cgiFormFileRead(uploadFilePtr, buffer, sizeof(buffer), &len) == cgiFormSuccess){
            fwrite(buffer, len, 1, targetFile);
        }
        fclose(targetFile);
        cgiFormFileClose(uploadFilePtr);
        char locationStr[1024] ={0};
        sprintf(locationStr,"netDisk.cgi?action=list&directory=%s",directory);
        cgiHeaderLocation(locationStr);
    } else {
        varlist = TMPL_add_var(varlist, "errorMsg", "没有选择文件！", 0);
        PrintPage(varlist);
    }
    return;
}

void PrintPage(TMPL_varlist *varlist){
    PrintHeaderContentText();
    TMPL_write("netDiskUploadFile.html", 0, 0, varlist, cgiOut, cgiOut);
}

