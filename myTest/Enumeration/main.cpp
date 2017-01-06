#include <iostream>

using namespace std;

int main()
{
    enum
    {
        Monday,
        Tuesday,
        Wensday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    }Week = Monday;
    cout << Week << endl;
    return 0;
}
