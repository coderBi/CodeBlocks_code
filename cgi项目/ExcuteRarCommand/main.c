#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <io.h>

void BatchRAR();

int main()
{
    BatchRAR();
    return 0;
}

void BatchRAR(){
    long handle;
    struct _finddata_t data;
    handle = _findfirst("E:/web/upload/*.jpg",&data);
    if(handle == -1){
        printf("here\n");
        return;
    }
    int count = 0;
    /*//这里之前用while 会丢失第一个找到些文件
    do{
        count++;
        char fullPath[1024] = {0};
        sprintf(fullPath,"E:/web/upload/%s",data.name);
        char param[1024] = "a -ep E:/web/upload/rar.rar ";
        strcat(param,fullPath);
        printf("fullpath=%s \n",fullPath);
        ShellExecute(NULL,"open","C:\\Program Files\\WinRAR\\Rar.exe",param,NULL,SW_HIDE);
    }while(!_findnext(handle,&data));*/ //这部分代码由于是把文件一个个的压缩，会产生很多rar进程，
                                        //  结果发现会丢失一半的文件（没有压缩进去）,所以下面改进，只执行一次压缩指令
    char param[1024] = "a -ep E:/web/upload/rar.rar ";
    do{
        count++;
        char fullPath[1024] = {0};
        sprintf(fullPath,"E:/web/upload/%s ",data.name);
        strcat(param,fullPath);
        printf("fullpath=%s \n",fullPath);
    }while(!_findnext(handle,&data));
    ShellExecute(NULL,"open","C:\\Program Files\\WinRAR\\Rar.exe",param,NULL,SW_HIDE);
    remove("E:/web/upload/rar.rar");
    _findclose(handle);
    printf("count=%d",count);
    return;
}
