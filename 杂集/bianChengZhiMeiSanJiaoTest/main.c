/*
��������Ҫ������֮���������εĲ������⣻
�����Ǹ����Լ���˼·����Ϊ����һ�����飨>=3��
�������е����ݽ���ƴװ�ܲ������һ�������Ρ�
���ߣ�������
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

    printf("������Ҫ���������ݶ���\n");
    printf("��ע��ÿ�������ڵ�����֮��ֻ��������һ���ַ����м������\n����Ϊ���з�ʱϵͳ��Ϊ������ɣ�\n");
    printf("���Գ���ֻ��֧��100���������ֵ����루��С���������3����\n");
    printf("\n\n");
    printf("�������Ϊ��\n");

    //���ݲɼ�
    scanf("%d",&input[0]);
    count=1;
    scanf("%c",&jianGeFu);
    while('\n'!=jianGeFu){
        scanf("%d",&input[count]);
        scanf("%c",&jianGeFu);
        count++;
    }

    //��ӡ���������
    printf("�������%d�����ֱ��ǣ�\n",count);
    for(i=0;i<count;i++){
        printf("%d  ",input[i]);
    }
    printf("\n");

    //�������������ɴ�С
    for(i=0;i<count;i++){
        sortedInput[i]=findMax(input,count);
        maxTurnToZero(input,count,sortedInput[i]);
    }


    printf("��������������%d�����ֱ��ǣ�\n",count);
    for(i=0;i<count;i++){
        printf("%d  ",sortedInput[i]);
    }
    printf("\n");


    //������ֻ��Ҫ�����Ѿ��ɴ�С�ź��������sortedInput
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

    printf("���յ����������ǣ�\n");
    printf("%d  %d  %d\n",threeBigNum[0],threeBigNum[1],threeBigNum[2]);
    if(threeBigNum[0]<(threeBigNum[1]+threeBigNum[2])){
       printf("��������ݾ����������������������Σ�\n");
       }else{
           printf("��������ݾ������������֪��������������Σ�\n");
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

/*ʧ�ܴ��룬д��̫�鷳,Ŀ���ǽ�����������*/
/*
int findMinInThree(int* maxInSorted,int* midInSorted,int* minInSorted){
    int min=*maxInSorted;
    int max=*maxInSorted;
    int mid=*maxInSorted;
    //�ҵ���С��
    if(min>*midInSorted){
        min=*midInSorted;
    }

    if(min>*minInSorted){
        min=*minInSorted;
    }

    //�ҵ�����
    if(max<*midInSorted){
        max=*midInSorted;
    }

    if(max<*minInSorted){
        max=*minInSorted;
    }

    //�ҵ��м��
    if(max==min){
        mid=max;
    }else  if((max>=*midInSorted)&&(min<=*midInSorted)){
         mid=*midInSorted;
    }



    return min;
}

*/
