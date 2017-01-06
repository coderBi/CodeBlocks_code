#include <stdio.h>
#include <stdlib.h>

int main()
{
    int (*p)[3]=NULL;
    int a[3]={1,2,3};
    p=&a;

    printf("%d\n%d\n%d\n",*p[0],*p[1],*p[2]);
    //cout<<p[0]<<"\t"<<*(p+1)<<"\t"<<*(p+2)<<"\t"<<endl;
    return 0;
}
