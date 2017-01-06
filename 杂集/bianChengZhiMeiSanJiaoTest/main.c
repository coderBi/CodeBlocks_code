/*
本程序是要解决编程之美中三角形的部分问题；
这里是根据自己的思路处理为输入一个数组（>=3）
求这所有的数据进行拼装能不能组成一个三角形。
作者：毕威威
2014-5-24 00:22:38
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

int findMax(int input[],int count);
void maxTurnToZero(int input[],int count,int max);

int main()
{
    int input[MAX_SIZE];
    int sortedInput[MAX_SIZE];
    int count=0;
    char jianGeFu;
    int i;
    int j;
    //int maxInSorted,midInSorted,minInSorted;
    int threeBigNum[3];

    printf("请输入要分析的数据队列\n");
    printf("请注意每两个相邻的数字之间只可以输入一个字符进行间隔处理，\n输入为换行符时系统视为输入完成！\n");
    printf("测试程序只能支持100个以内数字的输入（最小输入个数是3个）\n");
    printf("\n\n");
    printf("你的输入为：\n");

    //数据采集
    scanf("%d",&input[0]);
    count=1;
    scanf("%c",&jianGeFu);
    while('\n'!=jianGeFu){
        scanf("%d",&input[count]);
        scanf("%c",&jianGeFu);
        count++;
    }

    //打印输入的数据
    printf("你输入的%d个数分别是：\n",count);
    for(i=0;i<count;i++){
        printf("%d  ",input[i]);
    }
    printf("\n");

    //数据重新排序，由大到小
    for(i=0;i<count;i++){
        sortedInput[i]=findMax(input,count);
        maxTurnToZero(input,count,sortedInput[i]);
    }


    printf("经过重新排序后的%d个数分别是：\n",count);
    for(i=0;i<count;i++){
        printf("%d  ",sortedInput[i]);
    }
    printf("\n");


    //接下来只需要处理已经由大到小排好序的数组sortedInput
    /*
    maxInSorted=sortedInput[0];
    midInSorted=sortedInput[1];
    minInSorted=sortedInput[2];
    */

    threeBigNum[0]=sortedInput[0];
    threeBigNum[1]=sortedInput[1];
    threeBigNum[2]=sortedInput[2];
    for(i=3;i<count;i++){
        threeBigNum[2]+=sortedInput[i];
        for(j=0;j<3;j++){
            sortedInput[j]=findMax(threeBigNum,3);
            maxTurnToZero(threeBigNum,3,sortedInput[j]);
        }

        threeBigNum[0]=sortedInput[0];
        threeBigNum[1]=sortedInput[1];
        threeBigNum[2]=sortedInput[2];
    }

    printf("最终的三个数据是：\n");
    printf("%d  %d  %d\n",threeBigNum[0],threeBigNum[1],threeBigNum[2]);
    if(threeBigNum[0]<(threeBigNum[1]+threeBigNum[2])){
       printf("输入的数据经过处理分析可以组成三角形！\n");
       }else{
           printf("输入的数据经过处理分析得知不可以组成三角形！\n");
       }
    return 0;
}


int findMax(int input[],int count){
    int max=input[0];
    int i;

    for(i=0;i<count;i++){
        if(max<input[i]){
            max=input[i];
        }
    }

    return max;

}

void maxTurnToZero(int input[],int count,int max){
    int i;

    for(i=0;i<count;i++){
        if(max==input[i]){
            input[i]=0;
            break;
        }
    }

}

/*失败代码，写的太麻烦,目的是将三个数排序*/
/*
int findMinInThree(int* maxInSorted,int* midInSorted,int* minInSorted){
    int min=*maxInSorted;
    int max=*maxInSorted;
    int mid=*maxInSorted;
    //找到最小的
    if(min>*midInSorted){
        min=*midInSorted;
    }

    if(min>*minInSorted){
        min=*minInSorted;
    }

    //找到最大的
    if(max<*midInSorted){
        max=*midInSorted;
    }

    if(max<*minInSorted){
        max=*minInSorted;
    }

    //找到中间的
    if(max==min){
        mid=max;
    }else  if((max>=*midInSorted)&&(min<=*midInSorted)){
         mid=*midInSorted;
    }



    return min;
}

*/
