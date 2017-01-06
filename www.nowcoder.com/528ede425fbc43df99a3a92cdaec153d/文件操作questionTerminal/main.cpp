#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define MAX_STRING_LENGTH 30

vector<string> GetRecords(string fileName, int n){
    char szBuffer[MAX_STRING_LENGTH];
    FILE * pFileRead = fopen(fileName.c_str(),"r");
    if(!pFileRead){
        return NULL;
    }
    while(getline(szBuffer,MAX_STRING_LENGTH) != EOF){

    }
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
