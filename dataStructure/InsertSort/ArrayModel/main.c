#include <stdio.h>
#include <stdlib.h>

#define N 10

void InsertSortForArrayModel(int* arr, int length);
void InsertOneNumber(int* arr, int subscript);
void PrintArray(int* arr, int length);

int main()
{
    int arr[N];
    int i;

    printf("Input your %d numbers:\n", N);
    for(i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }
    InsertSortForArrayModel(arr, N);
    PrintArray(arr, N);
    return 0;
}

void InsertSortForArrayModel(int* arr, int length)
{
    int i;

    for(i = 0; i < length; i++)
    {
        InsertOneNumber(arr, i);
    }
    return;
}

void InsertOneNumber(int* arr, int subscript)
{
    int i;
    int temp = arr[subscript];

    for(i = subscript - 1; i >= 0; i--)
    {
        if(arr[i] > temp)
        {
            arr[i + 1] = arr[i];
        }
        else
        {
            break;
        }
    }
    arr[i + 1] = temp;
    return;
}

void PrintArray(int* arr, int length)
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
