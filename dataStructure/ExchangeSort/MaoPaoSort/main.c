/************************************************
1，这里分别给出Array model下的：
    a)常规冒泡
    b)通过记录exchange位置改进
    c)在上面情况的基础上为了改进不对称性的双向冒泡
 2，linklist model 分别给出移动指针与直接改变数值的
        方法
***************************************************/
#include <stdio.h>
#include <stdlib.h>

struct DataType
{
    int number;
    struct DataType* next;
};

void NormalExchangeSortArrayModel(int arr[], int length);
void PrintArray(int arr[], int length);
int ExchangeSortInSubArray(int arr[], int low, int length);
void ExchangeTwoNumber(int* a, int* b);

void AddExchangePlaceSortArrayModel(int arr[], int length);
int AddExchangePlaceSortInSubArray(int arr[], int low, int length);

void BidirectionalBubbleSort(int arr[], int length);
int BidirectionalBubbleSortInSubArray(int arr[], int* left, int* right);

void SwapNumberExchangeSortLinklist(struct DataType* head);
void FreeLinkList(struct DataType* head);
void PrintLinklist(struct DataType* head);
struct DataType* SwapNumberInOneTrip(struct DataType* head, struct DataType* tail);

void SwapPointerExchangeSortLinklist(struct DataType* head);
struct DataType* SwapPointerInOneTrip(struct DataType** head, struct DataType* tail);
struct DataType* FindPreviousNode(struct DataType* head, struct DataType* findNode);

int main()
{
    int i;
    int arr1[10] = {2, 33, 3432, 44, 66, 235, 23, 788, 3, 24};
    int arr2[10] = {2, 33, 3432, 44, 66, 235, 23, 788, 3, 24};
    int arr3[10] = {2, 33, 3432, 44, 66, 235, 23, 788, 3, 24};
    struct DataType* head = NULL;
    struct DataType* ptr = (struct DataType*)malloc(sizeof(struct DataType));
    ptr->next = NULL;
    head = ptr;
    for(i = 0; i < 9; i++)
    {
        struct DataType* temp = (struct DataType*)malloc(sizeof(struct DataType));
        temp->next = NULL;
        ptr->next = temp;
        ptr = temp;
    }

    i = 0;
    for(ptr = head; ptr != NULL; ptr = ptr->next)
    {
        ptr->number = arr1[i++];
    }

    NormalExchangeSortArrayModel(arr1, 10);
    PrintArray(arr1, 10);
    printf("\n\n");

    AddExchangePlaceSortArrayModel(arr2, 10);
    PrintArray(arr2, 10);
    printf("\n\n");

    BidirectionalBubbleSort(arr3, 10);
    PrintArray(arr3, 10);
    printf("\n\n");

    SwapNumberExchangeSortLinklist(head);
    PrintLinklist(head);
    printf("\n\n");

    SwapPointerExchangeSortLinklist(head);
    PrintLinklist(head);
    FreeLinkList(head);
    return 0;
}

