#include <stdio.h>
#include <stdlib.h>

void display(int*p,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("%d\n",p[i]);
    }
}
int main()
{
    int a[]={1,2,3,4};
    display(a,4);

    char b[]={'a','b','c'};
    display(b,3);  //乱对应，此处运行没有报错

    char* c="abc";
    display(c,3);  //换一种形式，都只是warning

    printf("*******************************\n\n\n\n");

    char p[]="bww";


    printf("%s\n",p);

    printf("*******************************\n\n\n\n");

    int* s=NULL;
    int bww=8;
    s=&bww;
    //s=7;
    printf("%d\n",s[0]);

    /*
    s[1]=10;
    printf("%d\n",s[1]);
    s[2]=11;
    printf("%d\n",s[2]);
    s[3]=12;
    printf("%d\n",s[3]);
    */

    s[1]=10;  //运行结果竟然可以正常？？？？？？   操作系统机制
    int i;
    for(i=0;i<2;i++)
    {
      printf("%d\n",s[i]);
    }

    return 0;
}
