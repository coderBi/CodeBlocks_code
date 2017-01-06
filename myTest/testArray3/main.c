#include <stdio.h>
#include <stdlib.h>

void show()
{

}



//int show;       //redeclared as different kind of  symbol

int main()
{
    int a[2]={{1,2}};

    int (*p)[2]=a;            //二级变量

    //p=a;

    printf("a[1]=  %d   &a[1]=%d  \n",*(*p+1),*p+1);



    return 0;
}
