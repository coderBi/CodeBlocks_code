#include <iostream>

using namespace std;

union myUnion
{
    struct myStruct1
    {
        char c1;
        char c2;
        char c3;

    }myS1;

    struct myStruct2
    {
        int I1;

    }myS2;
};

int main()
{
    cout << "union myUnion��С��  " <<sizeof(union myUnion)<<endl;
    return 0;
}
