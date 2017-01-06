/*********************************************************
1，核心的东西与直接插入排序是一样的，这里写array model
2，这里的增量序列采用的是hibbard序列
3，直接与insertsort中的array model 比较运行时间的结果是
shellInsert明显要更优
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
