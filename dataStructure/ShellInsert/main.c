/*********************************************************
1�����ĵĶ�����ֱ�Ӳ���������һ���ģ�����дarray model
2��������������в��õ���hibbard����
3��ֱ����insertsort�е�array model �Ƚ�����ʱ��Ľ����
shellInsert����Ҫ����
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

void ShellSortArrayModel(int* arr, int length);
void SortForOneIncrement(int* arr, int length, int increment);
int GetMostIncrement(int length);
void PrintArray(int* arr, int length);

int main()
{
    int arr[10] = {2, 34, 4353, 22, 335, 446, 223, 356, 223, 356};

    ShellSortArrayModel(arr, 10);
    PrintArray(arr, 10);
    return 0;
}

void ShellSortArrayModel(int* arr, int length)
{
    int mostIncrement;
    int i;

    mostIncrement = GetMostIncrement(length);
    for(i = mostIncrement -1; i >= 1; i = (i + 1)/2 - 1)
    {
        SortForOneIncrement(arr, length, i);
    }

}

void SortForOneIncrement(int* arr, int length, int increment)
{
    int i;

    for(i = 0; i < length; i += increment)
    {
        int temp = arr[i];
        int j;

        for(j = i - increment; j >= 0; j -= increment)
        {
            if(arr[j] > temp)
            {
                arr[j + increment] = arr[j];
            }
            else
            {
                break;
            }
        }
        arr[j + increment] = temp;
    }
}

int GetMostIncrement(int length)
{
    int index = 0;

    while(length/2 != 0)
    {
        index++;
        length /= 2;
    }
    return pow(2, index);
}

void PrintArray(int* arr, int length)
{
    int i;
    int count = 0;

    for(i = 0; i < length; i++)
    {
        if(count != 0 && count/10 == 0)
        {
            printf("\n");
        }
        printf("%d  ", arr[i]);
    }
}
