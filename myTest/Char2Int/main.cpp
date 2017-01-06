#include <iostream>

using namespace std;

char* DeleteSpace(char* ch)
{
    char* ch1 = ch;
    while(*ch1 != '\0' && *ch1 != ' ')
    {
        ch1++;
    }
    *ch1 = '\0';
    return ch;
}

int Char2Int(char* ch)
{
    char* ch1 = ch;
    int sum = 0;
    while(*ch1 != '\0')
    {
        sum = sum*10 + *ch1 - '0';
        ch1++;
    }
    return sum;
}


int main()
{
    char ch[20] = "123456   ";
    char* ch1 = DeleteSpace(ch);
    int a = Char2Int(ch1);
    cout << a << endl;
    return 0;
}
