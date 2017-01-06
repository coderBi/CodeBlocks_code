#include <stdio.h>
#include <stdlib.h>

int main()
{
    //char ch[10]="bww";    //没有问题，数组
    //char ch[10]={'b','w','w','\0','w'};
   /*
    char c1='b';
    char* ch;
    ch=&c1;

    ch[0]='w';
    ch[1]='q';
    ch[2]='q';
    ch[3]='q';
    ch[4]='q';
    ch[5]='\0';

    */

    /*
    //scanf("%s",ch);   //ch是指针，所指向的地址没有进行内存的分配，直接这样scanf写不进去东西
    printf("%s\n",ch);
    */

/*
    int numb=100;
    int i=0;
    int* p=NULL;
    p=&numb;
    p[1]=1;
    p[2]=2;    //p[1] p[2] 操作系统没有给与操作权限，所以会出错
    for(i=0;i<3;i++)
    {
        printf("%d\n",p[i]);
    }

*/
    printf("----------------------------------------------------\n");


    int* s=NULL;
    int bww=8;
    s=&bww;
    //s=7;
    printf("%d\n",s[0]);


    s[1]=10;  //运行结果竟然出错？？？？？？   同一段代码的两个不同地方的结果相反
    int i;
    for(i=0;i<2;i++)
    {
      printf("%d\n",s[i]);
    }

    return 0;
}
