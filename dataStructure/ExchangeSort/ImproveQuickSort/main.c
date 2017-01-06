/**********************************************
��ͳ���Ŵ������¼��㲻�㣺
1����ŦԪһֱѡȡ��һ��������Щ������ڱ׶�
    ����Ѿ��ź��������㷨���Ӷ�N*N
2���������ȷ����ŦԪ�����У�����������㷨����
    �����Ƚϴ�
3��ȡ���θ��м�Ԫ�м�ֵ����һ���̶ȿ�������
    ��ɢ��
4�����ڸ���ŦԪһ�������ݣ����˴���Ҫһֱ������
    ������ɲ�����

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
