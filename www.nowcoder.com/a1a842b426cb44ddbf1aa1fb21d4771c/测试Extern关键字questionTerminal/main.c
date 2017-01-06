#include <stdio.h>
#include <stdlib.h>

//warning: arr initialized and declared 'extern'
//extern int arr[2] = {1,2};
extern int arr1[2];

int main()
{
    //undefined reference to arr1
    /*arr1[1] = 1;
    printf("arr: %d %d\n",arr1[0],arr1[1]);
    printf("Hello world!\n");*/
    return 0;
}
