/**********************************************
传统快排存在以下几点不足：
1，枢纽元一直选取第一个对于有些情况存在弊端
    如果已经排好序，这事算法复杂度N*N
2，用随机数确定枢纽元，可行，但是随机数算法本身
    开销比较大
3，取两段跟中间元中间值法，一定程度可以做到
    离散化
4，对于跟枢纽元一样的数据，两端处理要一直，否则
    可能造成不均衡

**********************************************/

#include <stdio.h>
#include <stdlib.h>

void ImproveQuickSort(int arr[], int first, int last);
void PrintArray(int arr[], int length);
void Swap(int* a, int* b);
void InsertSort(int arr[], int first, int last);
int Median(int arr[], int first, int last);

int main()
{
    int arr[11] = {4, 981, 10, -17, 0, -20, 29, 50, 8, 43, -5};
    ImproveQuickSort(arr, 0, 10);
    PrintArray(arr, 11);
    return 0;
}

void ImproveQuickSort(int arr[], int first, int last)
{
    /*length <= 3 use InsertSort*/
    if(last - first < 3)
    {
        InsertSort(arr, first, last);
    }
    else
    {
        int key = Median(arr, first, last);
        int i, j;

        for(i = first, j = last - 1; ;)
        {
            while(arr[++i] < key){}
            while(arr[--j] > key){}
            if(i < j)
            {
                Swap(&arr[i], &arr[j]);
            }
            else
                break;
        }/*for*/
        Swap(&arr[i], &arr[last - 1]);
        ImproveQuickSort(arr, first, i - 1);
        ImproveQuickSort(arr, i + 1, last);
    }/*else*/
    return;
}

void PrintArray(int arr[], int length)
{
    int i;
    int count = 0;

    for(i = 0; i < length; i++)
    {
        if(count != 0 && count%10 == 0)
        {
            printf("\n");
        }
        printf("%d  ", arr[i]);
    }
    return;
}

void Swap(int* a, int* b)
{
    int temp = *a;

    *a = *b;
    *b = temp;
    return;
}

void InsertSort(int arr[], int first, int last)
{
    int i;

    for(i = first + 1;i <= last; i++)
    {
        int temp = arr[i];
        int j = i - 1;

        while(j >= first && arr[j] > temp)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
    return;
}

int Median(int arr[], int first, int last)
{
    int mid = (first + last)/2;

    if(arr[first] > arr[mid])
    {
        Swap(&arr[first], &arr[mid]);
    }
    if(arr[first] > arr[last])
    {
        Swap(&arr[first], &arr[last]);
    }
    if(arr[mid] > arr[last])
    {
        Swap(&arr[last], &arr[mid]);
    }
    Swap(&arr[mid], &arr[last - 1]);
    return arr[last - 1];
}
