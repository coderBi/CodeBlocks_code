#include <stdio.h>
#include <stdlib.h>

void SelectSort(int arr[], int length);
void PrintArray(int arr[], int length);
void Swap(int* a, int* b);
int main()
{
    int arr[10] = {2, 33, 3432, 222, 100, 235, 23, 788, 3, 24};
    SelectSort(arr, 10);
    PrintArray(arr, 10);
    return 0;
}

void SelectSort(int arr[], int length)
{
    int i, j;

    for(i = 0; i < length; i++)
    {
        for(j = i + 1; j < length; j++)
        {
            if(arr[i] > arr[j])
            {
                Swap(&arr[i], &arr[j]);
            }
        }
    }
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
        count++;
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
