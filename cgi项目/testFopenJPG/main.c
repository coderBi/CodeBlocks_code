#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void CopyFiles(char *srcPath);
DWORD GetSrcFileSize(char *srcPath);

int main()
{
    CopyFiles("E:\\web\\upload/chongwu817.jpg");
    return 0;
}

void CopyFiles(char *srcPath){
    FILE *readfilePtr = fopen(srcPath,"rb");
    if(readfilePtr == NULL){
        printf("读入指针为空！\n");
        return;
    }
    char desPath[256] = {0};
    char fileName[256] = {0};
    char fileExt[256] ={0};
    _splitpath(srcPath,0,0,fileName,fileExt);
    sprintf(desPath,"E:\\web\\upload\\fopenTestDes/%s%s",fileName,fileExt);
    FILE *writefilePtr = fopen(desPath,"wb");
    if(writefilePtr == NULL){
        printf("写入指针为空！\n");
        return;
    }
    DWORD size = GetSrcFileSize(srcPath);
    printf("size=%d\n",size);
    //对于jpg gif等等文件格式，发现用 == eof 会由于特定编码取补全文件，所以这里先调用winapi得到文件大小信息，
    //用这个大小信息来控制读取
    char c;
    while(size >0){
        c = fgetc(readfilePtr);
        fputc(c,writefilePtr);
        size--;
    }
    printf("操作完成！\npath:%s--->%s\n",srcPath,desPath);
}

DWORD GetSrcFileSize(char *srcPath){
    HANDLE handle =CreateFile(srcPath,FILE_READ_EA,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
    if(handle == INVALID_HANDLE_VALUE) {
        printf("打开文件失败: %x\n", GetLastError());
        return 0;
    }
    DWORD size,highSize;
    size = GetFileSize(handle,&highSize);
    return size;
}
