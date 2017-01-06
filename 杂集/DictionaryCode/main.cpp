#include <iostream>

using namespace std;
void MatrixTranspose(char* in, char* out, int n);

int main()
{
    int n, i;
    cout << "Input n:" << endl;
    cin >> n;
    char inputArr[n*n];
    char outputArr[n*n];

    cout << "Input inputArr:" << endl;
    for(i = 0; i < n*n; i++)
    {
        cin >> inputArr[i];
    }
    MatrixTranspose(inputArr, outputArr, n);
    for(i = 0; i < n*n; i++)
    {
        cout << outputArr[i] << ' ';
    }
    return 0;
}

void MatrixTranspose(char* in, char* out, int n)
{
    int i;

    for(i = 0; i < n*n; i++)
    {
        int temp = i/n + (i%n)*n;
        out[temp] = in[i];
    }
    return;
}
