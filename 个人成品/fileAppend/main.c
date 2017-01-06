#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char * filePath = "C:\\Users\\Administrator\\Desktop\\save\\bww1.txt"; //待处理的文件路径
    unsigned int i = 0;
    char * strBefore = "1    jdk       kdl                 3         4         ";  //最后一个数字之前的写入字符串
    unsigned int maxCount = 1 << 15;
    char strToAppend[255] = {0}; //最终插入的字符串

    FILE* file = fopen(filePath,"a"); //打开文件
    if(file == NULL){
        printf("文件加载失败，请检查文件路劲是否正确");
        exit(0);
    }
    while(i < maxCount){
        strcpy(strToAppend,strBefore);
        char arrFromInt[32] = {0};  //存储i转换成的字符串
        itoa(i,arrFromInt,10);  //这里也可以使用sprintf
        strcat(strToAppend,arrFromInt);
        strcat(strToAppend,"\n"); //最终添加的字符串
        fwrite(strToAppend,sizeof(char),strlen(strToAppend),file);
        i++;
    }
    return 0;
}