void NormalExchangeSortArrayModel(int arr[], int length)
{
    int i;
    int exchange;

    for(i = 0; i < length; i++)
    {
        exchange = ExchangeSortInSubArray(arr, i, length);
        if(!exchange)
        {
            break;
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

int ExchangeSortInSubArray(int arr[], int low, int length)
{
    int i;
    int flag = 0;

    for(i = length -1; i > low; i--)
    {
        if(arr[i] < arr[i-1])
        {
            ExchangeTwoNumber(&arr[i], &arr[i-1]);
            flag = 1;
        }
    }
    return flag;
}

void ExchangeTwoNumber(int* a, int* b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;

    return;
}

void AddExchangePlaceSortArrayModel(int arr[], int length)
{
    int exchangePlace = 0;

    while(exchangePlace < length - 1)
    {
        exchangePlace = AddExchangePlaceSortInSubArray(arr, exchangePlace, length);
        if(exchangePlace == length)
        {
            break;
        }
    }
    return;
}

int AddExchangePlaceSortInSubArray(int arr[], int low, int length)
{
    /*返回的交换点是length意味着没交换*/
    int exchangePlace = length;
    int i;

    for(i = length - 1; i > low; i--)
    {
        if(arr[i] < arr[i-1])
        {
            ExchangeTwoNumber(&arr[i], &arr[i-1]);
            exchangePlace = i;
        }
    }
    return exchangePlace;
}

void BidirectionalBubbleSort(int arr[], int length)
{
    int left = 0, right = length - 1;
    int flag;

    while(left < right)
    {
        flag = BidirectionalBubbleSortInSubArray(arr, &left, &right);
        if(flag == 0)
        {
            break;
        }
    }
    return;
}

int BidirectionalBubbleSortInSubArray(int arr[], int* left, int* right)
{
    int flag = 0;
    int i, exchangePlace = *left;

    for(i = *left; i < *right; i++)
    {
        if(arr[i] > arr[i+1])
        {
            ExchangeTwoNumber(&arr[i], &arr[i+1]);
            flag = 1;
            exchangePlace = i;
        }
    }

    *right = exchangePlace;

    for(i = *right; i > *left; i--)
    {
        if(arr[i] < arr[i-1])
        {
            ExchangeTwoNumber(&arr[i], &arr[i-1]);
            flag = 1;
            exchangePlace = i;
        }
    }
    *left = exchangePlace;

    return flag;
}

void SwapNumberExchangeSortLinklist(struct DataType* head)
{
    struct DataType* tail = NULL;

    while(tail != head)
    {
        tail = SwapNumberInOneTrip(head, tail);
    }
    return;
}

void FreeLinkList(struct DataType* head)
{
    struct DataType* temp = NULL;
    struct DataType* ptr = NULL;

    for(ptr = head; ptr != NULL; ptr = temp)
    {
        temp = ptr->next;
        free(ptr);
    }
}

void PrintLinklist(struct DataType* head)
{
    struct DataType* ptr = NULL;
    int count = 0;

    for(ptr = head; ptr != NULL; ptr = ptr->next)
    {
        if(count != 0 && count%10 == 0)
        {
            printf("\n");
        }
        printf("%d  ", ptr->number);
    }
}


/*仔细分析后发现单向链表不容易从后往前交换，所以修改为“落石”方案*/
struct DataType* SwapNumberInOneTrip(struct DataType* head, struct DataType* tail)
{
    struct DataType* ptr = NULL;
    struct DataType* newTail = head;

    for(ptr = head; ptr != tail && ptr->next != NULL; ptr = ptr->next)
    {
        if(ptr->number > ptr->next->number)
        {
            ExchangeTwoNumber(&(ptr->number), &(ptr->next->number));
            newTail = ptr;
        }
    }
    return newTail;

}

void SwapPointerExchangeSortLinklist(struct DataType* head)
{
    struct DataType* tail = NULL;

    while(tail != head)
    {
        tail = SwapPointerInOneTrip(&head, tail);
    }
    return;
}

struct DataType* SwapPointerInOneTrip(struct DataType** head, struct DataType* tail)
{
    struct DataType* ptr = NULL;
    struct DataType* newTail = *head;

    for(ptr = *head; ptr != tail && ptr->next != NULL; ptr = ptr->next)
    {
        if(ptr->number > ptr->next->number)
        {
            struct DataType* temp = FindPreviousNode(*head, ptr);
            struct DataType* forExchange = NULL;

            forExchange = ptr->next;
            ptr->next = ptr->next->next;
            forExchange->next = ptr;
            if(temp == NULL)
            {
                *head = ptr->next;
            }
            else
            {
                temp->next = forExchange;
            }
            newTail = ptr;
        }
    }
    return newTail;
}

struct DataType* FindPreviousNode(struct DataType* head, struct DataType* findNode)
{
    struct DataType* ptr = NULL;

    if(findNode == head)
    {
        return NULL;
    }
    for(ptr = head; ptr != NULL && ptr->next != findNode; ptr = ptr->next)
    {
        /*there is no content!*/
    }

    if(ptr == NULL)
    {
        /*node not found, exit abnormally */
        exit(1);
    }
    return ptr;
}
