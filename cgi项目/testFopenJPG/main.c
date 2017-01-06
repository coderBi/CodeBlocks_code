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
        printf("����ָ��Ϊ�գ�\n");
        return;
    }
    char desPath[256] = {0};
    char fileName[256] = {0};
    char fileExt[256] ={0};
    _splitpath(srcPath,0,0,fileName,fileExt);
    sprintf(desPath,"E:\\web\\upload\\fopenTestDes/%s%s",fileName,fileExt);
    FILE *writefilePtr = fopen(desPath,"wb");
    if(writefilePtr == NULL){
        printf("д��ָ��Ϊ�գ�\n");
        return;
    }
    DWORD size = GetSrcFileSize(srcPath);
    printf("size=%d\n",size);
    //����jpg gif�ȵ��ļ���ʽ�������� == eof �������ض�����ȡ��ȫ�ļ������������ȵ���winapi�õ��ļ���С��Ϣ��
    //�������С��Ϣ�����ƶ�ȡ
    char c;
    while(size >0){
        c = fgetc(readfilePtr);
        fputc(c,writefilePtr);
        size--;
    }
    printf("������ɣ�\npath:%s--->%s\n",srcPath,desPath);
}

DWORD GetSrcFileSize(char *srcPath){
    HANDLE handle =CreateFile(srcPath,FILE_READ_EA,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
    if(handle == INVALID_HANDLE_VALUE) {
        printf("���ļ�ʧ��: %x\n", GetLastError());
        return 0;
    }
    DWORD size,highSize;
    size = GetFileSize(handle,&highSize);
    return size;
}
