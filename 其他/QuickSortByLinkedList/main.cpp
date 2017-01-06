#include <iostream>

using namespace std;

typedef struct _NODE {
    int num;
    struct _NODE *next;
} NODE,*PNODE;

void printNodeList(PNODE phead){
    PNODE pnode = NULL;
    pnode = phead;
    while(pnode != NULL){
        cout << pnode->num << "\t";
        pnode = pnode->next;
    }
    cout << endl;
}

PNODE createNodeFromInt(int num){
    PNODE pnode = new NODE;
    pnode->num = num;
    pnode->next = NULL;
    return pnode;
}

PNODE IntArray2NodeLink(int arr[],int length){
    PNODE phead = NULL, ptail = NULL, pnode = NULL;
    int i = 0;
    for(i = 0; i < length; ++i){
        //创建一个node
        pnode = new NODE;
        pnode->num = arr[i];
        pnode->next = NULL;
        if(phead == NULL){
            //如果phead还是空的，就直接把phead ptail都赋值为pnode
            phead = ptail = pnode;
            continue;
        }
        ptail->next = pnode;
        ptail = pnode;
    }
    return phead;
}

PNODE addToNodeLinkedList(PNODE phead, PNODE pnode){
    if(pnode == NULL) return phead;
    pnode->next = NULL;
    //如果phead是空，就直接返回pnode
    if(phead == NULL){
        return pnode;
    }
    PNODE ptail = NULL;
    //先找到最后一个节点
    for(ptail = phead; ptail->next != NULL; ptail = ptail->next){}
    //追加到尾节点
    ptail->next = pnode;
    ptail = pnode;
    return phead;
}

PNODE quickSort(PNODE phead, PNODE pnode){
    if(phead == NULL) return NULL;
    PNODE ptemp = NULL, pnext = NULL;
    PNODE pleft = NULL, pright = NULL, pcenter = NULL;
    for(ptemp = phead; ptemp != NULL; ptemp = pnext){
        pnext = ptemp->next; //先将后续节点保存起来，因为在进行当前节点添加的时候，会对当前节点的next修改为null
        if(ptemp == pnode){
            pcenter = addToNodeLinkedList(pcenter,ptemp);
            continue;
        }
        if(ptemp->num < pnode->num || ptemp->num == pnode->num){
            pleft = addToNodeLinkedList(pleft,ptemp);
        } else {
            pright = addToNodeLinkedList(pright,ptemp);
        }
    }
    pleft = quickSort(pleft,pleft);
    pleft = addToNodeLinkedList(pleft,pcenter);
    pright = quickSort(pright,pright);
    pleft = addToNodeLinkedList(pleft,pright);
    return pleft;
}
int main()
{
    int arr[] = {10,9,8,7,6,5,4,3,2,1};
    PNODE phead = IntArray2NodeLink(arr,10);
    printNodeList(phead);
    phead = quickSort(phead,phead);
    printNodeList(phead);
    return 0;
}
