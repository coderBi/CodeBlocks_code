#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"
#include "ctemplate.h"
#include <string.h>
#include <windows.h>

void PrintPage(TMPL_varlist *varlist);

int cgiMain()
{
    cgiHeaderContentType("text/html;charset=gbk");
    TMPL_varlist *varlist = 0;
    if(cgiFormSubmitClicked("submit") != cgiFormSuccess){
        PrintPage(varlist);
    } else {
        char fileName[256] = {0};
        if(cgiFormFileName("file1", fileName, sizeof(fileName)) == cgiFormSuccess){
            int fileSize;
            cgiFormFileSize("file1", &fileSize);
            if(fileSize > 1024*1024){
                varlist = TMPL_add_var(varlist, "errorMsg", "�ļ�����1M��", 0);
                PrintPage(varlist);
                return 0;
            } else {
                char ext[20];
                _splitpath(fileName,NULL,NULL, NULL, ext);
                if(stricmp(ext,".jpg") != 0 && stricmp(ext,".png") != 0
                   && stricmp(ext,".gif") != 0 && stricmp(ext,".zip") != 0){
                       varlist = TMPL_add_var(varlist, "errorMsg", "�ļ�����ֻ���ǣ�jpg��png��gif��zip", 0);
                       PrintPage(varlist);
                       return 0;
                   }

            }
            cgiFilePtr uploadFilePtr;
            cgiFormFileOpen("file1", &uploadFilePtr);
            char localPath[256] = {0};
            GetCurrentDirectory(sizeof(localPath), localPath);
            strcat(localPath, "/upload/");
            strcat(localPath, fileName);
            FILE *targetFile = fopen(localPath, "wb");
            char buffer[1024] = {0};
            int len;
            while(cgiFormFileRead(uploadFilePtr, buffer, sizeof(buffer), &len) == cgiFormSuccess){
                fwrite(buffer, len, 1, targetFile);
            }
            fclose(targetFile);
            cgiFormFileClose(uploadFilePtr);
            fprintf(cgiOut,"path= %s", localPath);
            varlist = TMPL_add_var(varlist, "errorMsg", "�ϴ��ɹ���", 0);
            PrintPage(varlist);
        } else {
            varlist = TMPL_add_var(varlist, "errorMsg", "û��ѡ���ļ���", 0);
            PrintPage(varlist);
        }

    }
    return 0;
}

void PrintPage(TMPL_varlist *varlist){
    TMPL_write("uploadFile.html", 0, 0, varlist, cgiOut, cgiOut);
}
