# include <stdio.h>
double fun(int n)
 {
  double a , b = 1;
  double  sum = 0;
  for(a = 0 ; a <= n ; a++)
  {
     sum+=b/(a+(a++)) ;  ///����  Ӧ����++a  �����ĸ��0+0  ��ʾ����
	 b++;


  }

return sum;

}
int main(void)
{
   int x;
   scanf("%d",&x);
   printf("%f\n",fun(x));
   return 0;
}
