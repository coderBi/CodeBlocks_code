/*
�����Ǻ���Ⱥ�����۵����⣬��ײ����е�0���������������ҳ����е�2��5�ĸ�����ȡ�ý�Сֵ��
ʵ����2�϶����5�࣬�������⼴������ײ���5�ĸ���
ps:��̳�ϸ������ҳ�5�ĸ���������������ģ��������20���е�ȷ��7��0 �����м���3��0��Ҳ���ǿ��ܳ���0���м䲻�ܲ�����������
        ����ֻ������ж��ٸ�0��
ps:�����ٴ���֤����2*5ģ�ͣ����м���0����鲻������55555555555555~    7*8*9 = 504   *5=2520

ps:������������ʵ����ͳ��5�ĸ�����������������0�ǿɿ��أ���Ϊ������λ��0�ǲ����ܽ���β��������0�еġ�
    ����Ŀǰͳ��5�ĸ������������⣬���潫������д
*/
#include <stdio.h>
#include <stdlib.h>

int _GetCountOf5(int n)   //����ͳ�Ʒ��������⣬����ǰ���ظ�ͳ�Ƶ����
{
    int i, sum = 0;
    for(i = n; i > n/2; i--)
    {
        if(i%5 == 0)
        {
            sum += i/5;
            sum += _GetCountOf5(i/5);
        }
    }
    return sum;
}

int GetCountOf5(int n)
{
    int i, res = 0;
    for(i = 5; i <= n; i += 5)
    {
        int temp = i;
        while(temp%5 == 0)
        {
            res++;
            temp /= 5;
        }
    }
    return res;
}

int GetCountOfFive(int n)
{
    int i, res = 0, maxNum = 0;
    if(n < 5)
        return 0;
    for(i = n; i > n-5; i--)
    {
        if(i%5 == 0)
        {
            maxNum = i;
            break;
        }
    }
    res += maxNum/5;
    res += GetCountOfFive(maxNum/5);
    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("%d\n", GetCountOf5(n));
    printf("%d\n", GetCountOfFive(n));
    return 0;
}
