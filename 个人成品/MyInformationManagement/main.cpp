#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include <windows.h>

#include "DataModel.h"

using namespace std;

void PrintHead();
struct DataModel *Create();
void PrintDataset(struct DataModel* head);
void SaveDataset(struct DataModel* head, string fileName);
struct DataModel* LoadFile(string fileName);
char* DeleteSpace(char* ch);
int Char2Int(char* ch);
int Char2Int(const char* ch);
int SafeTestString2Int(string str);
void TestGradeRenge(int* grade) throw(int);
struct DataModel* AddItem(struct DataModel* person);
int Find(struct DataModel* head);
void PrintOneItem(struct DataModel* person);
void ChangeItem(struct DataModel* person);
struct DataModel* DeleteItem(struct DataModel* person);
void RemoveDataset(struct DataModel* person);

int main()
{
    string strMenu;
    string fileName = "new";
    struct DataModel *person = NULL;

    PrintHead();
    cin >> strMenu;
    while(strMenu.compare(""))
    {
        if(strMenu.compare("quit") == 0)
        {
            break;
        }
        else if(strMenu.compare("create") == 0)
        {
            if(fileName != "new")
            {
                cout << "save file firstly!" << endl;
                SaveDataset(person, fileName);
            }
            person = Create();
        }
        else if(strMenu.compare("view") == 0)
        {
            PrintDataset(person);
        }
        else if(strMenu.compare("save") == 0)
        {
            SaveDataset(person, fileName);
        }
        else if(strMenu.compare("load") == 0)
        {
            string strTmpName;
            cout << "input filename ->" << endl;
            cin >> strTmpName;
            while(strTmpName == "new")
            {
                cout << "the file can not be named \'new\'" << endl;
                cout << "input filename ->" << endl;
                cin >> strTmpName;
            }
            person = LoadFile( strTmpName);
            //如果确实加载成功了，就修改fileName，否则fileName保持为“new”
            if(person){
                fileName = strTmpName;
            } else {
                fileName = "new";
            }
        }
        else if(strMenu.compare("find") == 0)
        {
            Find(person);
        }
        else if(strMenu.compare("change") == 0)
        {
            ChangeItem(person);
        }
        else if(strMenu.compare("add") == 0)
        {
            person = AddItem(person);
        }
        else if(strMenu.compare("delete") == 0)
        {
            person = DeleteItem(person);
        }
        else if(strMenu.compare("remove") == 0)
        {
            RemoveDataset(person);
            person = NULL;
            fileName = "new";
        }
        else if(strMenu.compare("help") == 0)
        {
            PrintHead();
        }
        cin >> strMenu;
    }
    return 0;
}

void PrintHead()
{
    cout << "************************************************"<<endl;
    cout << "************InformationManagement***************"<<endl;
    cout << "[create]   create a new form                   *"<<endl;
    cout << "[view]     View your dataset                   *"<<endl;
    cout << "[save]     save your form to a file            *"<<endl;
    cout << "[add]      add one item to dataset             *"<<endl;
    cout << "[delete]   delete one item by id               *"<<endl;
    cout << "[find]     find one item                       *"<<endl;
    cout << "[change]   change one item                     *"<<endl;
    cout << "[remove]   remove a form existed               *"<<endl;
    cout << "[load]     load a form from a file             *"<<endl;
    cout << "[quit]     close the information system        *"<<endl;
    cout << "[help]     view the instructions               *"<<endl;

    cout << "************************************************"<<endl;

}

struct DataModel *Create()
{
    int id = 0;
    string flag = "Y";
    struct DataModel *person = NULL;
    struct DataModel *head = NULL;
    struct DataModel *tail = NULL;

    while(flag == "Y")
    {
        person = new struct DataModel;
        if(id == 0 )
        {
            head = person;
            tail = person;
        }
        else
        {
            tail->next = person;
            tail = person;
        }
        cout << "input your dataSet->" <<endl;
        cout << "id = " << id << endl;
        person->id = id;
        cout << "input \'name\'->";
        cin >> person->name;
        cout << "input \'address\'->";
        cin >> person->address;
        cout << "input \'grade\'->" << endl;
        cout << "Chinese value ->" << endl;
        cin >> person->grade.chinese;
        TestGradeRenge(&person->grade.chinese);

        cout << "math value ->" << endl;
        cin >> person->grade.math;
        TestGradeRenge(&person->grade.math);
        cout << "English value ->" << endl;
        cin >> person->grade.English;
        TestGradeRenge(&person->grade.English);
        person->next = NULL;
        id++;

        cout << "continue ? (Y: yes N: no)";
        cin >> flag;
    }
    return head;
};

