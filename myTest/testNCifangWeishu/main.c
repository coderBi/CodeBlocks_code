#include <stdio.h>
#include <stdlib.h>

int main()
{
   int i,x,y,last=1;
   printf("Input X and Y(X**Y):");
   scanf("%d**%d",&x,&y);
   for(i=1;i<=y;i++)
   {
       last=last*x%1000;

   }
   printf("The last finally is: %d",last);
   return 0;
}
