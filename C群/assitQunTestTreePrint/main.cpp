#include<stdio.h>
#include<string.h>
#include<malloc.h>
#define NULL 0
typedef struct BiTNode
{
   char data;
   struct BiTNode *Lchild,*Rchild;
}BiTNode,*BiTree;
BiTree Create(BiTree T)
{
   char ch;
   ch=getchar();
   getchar();
   if(ch=='#')   //这里
      T=NULL;
   else
   {
      if(!(T=(BiTNode *)malloc(sizeof(BiTNode))))
          printf("Error!");
      T->data=ch;
      T->Lchild=Create(T->Lchild);
      T->Rchild=Create(T->Rchild);   //这里
   }
   return T;
}
void Preorder(BiTree T)
{
    if(T)
    {
  printf("%d:%c\n",T,T->data);
  Preorder(T->Lchild);
  Preorder(T->Rchild);
    }
}
void zhongxu(BiTree T)
{
    if(T)
    {
  zhongxu(T->Lchild);
  printf("%d:%c\n",T,T->data);
  zhongxu(T->Rchild);
    }
}
void houxu(BiTree T)
{
    if(T)
    {
  houxu(T->Lchild);
  houxu(T->Rchild);
  printf("%d:%c\n",T,T->data);
    }
}
int main()
{
    BiTree T;
    printf("请输入数据:\n");
    T=Create(T);
    printf("先序遍历为:\n");
    Preorder(T);
    printf("中序遍历为:\n");
    zhongxu(T);
    printf("后序遍历为:\n");
    houxu(T);
    printf("\n");

    return 0;
}
