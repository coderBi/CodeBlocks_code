#include <iostream>
#include <windows.h>
#include <io.h>
#include <vector>
#include <algorithm>

using namespace std;

string delStr = "【US福利网fuli.us】-"; //要删掉的文字
string dirPath = "./btTemp/"; //要处理的文件夹目录

//因为这个页面跟codeblocks的环境是utf8 的，而window获得到的文件名，编码是gbk的。所以要想正确在获取的文件名中查找到上面定义的 delStr，需要进行编码转化
void translateUtf82GBK(string & utf8){
    int length1 = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
    WCHAR * wGBK = new WCHAR[length1];
    MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, wGBK, length1);

    int length2 = WideCharToMultiByte(CP_ACP, 0, wGBK, -1, NULL, 0, NULL, NULL);
    char * gbk = new char[length2];
    WideCharToMultiByte(CP_ACP, 0, wGBK, -1, gbk, length2, NULL, NULL);

    utf8 = gbk;
    delete wGBK;
    delete gbk;
}


int main()
{
    translateUtf82GBK( delStr); //转换成gbk

    struct _finddata_t find_data;  //这个结构定义在io.h
    long handle =  _findfirst((dirPath + "*.*").c_str(),&find_data);

    if(handle == -1){
        cout << "相应目录不存在" << endl;
        return 0;
    }

    vector<string> doneFileNames; //保存已经处理过了的文件名称，避免修改之后进行重复遍历。
    int count = 0;
    while(!_findnext(handle,&find_data)){ //这里比较奇怪，如果找到了文件返回 0. 所以这里有个 "!"
        if((find_data.attrib & _A_SUBDIR) != _A_SUBDIR){ //不是子目录
            if(strcmp(find_data.name, ".") == 0 || strcmp(find_data.name, "..") == 0){
                continue;
            }

            string oldName = find_data.name;

            if(find(doneFileNames.begin(), doneFileNames.end(), oldName) != doneFileNames.end()){ //这个文件已经处理过了
                continue;
            }

            string newName = oldName;
            unsigned int pos = string::npos;
            if((pos =newName.find(delStr)) != string::npos){ //string::npos不是 -1 是一个极大值
                newName.erase(pos, delStr.length());
            }

            cout << "old name : " << dirPath+oldName << endl;
            cout << "new name : " << dirPath + newName << endl;
            if(oldName != newName){
                rename((dirPath+oldName).c_str(), (dirPath + newName).c_str());
                doneFileNames.push_back(newName); //保存修改之后的名称
                count++;
                cout << "count = " << count << endl;
            }
        }
    }
    cout << "done, cout = " << count << endl;
    return 0;
}
