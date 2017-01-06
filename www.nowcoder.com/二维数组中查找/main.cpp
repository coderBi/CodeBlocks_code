/**********************************************************************
问题描述：在一个二维数组中，每一行都按照从左到右递增的顺序排序，
每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个
二维数组和一个整数，判断数组中是否含有该整数。
思路： 从矩阵左下角开始查找，如果target比查找的小 就向上移动，如果
比它大向右移动。
**********************************************************************/
#include <iostream>
#include <vector>

using namespace std;

bool Find(vector<vector<int> > array, int target){
    int iRowCount = array.size();
    int iColCount = array[0].size();
    for(int i = iRowCount -1, j = 0; i >= 0&& j < iColCount;){
        if(target == array[i][j]){
            return true;
        }
        else if(target < array[i][j]){
            i--;
        }
        else
            j++;
    }
    return false;
}

int main()
{
    int noVector[][3] = {{1,2,3},{4,5,6},{7,8,9}};
    vector<vector<int> > array;
    for(int i = 0; i < 3; i++){
        vector<int> temp;
        for(int j = 0; j < 3; j++){
            temp.push_back(noVector[i][j]);
        }
        array.push_back(temp);
    }

    //<< boolalpha 控制以bool方式打印
    cout << "the result is " << boolalpha << Find(array,4) << endl;
    return 0;
}