void PrintDataset(struct DataModel* head)
{
    struct DataModel* person = head;

    cout.setf(ios::left);
    cout.fill(' ');
    cout << setw(5) << "id";
    cout << setw(10) << "name";
    cout << setw(20) << "address";
    cout << setw(10) << "Chinese";
    cout << setw(10) << "math";
    cout << setw(10) << "English" << endl;
    while(person != NULL)
    {
        PrintOneItem(person);
        person = person->next;
    }
    //cout.setf(ios::right);
}

void SaveDataset(struct DataModel* head, string fileName)
{
    char buf[80];
    string name;
    struct DataModel* person = head;

    getcwd(buf, sizeof(buf));
    if(fileName == "new")
    {
        cout << "input filename-> ";
        cin >> fileName;
        name = (string)buf + "\\save" + "\\" + fileName + ".txt";
        ifstream in(name.c_str(), ios::in);
        while(in)
        {
            cout << "the file is already existed" << endl;
            cout << "input filename-> ";
            cin >> fileName;
            name = (string)buf + "\\save" + "\\" + fileName + ".txt";
            in.open(name.c_str());
        }
        in.close();
    }

    name = (string)buf + "\\save" + "\\" + fileName + ".txt";
    ofstream out(name.c_str(), ios::out);
    out.setf(ios::left);
    out.fill(' ');
    out << setw(5) << "id";
    out << setw(10) << "name";
    out << setw(20) << "address";
    out << setw(10) << "Chinese";
    out << setw(10) << "math";
    out << setw(10) << "English" << endl;
    while(person != NULL)
    {
        out << setw(5) << person->id;
        out << setw(10) << person->name;
        out << setw(20) << person->address;
        out << setw(10) << person->grade.chinese;
        out << setw(10) << person->grade.math;
        out << setw(10) << person->grade.English;
        out << endl;
        person = person->next;
    }
    out.setf(ios::right);
    out.close();
}

struct DataModel* LoadFile(string fileName)
{
    char buf[80];
    string name;
    char ch[100];
    struct DataModel* head = NULL;
    struct DataModel* person = NULL;
    struct DataModel* tail = NULL;

    getcwd(buf, sizeof(buf));
    name = (string)buf + "\\save" + "\\" + fileName + ".txt";
    ifstream in(name.c_str(), ios::in);
    if(!in)
    {
        cout << "the file does not exist" << endl;
        return NULL;
    }
    in.getline(ch, sizeof(ch));

    while(in.getline(ch, 6, ' '))
    {
        char* ch1;
        int chLength = 0;
        person = new struct DataModel;
        if(head == NULL)
        {
            head = person;
            tail = person;
        }
        else
        {
            tail->next = person;
            tail = person;
        }

        ch1 = DeleteSpace(ch);
        chLength = strlen(ch1);
        in.ignore(4 - chLength);
        person->id = Char2Int(ch1);

        in.getline(ch, 11, ' ');
        person->name = (string)ch;
        chLength = strlen(ch);
        in.ignore(9 - chLength);

        in.getline(ch, 21, ' ');
        person->address = (string)ch;
        chLength = strlen(ch);
        in.ignore(19 - chLength);

        in.getline(ch, 11, ' ');
        ch1 = DeleteSpace(ch);
        chLength = strlen(ch1);
        in.ignore(9 - chLength);
        person->grade.chinese = Char2Int(ch1);

        in.getline(ch, 11, ' ');
        ch1 = DeleteSpace(ch);
        chLength = strlen(ch1);
        in.ignore(9 - chLength);
        person->grade.math = Char2Int(ch1);

        in.getline(ch, 11);
        ch1 = DeleteSpace(ch);
        chLength = strlen(ch1);
        //in.ignore(11 - chLength);
        person->grade.English = Char2Int(ch1);
        person->next = NULL;

    }
    return head;
}

char* DeleteSpace(char* ch)
{
    char* ch1 = ch;
    while(*ch1 != '\0' && *ch1 != ' ')
    {
        ch1++;
    }
    *ch1 = '\0';
    return ch;
}

int Char2Int(char* ch)
{
    char* ch1 = ch;
    int sum = 0;
    while(*ch1 != '\0')
    {
        if(*ch1 < '0' || *ch1 > '9')
        {
            runtime_error err("No number_string to int!");
            throw err;
        }
        sum = sum*10 + *ch1 - '0';
        ch1++;
    }
    return sum;
}

int Char2Int(const char* ch)
{
    const char* ch1 = ch;
    int sum = 0;
    while(*ch1 != '\0')
    {
        if(*ch1 < '0' || *ch1 > '9')
        {
            runtime_error err("No number_string to int!");
            throw err;
        }
        sum = sum*10 + *ch1 - '0';
        ch1++;
    }
    return sum;
}

