# include <stdio.h>
double fun(int n)
 {
  double a , b = 1;
  double  sum = 0;
  for(a = 0 ; a <= n ; a++)
  {
     sum+=b/(a+(a++)) ;  ///出错  应该用++a  否则分母是0+0  表示错误
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
