#include <stdio.h>
#include <stdlib.h>

void Merge(int arr[], int low, int mid, int high);
void PrintArray(int arr[], int length);
void MergeSort(int arr[], int length);

int main()
{
    int arr[11] = {4, 981, 10, -17, 0, -20, 29, 50, 8, 43, -5};
    MergeSort(arr, 11);
    //Merge(arr, 6, 7, 7);
    PrintArray(arr, 11);
    return 0;
}

void MergeSort(int arr[], int length)
{
    int i = 1;
    while(i < length)
    {
        int j = 0;
        while(j + i - 1 < length)
        {
            if(j + 2*i - 1 < length)
            {
                Merge(arr, j, j + i, j + 2*i -1);
            }
            else
            {
                Merge(arr, j, j + i, length - 1);
            }
            j += 2*i;
        }
        i *= 2;
    }
}

void PrintArray(int arr[], int length)
{
    int i;

    for(i = 0; i < length - 1; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("%d", arr[length - 1]);
    return;
}

void Merge(int arr[], int low, int mid, int high)  //这里的mid其实就是后面的步长
{
    if(mid > high)
        return;
    int i = low, j = mid, k = 0;
    int arr1[high - low + 1];
    while(i < mid && j <= high)
    {
        if(arr[i] <= arr[j])
        {
            arr1[k++] = arr[i];
            i++;
        }
        else
        {
            arr1[k++] = arr[j];
            j++;
        }
    }
    if(i == mid)
    {
        while(j <= high)
            arr1[k++] = arr[j++];
    }
    else
    {
        while(i < mid)
            arr1[k++] = arr[i++];
    }
    for(i = low, k = 0; i <= high; i++, k++)
    {
        arr[i] = arr1[k];
    }
    return;
}
