#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v1, v2;
    v1.push_back(100);
    v2.push_back(1);
    v2.push_back(2);

    v1.clear();
    v1.insert(v1.end(), v2.begin(), v2.end());

    cout << "size: " << v1.size() << endl;
    for(unsigned int i = 0; i< v1.size(); ++i){
        cout << v1[i] << " ";
    }
    cout << endl;
    return 0;
}
