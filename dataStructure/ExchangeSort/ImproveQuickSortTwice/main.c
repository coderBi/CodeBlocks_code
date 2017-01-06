/**********************************************
1,��Ϊ��������ĸĽ����ŵ��㷨�д��������ȶ������
�������Լ������µĸĽ���������Ҫ���ڴ��������ƶ��Ǳ�ʱ
�Ƿ�����ȵ���������⴦������Ҳ���л������Ի��ǲ��ȶ��ģ���Ȼ
������������ͬʱ��֤�����鲻��Խ��~

2,ע�⣬���ﴦ�����ȫ����һ��������ȫ�����ƶ���~
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
            while(arr[++i] <= key && i < j){}  //�޸ĵ�  =
            while(arr[--j] >= key && i < j){}
            if(i < j)
            {
                Swap(&arr[i], &arr[j]);
                continue;
            }
            else if(i != first && j != last - 1)  //�м���������i �����������Կ϶�ͣ�ڴ���key�ĵ�
                Swap(&arr[i], &arr[last - 1]);
            break;

        }/*for*/
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
