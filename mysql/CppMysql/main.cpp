#include <iostream>
#include "MySQL_Dao.h"

using namespace std;

int main()
{
    MySQL_Dao mysql;
    string sql;

    //test add
    /*
    sql = "insert into te11st(content) values('test1'),('test2')";
    long iRows = mysql.add(sql);
    cout << "totally insert: " << iRows << " rows" << endl;*/

    //test query list
    /*
    sql = "select * from test";
    vector<MYSQL_ROW> vList = mysql.queryList(sql);
    for(unsigned int i = 0; i < vList.size(); ++i){
        MYSQL_ROW row = vList[i];
        cout << "{ " << row[0] << ", " << row[1] << " }" << endl;
    } */

    //test query_row
    //*
    try{
        sql = "select * from test where id=1";
        MYSQL_ROW qRow = mysql.queryRow(sql);
        cout << "{ " << qRow[0] << ", " << qRow[1] << " }" << endl;
    } catch(string & e){
        cout << "query_row fail, detail reason is: \n" << e << endl;
    }
    //*/

    //test query_one
    //*
    try{
        sql = "select content from test where id=1";
        string content = mysql.queryOne(sql);
        cout << content << endl;
    } catch(string & e){
        cout << "query_one fail, detail reason is: \n" << e << endl;
    }
    //*/

    //test deleteItem
    /*sql = "delete from test where id = 2";
    long iRows = mysql.deleteItem(sql);
    cout << "totally delete: " << iRows << " rows" << endl;*/

    //test  updateData
    /*
    sql = "update test set `content`='修改后...' where id=3";
    long iRows = mysql.updateData(sql);
    cout << "totally update: " << iRows << " rows" << endl;
    */

    return 0;
}
