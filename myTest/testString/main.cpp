#include <iostream>
#include <string>

using namespace std;

int main()
{
    char* p="bww";  //此处给出了string到char*转换不支持的警告，即认为"bww"代表的是string类，这里存疑！！！同样的代码在vs上运行时没有警告的
    if(p[3]=='\0')
    {
        cout<<"yes'\\0'"<<endl;
    }
    else
    {
        cout<<"no!";
    }

    cout<<"----------------------------------\n\n\n";



    return 0;
}
