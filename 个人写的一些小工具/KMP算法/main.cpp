/*
    思路：
        ①：建立一个next数组，假设要查询子序列长度位 m，这个next数组长度也为m，记录每一位如果不匹配需要回溯的位数。
        ②：在查找的目标序列中，从index为0 开始向右移动，一直到某一位跟相应的要找的子序列中不同，就查询next数组，回溯相应的位置，又从子序列的 0 位置开始比对
        ③：next数组的建立：
            每一位之前的序列，前缀表达式与后缀表达式最长的相同序列就是需要回溯的长度。 例如 aaaa, 其前缀 aaa 与后缀 aaa 是最长相同子序列。那么如果下一位不同需要回溯 3
        ④：如果对于每一个长度都去对比所有前缀表达式与后缀表达式，这个复杂度也是糟糕的，进一步分析可以如下产生next数组
            ---next[0] = -1, 原因是如果第一个就不符合，就直接向前移动，那么回溯的长度就是 “-1”
            ---next[1] = 0, 原因是如果索引是 1 的不符合，如果进行回溯，最好的结果是 回溯到起始的索引 0。这个没有意义，所以不进行回溯二是从当前位就行新的查找
            ---i > 1, 假设next[i] = k,如果查找的子序列 subStr[i] = subStr[k] (第 i + 1位 与 第 k + 1 位也相同),那么 next[i + 1] = k + 1; 如果  subStr[i] != subStr[k]。
                那么这个问题的思路可以改成这样：前 k位中，第 k+1位 subStr[k] = 目前的 subStr[i] 的情况下(这前k+1个字符不满足需求) 求 next[k]。也即是如果subStr[i] != subStr[k],就将k 调整位 next[k]
                直到 subStr[k] == subStr[i] 或者 k < 0
*/

#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

//ofstream fs("out.txt");

int getSubStringIndex(string s1, string s2){
    //得到next数组
    int * next = new int[s2.size()]; //定长的数组在c++11之后最好用array而不用vector，这特更高效
    next[0] = -1; next[1] = 0;
    for(unsigned int i = 2; i < s2.length(); ++i){
        int k = next[i -1];
        while(k >= 0 && s2[i-1] != next[k]){
            k = next[k];
        }
        next[i] = k+1; //脚标在 0 ~ k 的是前缀跟后缀重复的
    }

    //查找第一个出现的s2，返回脚标
    int s1Size = s1.size(), s2Size = s2.size();
    int i = 0, j = 0;
    while(i < s2Size && j < s1Size){
        if(i != -1 && s1[j] != s2[i]){ //当前位不相同，就s1脚标不动，s2待比较的脚标移动到 next[i]
            // s1回溯，也就是s1当前位前面存在 next[i]位跟 s2的前 next[i]位是相同的，那么下一步 s2待查找的脚标是next[i]
            i = next[i];
        } else { //当前位相同， s1 s2脚标分别后移.  //这里还包含另一种情况，就是 i = -1，接下来设置 i = 0，j++
            i++;
            j++;
        }
    }
    delete[] next;
    return (i < s2Size) ? -1 : j - i;
}

int main()
{
    string s1, s2;
    while(cin >> s1 >> s2){
        if(-1 != getSubStringIndex(s1,s2)){
            //fs << "found" << endl;
            cout << "found" << endl;
        }
        else{
            //fs << "not found" << endl;
            cout << "not found" << endl;
        }
    }
    return 0;
}
