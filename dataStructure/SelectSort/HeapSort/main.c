#include <stdio.h>
#include <stdlib.h>

void HeapSort(int arr[], int length);
void Heapify(int arr[], int heapTop, int length);
void PrintArray(int arr[], int length);
void Swap(int* a, int* b);

int main()
{
    int arr[10] = {2, 33, 3432, 222, 100, 235, 23, 788, 3, 24};
    HeapSort(arr, 10);
    PrintArray(arr, 10);
    return 0;
}

void HeapSort(int arr[], int length)
{
    int i;

    /*build heap*/
    for(i = length - 1; i >= 0; i--)
    {
        Heapify(arr, i, length);
    }

    while(length > 1)
    {
        Swap(&arr[0], &arr[length - 1]);
        Heapify(arr, 0, length - 1);
        length--;
    }
    return;

}

/*adjust heap top*/
void Heapify(int arr[], int heapTop, int length)
{
    int child = heapTop*2 + 1;

    if(child < length)
    {
        if((child + 1) < length && arr[child + 1] > arr[child])
        {
            child++;
        }
        if(arr[heapTop] < arr[child])
        {
            Swap(&arr[heapTop], &arr[child]);
            Heapify(arr, child, length);
        }
    }
    return;
}

void PrintArray(int arr[], int length)
{
    int i, count = 0;

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