void TestGradeRenge(int* grade) throw(int)
{
    cout <<"test里面的grade： "<< *grade <<endl;
    Sleep(1000);
    try
    {
        if(0 > *grade || *grade > 100)
        {
        throw(-1);
        }
    }
    catch(int e)
    {
        if(e == -1)
        {
            cout << "grade must between 0~100, input again ->" << endl;
            cin >> *grade;
            cout << *grade << endl;
            TestGradeRenge(grade);
        }
    }
   return;
}

int Find(struct DataModel* head)
{
    string key;
    int amount = 0;
    struct DataModel* node = head;

    cout << "input your keyword: " << endl;
    cin >> key;

    while(node != NULL)
    {
        if(-1 != SafeTestString2Int(key))
        {
            int num = Char2Int(key.c_str());
            if(num == node->id || num == node->grade.chinese
               || num == node->grade.math
               || num == node->grade.English
               || key == node->name || key == node->address)
            {
                PrintOneItem(node);
                amount++;
            }
        }
        else
        {
            if(key == node->name || key == node->address)
            {
                PrintOneItem(node);
                amount++;
            }
        }
        node = node->next;
    }
    return amount;
}

struct DataModel* AddItem(struct DataModel* person)
{
    struct DataModel* new_Node = new struct DataModel;
    int id = 0;
    struct DataModel* node = person;

    if(node != NULL)
    {
        while(node->next != NULL)
        {
            node = node->next;
        }
        id = node->id + 1;
    }

    new_Node->id = id;
    new_Node->next = NULL;
    cout << "input \'name\'->";
    cin >> new_Node->name;
    cout << "input \'address\'->";
    cin >> new_Node->address;
    cout << "input \'grade\'->" << endl;
    cout << "Chinese value ->" << endl;
    cin >> new_Node->grade.chinese;
    TestGradeRenge(&new_Node->grade.chinese);

    cout << "math value ->" << endl;
    cin >> new_Node->grade.math;
    TestGradeRenge(&new_Node->grade.math);
    cout << "English value ->" << endl;
    cin >> new_Node->grade.English;
    TestGradeRenge(&new_Node->grade.English);

    if(new_Node->id == 0)
    {
        return new_Node;
    }
    else
    {
        node->next = new_Node;
        return person;
    }
}

void PrintOneItem(struct DataModel* person)
{
    cout.setf(ios::left);
    cout << setw(5) << person->id;
    cout << setw(10) << person->name;
    cout << setw(20) << person->address;
    cout << setw(10) << person->grade.chinese;
    cout << setw(10) << person->grade.math;
    cout << setw(10) << person->grade.English;
    cout << endl;
    return;
}

int SafeTestString2Int(string str)
{
    int length = 0;
    const char* ch = str.c_str();

    while(*ch != '\0')
    {
        if(*ch < '0' || *ch > '9')
        {
            return -1;
        }
        else
        {
            length++;
        }
        ch++;
    }
    return length;
}

void ChangeItem(struct DataModel* person)
{
    int id;
    struct DataModel* node = person;

    if(Find(person) == 0)
    {
        cout << "no information found" << endl;
        return;
    }

    cout << "input the id you want to change:" << endl;
    cin >> id;

    while(node != NULL)
    {
        if(id == node->id)
        {
            cout << "input \'name\'->";
            cin >> node->name;
            cout << "input \'address\'->";
            cin >> node->address;
            cout << "input \'grade\'->" << endl;
            cout << "Chinese value ->" << endl;
            cin >> node->grade.chinese;
            TestGradeRenge(&node->grade.chinese);

            cout << "math value ->" << endl;
            cin >> node->grade.math;
            TestGradeRenge(&node->grade.math);
            cout << "English value ->" << endl;
            cin >> node->grade.English;
            TestGradeRenge(&node->grade.English);
            break;
        }
        else
        {
            node = node->next;
        }
    }
}

struct DataModel* DeleteItem(struct DataModel* person)
{
    int id;
    struct DataModel* node = person;
    struct DataModel* callBack = person;
    struct DataModel* pre_Node = person;

    if(Find(person) == 0)
    {
        cout << "no information found" << endl;
        return callBack;
    }

    cout << "input the id you want to delete:" << endl;
    cin >> id;

    while(node != NULL)
    {
        if(id == node->id)
        {
            if(node == person)
            {
                callBack = node->next;

            }
            else
            {
                while(pre_Node->next != node)
                {
                    pre_Node = pre_Node->next;
                }
                pre_Node->next = node->next;
            }
            free(node);
            node = NULL;
            break;
        }
        else
        {
            node = node->next;
        }
    }
    return callBack;
}

void RemoveDataset(struct DataModel* person)
{
    struct DataModel* node = person;
    struct DataModel* next_Node = person;

    while(node != NULL)
    {
        next_Node = node->next;
        free(node);
        node = next_Node;
    }
}
