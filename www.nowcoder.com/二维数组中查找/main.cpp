/**********************************************************************
������������һ����ά�����У�ÿһ�ж����մ����ҵ�����˳������
ÿһ�ж����մ��ϵ��µ�����˳�����������һ������������������һ��
��ά�����һ���������ж��������Ƿ��и�������
˼·�� �Ӿ������½ǿ�ʼ���ң����target�Ȳ��ҵ�С �������ƶ������
�����������ƶ���
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

    //<< boolalpha ������bool��ʽ��ӡ
    cout << "the result is " << boolalpha << Find(array,4) << endl;
    return 0;
}

