/*
    ①：把这个文件加入到path里面，然后cd到项目根目录，这样可以不用提供项目根目录参数到命令参数，否则需要使用 myIde -option filepath形式命令
    ②：这个程序没有像其他ide那样处理dll调用与lib引入的问题
    ③：为了防止在某个目录出现不可预料的错误操作，这里对我本人的project类型进行约束。要想成功运行这个程序，
        需要在项目根目录放置一个 .myIde文件。目前这个文件一是起到了标识的作用，二是保存配置最后生成的exe的名称跟是否是C++项目还是纯C项目
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <io.h>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

string baseDir = ""; //当前运行目录
bool isCpp = true; //当前是否是C++项目，如果是值为true，不是为false。默认true表示C++项目。
string debugDir = "";
string oDir = ""; //存放汇编后的 .o文件位置
string binDir = "";
string workDir = ""; //本ide运行过程中存放数据的空间
string iDir = ""; //存放预处理后的 .i文件位置
string sDir = ""; //存放编译后的 .s文件位置
string exeName = "default"; //最后生成的exe的名称，配置在.myIde文件中

//创建管道
bool createMyPipe(HANDLE & hRead, HANDLE & hWrite){
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;
    if(0 == CreatePipe(&hRead, &hWrite, &sa, 0)){
        return false;
    }
    return true;
}

/*
    *hRead里面读取到内容输出到filePath路径的文件中。
    *mode 是文件打开的方式
*/
bool translateContentFromPipe2File(HANDLE & hRead, string filePath, std::ios_base::openmode mode){
    fstream f(filePath.c_str(), mode);
    if(NULL == f){
        return false;
    }
    char buff[1024 + 1] = {0};
    DWORD len = 0;
    while(0 != ReadFile(hRead, buff, 1024, &len,NULL)){
        f << buff;
        if(len < 1024){
            break;
        }
    }
    return true;
}

//运行一个子进程，并且用管道捕获输出
bool execCmdWithMyPipe(HANDLE & hRead, HANDLE & hWrite, const char * cmd, const char * param, bool isSyschronized, WORD wCmdShow){
    //-----  start 这段代码处理形参类型从 const char * 到 char * 以匹配CreateProcess的调用 ------------///
    char * pCommand = NULL;
    char * pParam = NULL;
    if(cmd != NULL){
        pCommand = new char[strlen(cmd) + 1];
        ZeroMemory(pCommand, strlen(cmd) + 1);
        strcpy(pCommand, cmd);
    }
    if(param != NULL){
        pParam = new char[strlen(param) + 1];
        ZeroMemory(pParam, strlen(param) + 1);
        strcpy(pParam, param);
    }
    //-----  end ------------///

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    si.cb = sizeof(STARTUPINFO);
    GetStartupInfo(&si);
    si.hStdError = hWrite;
    si.hStdOutput = hWrite;
    si.wShowWindow = wCmdShow;
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    if(0 == CreateProcess(pCommand,pParam,NULL,NULL, TRUE, CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi)){
        delete[] pCommand;
        delete[] pParam;
        return false;
    }
    delete[] pCommand;
    delete[] pParam;
    if(isSyschronized){
        unsigned long waitResult = WaitForSingleObject(pi.hProcess, INFINITE); //等待完成
        if(WAIT_FAILED == waitResult)
            return false;
    }
    return true;
}

string translateUtf82GBK(string utf8){ //utf8转 GBK
    int length1 = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
    WCHAR * wGBK = new WCHAR[length1];
    MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, wGBK, length1);

    int length2 = WideCharToMultiByte(CP_ACP, 0, wGBK, -1, NULL, 0, NULL, NULL);
    char * gbk = new char[length2];
    WideCharToMultiByte(CP_ACP, 0, wGBK, -1, gbk, length2, NULL, NULL);

    utf8 = gbk;
    delete wGBK;
    delete gbk;
    return utf8;
}

bool checkFileExist(string path){ //检查当前路径的文件是否存在
    FILE * file = fopen(path.c_str(), "r");
    if(!file)
        return false;
    fclose(file);
    return true;
}

bool checkFileEmpty(string path){ //检查文件是否为空，没有任何内容
    if(!checkFileExist(path))
        throw string("文件不存在");
    FILE * file = fopen(path.c_str(), "r");
    fseek(file,0,SEEK_END);
    if(0 == ftell(file)){
        return true;
    }
    fclose(file);
    return false;
}

bool checkDirExist(string path){ //检查当前路径的文件夹是否存在
    bool res = true;
    struct _finddata_t fd;
    long handle = _findfirst((path + "*.*").c_str(), &fd); //查找 *.*文件类型
    if(-1 == handle){ //打开一个目录失败，说明不存在
        res = false;
    }
    _findclose(handle);
    return res;
}

//检查文件夹下面是否存在某一种文件类型，这种检查不会进行子目录的遍历。参数type的取值例如: c cpp exe *
bool checkFileTypeInDir(string dir, string type){
    bool toReturn = false;
    if(!checkDirExist(dir)){
        return false;
    }
    _finddata_t fd;
    long handle = _findfirst((dir + "*." + type).c_str(), &fd);
    if(-1 != handle){
        do{
            if(!strcmp(fd.name, ".") || !strcmp(fd.name, "..") || _A_SUBDIR & fd.attrib) //不进行子目录的遍历，同时这里可以筛选像"test.c"这样命名的文件夹
                continue;
            toReturn = true;
            break;
        }while(_findnext(handle, &fd) == 0);
    }
    _findclose(handle);
    return toReturn;
}

//删除一个目录
bool removeDir(string dir){
    if(!checkDirExist(dir))
        return true;
    //递归删除 文件夹里面的内容
    _finddata_t fd;
    long handle = _findfirst((dir + "*.*").c_str(), &fd);
    if(-1 != handle){
        do{
            if(!strcmp(".",fd.name) || !strcmp("..",fd.name))
                continue;
            if(_A_SUBDIR == (fd.attrib & _A_SUBDIR)){
                if(!removeDir(dir + fd.name + "/"))
                    return false;
            }
            //属性是文件  直接删除 remove函数成功返回0 失败返回-1 并且会设置error
            else if(0 != remove((dir + fd.name).c_str()))
                return false;

        }while(_findnext(handle, &fd) == 0);
    }
    _findclose(handle);

    //删除文件夹本身 RemoveDirectory函数失败返回0 成功返回非0
    return !RemoveDirectory(dir.c_str()) ? false : true;
}

void printFileContent2Console(string filePath){
    if(!checkFileExist(filePath)){
        throw string("打印到控制台的文件不存在");
    }
    char buffer[1024] = {0}; //缓冲字符串

    /*
    fstream fin(filePath.c_str(), ios::in | ios::binary);
    while(!fin.eof()){
        //fin.get(buffer, 1023);
        //cout << buffer;
        cout << fstream.get();
    }
    fin.close();
    */ //这里文件操作有问题，暂时不用c++的

    FILE * file = fopen(filePath.c_str(), "r");
    while(NULL != fgets(buffer, 1023, file)){ //fgets读取失败或者到了文件末尾 返回false，否则返回buffer指针
        cout << buffer;
    }
    fclose(file);
}

string getCommand(){ //返回要执行的 "gcc" 或者是 “g++”
    //g++跟gcc最主要的区别在于链接阶段， g++会链接到c++库，但是gcc可能会有问题。 g++是将文件当做c++文件处理，即使是.c后缀结尾的。而gcc历史上一开始表示
    // gnu c compiler 后来随着发展，成了 gnu compilers collection 表示一系列的编译器。它会通过判断后缀选择使用的的编译器，如果是.c结尾就用c编译器，如果
    //是.cpp结尾就用c++编译器（g++）。但是在链接阶段没了这个判断，gcc就可能出现链接不到有些系统库。
    return isCpp ? "g++" : "gcc";
}

void createDestDir(string dir, string baseDir) throw(string){ //创建一个目录，如果这个目录存在就不创建. 其中baseDir是路径前面部分，且必须已经存在
    //利用 "/" "\" 或者 "\\"
    int index = dir.find(baseDir,0); // 从开始查找baseDir
    if(index == -1){
        throw string("待创建的目录不在项目根目录下面");
    }
    unsigned int start = baseDir.length();
    int a, b, c; //分别表示dir从start开始向下找到的第一个 "/" "\" 的位置, 以及最近找到的 “\” 或者 “/"
    while(start < dir.length()){
        a = dir.find("/", start);
        b = dir.find("\\", start);
        c = b == -1 || a < b ? a : b;
        if(-1 != c){
            string subStr = dir.substr(0,c + 1);
            if(!checkDirExist(subStr)){
                mkdir(subStr.c_str());
            }
            start = c + 1;
        } else { //如果没有找打 "/" 或者 ”\“ 就查看start是否是到了最后，如果没有，就判断整个dir是否应该判断
            if(!checkDirExist(dir)){
                mkdir(dir.c_str());
            }
            start = dir.length();
        }
    }
}

vector<string> & getIncludeDirs(string dir, vector<string> & v){
    //遍历dir，如果某一个目录下面存在 .h文件就将这个目录添加到gcc  -I 命令参数配置下面
    _finddata_t fd;
    bool found = false;
    long handle = _findfirst((dir + "*.*").c_str(), &fd);
    if(-1 == handle){
        return v;
    }
    do{
        if(strcmp(fd.name,".") == 0 || strcmp(fd.name,"..") == 0){
            continue;
        }
        if(fd.attrib & _A_SUBDIR){//子文件夹
            getIncludeDirs(dir + fd.name + "/", v);
        }
        if(found == true)
            continue;
        int index = string(fd.name).find_last_of(".");
        if(index != -1 && string(fd.name).substr(index+1) == "h"){//后缀是.h
            v.push_back(dir);
            found = true;
        }
    }while(0 == _findnext(handle, &fd));
    _findclose(handle);
    return v;
}

//预处理某一个目录下面的所有.c .cpp源文件
bool processCppInOneDirectory(string iParam, string dir){
    _finddata_t fd;
    long handle = _findfirst((dir + "*.*").c_str(), &fd);
    if(-1 == handle){
        return false;
    }
    HANDLE hRead, hWrite;
    string cmd = getCommand();
    if(!createMyPipe(hRead, hWrite)){ //管道创建失败
        return false;
    }

    bool toReturn = true;
    do{
        if(strcmp(fd.name,".") == 0 || strcmp(fd.name,"..") == 0){
            continue;
        }
        if(fd.attrib & _A_SUBDIR){//子文件夹
            if(!processCppInOneDirectory(iParam, dir + fd.name + "/")){
                toReturn = false;
                break;
            }
        }
        int index = string(fd.name).find_last_of(".");
        if(index != -1 && (string(fd.name).substr(index+1) == "c" || string(fd.name).substr(index+1) == "cpp")){//后缀是.h
            //处理一个源文件
            string name = string(fd.name).substr(0, index);
            bool res = execCmdWithMyPipe(hRead, hWrite, NULL, (cmd + iParam + " -E " + dir + fd.name + " -o " + iDir +name + ".i").c_str(),
                                  TRUE, SW_HIDE);

            //暂停一下  因为execCmdWithMyPipe 里面执行了gcc命令  一个gcc命令会创建文件 由于创建文件设计的磁盘操作与内存可能存在不同步  所以这里用一个Sleep(1)
            Sleep(1);
            if(!res){
                toReturn = false;
                break;
            }
        }
    }while(0 == _findnext(handle, &fd));
    _findclose(handle);
    CloseHandle(hWrite);

    //预处理的相关gcc输出结果保存到workDir/~preprocess.out文件
    if(translateContentFromPipe2File(hRead, workDir + "~preprocess.err",
                                     ios::out | ios::binary) && !checkFileEmpty(workDir + "~preprocess.err")){ //gcc执行的错误输出文件有内容，说明命令执行出错
        toReturn = false;
    }
    CloseHandle(hRead);
    return toReturn;
}

bool myPreprocess(){ //执行预编译，生成 .i 输出到iDir目录
    if(!checkFileTypeInDir(baseDir, "c") && !checkFileTypeInDir(baseDir, "cpp")){ //项目中没有任何源文件
        cout << translateUtf82GBK("项目中没有发现任何.c或者.cpp源文件") << endl;
        return false;
    }

    //得到包含.h文件
    vector<string> includes;
    getIncludeDirs(baseDir, includes);

    string iParam = "";
    for(vector<string>::iterator it = includes.begin(); it != includes.end(); ++it){
        iParam += " -I " + (*it);
    }
    bool res = processCppInOneDirectory(iParam, baseDir);
    if(!res){
        cout << translateUtf82GBK("预处理阶段出错，详细的参考信息如下：") << endl;
        string outFilePath = workDir + "~preprocess.err";
        if(checkFileExist(outFilePath) && !checkFileEmpty(outFilePath))
            printFileContent2Console(outFilePath);
        else
            cout << translateUtf82GBK("未知错误") << endl;
    } else {
        cout << translateUtf82GBK("预处理阶段，执行完成，并已生成所有相关文件(.i)") << endl;
    }
    return res;
}

bool myCompile() { //把一个目录中的.i 文件编译成 .s 并且输出到 sDir目录下面
    if(!checkFileTypeInDir(iDir, "i")){
        cout << translateUtf82GBK("编译模式下，iDir目录下，不存在任何 .i 类型文件。程序自动进入预处理模式，运行结束后，编译模式将自动继续运行...") << endl << endl;
        if(!myPreprocess()){
            return false;
        }
        cout << translateUtf82GBK("继续执行编译模式...") << endl;
    }
    _finddata_t fd;
    long handle = _findfirst((iDir + "*.i").c_str(), &fd);
    if(-1 == handle){
        return false;
    }
    string cmd = getCommand();
    HANDLE hRead, hWrite;
    if(!createMyPipe(hRead, hWrite)){ //管道创建失败
        return false;
    }

    bool toReturn = true;
    do{
        if((fd.attrib & _A_SUBDIR)) //忽略子文件夹
            continue;
        string filename = string(fd.name).substr(0, strlen(fd.name) - 2); //去掉后两个字符.i就是文件不带后缀的名称
        bool res = execCmdWithMyPipe(hRead, hWrite, NULL, (cmd + " -S " + iDir + fd.name + " -o " + sDir + filename + ".s").c_str(),
                            TRUE, SW_HIDE);
        //编译完一个文件之后  暂停一下
        Sleep(1);
        if(!res){
            toReturn = false;
            break;
        }
    }while(0 == _findnext(handle, &fd));
    _findclose(handle);
    CloseHandle(hWrite);

    if(!toReturn){
        string sOut = workDir + "~compile.err";
        cout << translateUtf82GBK("编译阶段执行错误，详细参考信息如下: ") << endl;
        if(translateContentFromPipe2File(hRead, sOut, ios::out | ios::binary)){
            printFileContent2Console(sOut);
        } else {
            cout << translateUtf82GBK("未知错误") << endl;
        }
    } else {
        cout << translateUtf82GBK("编译阶段，执行完成，所有的相关文件(.s)已经生成完毕...") << endl << endl;
    }
    CloseHandle(hRead);
    return toReturn;
}

bool myAssembly(){ //执行汇编，生成 .o 输出到obj目录
    if(!checkFileTypeInDir(sDir, "s")){
        cout << translateUtf82GBK("汇编模式下，sDir目录下，不存在任何 .s 类型文件。程序自动进入编译模式，运行结束后，汇编模式将自动继续运行...") << endl << endl;
        if(!myCompile()){
            return false;
        }
        cout << translateUtf82GBK("继续执行汇编模式...") << endl;
    }
    _finddata_t fd;
    long handle = _findfirst((sDir + "*.s").c_str(), &fd);
    if(-1 == handle){
        return false;
    }
    string cmd = getCommand();
    HANDLE hRead, hWrite;
    if(!createMyPipe(hRead, hWrite)){ //管道创建失败
        return false;
    }

    bool toReturn = true;
    do{
        if((fd.attrib & _A_SUBDIR)) //忽略子文件夹
            continue;
        string filename = string(fd.name).substr(0, strlen(fd.name) - 2); //去掉后两个字符.s就是文件不带后缀的名称
        bool res = execCmdWithMyPipe(hRead, hWrite, NULL, (cmd + " -c " + sDir + fd.name + " -o " + oDir + filename + ".o").c_str(),
                            TRUE, SW_HIDE);
        //汇编完一个文件之后暂停一下
        Sleep(1);
        if(!res){
            toReturn = false;
            break;
        }
    }while(0 == _findnext(handle, &fd));
    _findclose(handle);
    CloseHandle(hWrite);

    if(!toReturn){
        string sOut = workDir + "~assembly.err";
        cout << translateUtf82GBK("汇编阶段执行错误，详细参考信息如下: ") << endl;
        if(translateContentFromPipe2File(hRead, sOut, ios::out | ios::binary)){
            printFileContent2Console(sOut);
        } else {
            cout << translateUtf82GBK("未知错误") << endl;
        }
    } else {
        cout << translateUtf82GBK("汇编阶段，执行完成，所有的相关文件(.o)已经生成完毕...") << endl << endl;
    }
    CloseHandle(hRead);
    return toReturn;
}

bool myLink(){ //将obj目录下面的所有 .o 链接成 exe 输出到 bin目录下
    //如果已经存在exe，就删除它
    string exePath = binDir + exeName + ".exe";
    if(checkFileExist(exePath)){
        remove(exePath.c_str());
    }

    if(!checkDirExist(oDir))
        createDestDir(oDir, baseDir);
    _finddata_t fd;
    long handle = _findfirst((oDir + "*.o").c_str(), &fd);
    if(-1 == handle){ //因为通过上面的判断跟创建，这里没有获取到内容的原因一定是没有一个匹配项
        cout << translateUtf82GBK("链接模式下，oDir目录下，不存在任何 .o 类型文件，程序自动进入汇编模式。之后链接模式会继续运行...") << endl << endl;
        if(!myAssembly()){
            return false;
        }
        cout << translateUtf82GBK("汇编模式模式执行完毕。链接模式继续运行...") << endl << endl;

        //生成文件之后重开
        handle = _findfirst((oDir + "*.o").c_str(), &fd);
        if(-1 == handle){
            cout << translateUtf82GBK("汇编模式模式执行完毕，但oDir目录下依然不存在任何 .o 类型文件，程序将终止执行...") << endl << endl;
            return false;
        }
    }
    string param = "";
    string linkErrOutputFilePath = workDir + "~link.err";

    do{
        param += " " + oDir + fd.name;
    }while(0 == _findnext(handle, &fd));
    _findclose(handle);
    param += " -o " + exePath;

    //创建管道
    HANDLE hRead, hWrite;
    if(!createMyPipe(hRead, hWrite)){
        cout << translateUtf82GBK("创建管道失败") << endl;
        return false;
    }

    cout  << "link command : " << (getCommand() + param) << endl;
    //执行链接命令
    if(!execCmdWithMyPipe(hRead, hWrite, NULL, (getCommand() + param).c_str(), TRUE, SW_HIDE)){
        cout << translateUtf82GBK("链接出错, 完整的错误执行命令如下：") << getCommand() << param << endl << endl;
        return false;
    }
    CloseHandle(hWrite);

    //连接命令执行完成 暂停一下
    Sleep(1);

    //从管道中获取数据
	translateContentFromPipe2File(hRead, linkErrOutputFilePath, ios::out | ios::binary);
	CloseHandle(hRead);

    bool toReturn = true;
    if(!checkFileExist(exePath)){
        cout << translateUtf82GBK("链接阶段出错，相应的错误提示如下:") << endl << endl;
        if(!checkFileEmpty(linkErrOutputFilePath)){
            printFileContent2Console(linkErrOutputFilePath);
        } else {
            cout << translateUtf82GBK("未知错误") << endl;
        }
        toReturn = false;
    } else {
        cout << translateUtf82GBK("连接阶段，执行完毕，并已生成相应的exe文件...") << endl << endl;
    }

    return toReturn;
}

bool myRun(){
    string exeFullPath = binDir + exeName + ".exe";
    if(!checkFileExist(exeFullPath)){
        cout << translateUtf82GBK("运行模式下，没有找到相应的exe文件，程序将自动进入链接模式，之后运行模式会继续运行...") << endl << endl;
        if(!myLink()){
            return false;
        }
        cout << translateUtf82GBK("链接模式运行完毕，运行模式继续运行...") << endl;
    }
    cout << translateUtf82GBK("......执行 ") << exeFullPath << translateUtf82GBK(", 具体结果如下...") << endl << endl;
    string tempOutputFilePath = workDir + "~exe.out";
    //创建管道
    HANDLE hRead, hWrite;
    if(!createMyPipe(hRead, hWrite)){
        cout << translateUtf82GBK("创建管道失败") << endl;
        return false;
    }

    //执行程序
    if(!execCmdWithMyPipe(hRead, hWrite, exeFullPath.c_str(), NULL, TRUE, SW_HIDE)){
        cout << translateUtf82GBK("运行出错, 完整的错误执行命令如下：") << exeFullPath << endl;
        return false;
    }
    CloseHandle(hWrite);

    //从管道中获取程序执行结果输出到文件
    char buffer[1024 + 1] = {0};
    DWORD dwCount = 0;
    fstream f(tempOutputFilePath.c_str(), ios::out | ios::binary);
	if(NULL == f){
		cout << translateUtf82GBK("打开 ") << tempOutputFilePath << translateUtf82GBK(" 文件打开失败,请检查相应的文件是否被占用") <<  endl;
		return false;
	}
	while(0 != ReadFile(hRead, buffer, 1024, &dwCount,NULL)){
		f << buffer;
		if(1024 > dwCount) //已经读到文件的末尾
			break;
	}
	f.close();
	CloseHandle(hRead);
	//读取运行结果到控制台
    printFileContent2Console(tempOutputFilePath);
    return true;
}

bool validateMyProject() throw(std::string){ //判断当前目录是不是我本人自定义的project类型，这里判断依据是目录下面是否存在 .myIde文件
    struct _finddata_t fd;
    long handle = _findfirst((baseDir + "*.*").c_str(), &fd); //查找 *.*文件类型8
    string desCmp = ".myIde";  //待寻找的文件名. 跟下面的 fd.name 进行比较判断是否存在
    if(-1 == handle){
        throw string("项目根目录不存在，或者配置错误");
    }
    while(!_findnext(handle,&fd)){
        if(strcmp(fd.name, ".") == 0 || strcmp(fd.name, "..") == 0){ //特殊情况
            continue;
        }
        if(0 == (fd.attrib & _A_SUBDIR) && strcmp(fd.name, desCmp.c_str()) == 0)
            return true;
    }
    _findclose(handle);
    return false;
}

void printHelpInfo(){
    cout << translateUtf82GBK("您可输入的命令参考如下:") << endl;
    cout << translateUtf82GBK("\t...以下命令如果没有加入到系统path，需要cd到这个myIde.exe所有目录...") << endl;
    cout << "\tmyIde [-e/-s/-c/-o/-r [PROJECTDIR]]" << endl;
    cout << translateUtf82GBK("\t   -e\t预编译模式") << endl;
    cout << translateUtf82GBK("\t   -s\t编译模式") << endl;
    cout << translateUtf82GBK("\t   -c\t汇编模式") << endl;
    cout << translateUtf82GBK("\t   -o\t链接模式") << endl;
    cout << translateUtf82GBK("\t   -r\t运行模式") << endl;
    cout << translateUtf82GBK("\t   PROJECTDIR为项目根目录，如果没有传入，默认是当前命令执行环境") << endl;
    cout << translateUtf82GBK("\tmyIde -help\t输出帮助信息") << endl;
    cout << translateUtf82GBK("\tmyIde -var\t输出程序相关变量信息") << endl;
}

string getPropertyFromConfig(string name){
    string toReturn = "";
    fstream fileReader((baseDir+".myIde").c_str(), ios::in);
    if(!fileReader){
        cout << "配置文件读取失败，采用默认"  << name << endl;
    } else {
        string buffer;
        string leftHand;
        do{
            fileReader >> buffer;
            int findIndex = -1;
            if(-1 != (findIndex = buffer.find("=", 0))){
                leftHand = buffer.substr(0,findIndex + string("=").length());
            }
        }while(!fileReader.eof() && leftHand != (name + "="));
        if(leftHand == (name + "="))
            toReturn = buffer.substr(leftHand.length(), buffer.length() - leftHand.length());
        fileReader.close();
    }
    return toReturn;
}

//打印程序相关变量
void printEnv(){
    cout << "baseDir :\t" << baseDir << endl;
    cout << "debugDir :\t" << debugDir << endl;
    cout << "oDir :\t" << oDir << endl;
    cout << "binDir :\t" << binDir << endl;
    cout << "exeName :\t" << exeName << endl;
    cout << "isCpp : \t" << boolalpha << isCpp << noboolalpha << endl;
    cout << "workDir :\t" << workDir << endl;
}

string getDefaultExeNameFromBaseDir(){
    string temp = baseDir;
    while(temp.length() > 0 && (temp[temp.length() -1] == '/' || temp[temp.length() -1] == '\\')){
        temp.erase(temp.length() -1, 1);
    }
    int len1 = temp.find_last_of("/",0);
    int len2 =  temp.find_last_of("\\",0);
    int len = len1 == -1 || len1 < len2 ? len2 : len1;
    if(len != -1){
        return temp.substr(len + 1);
    } else {
        return exeName;
    }
}

int main(int argc, char ** args)
{
    enum _mode{PREPROCESS_MODE, COMPLIE_MODE, ASSEMBLY_MODE, LINK_MODE, RUN_MODE, HELP_MODE, VAR_MODE, UNKNOWN_MODE} mode; //各种运行模式
    const char * inputModeMatchs[] = {"-e", "-s", "-c", "-o", "-r", "-help", "-var"}; // 分别对应 预编译 编译  汇编  链接  运行 帮助 输出环境变量

    //处理运行模式
    bool flag = false;
    bool useDefaultBaseDir = true; //默认是使用获取到的当前目录, 如果调用exe的时候第二个参数有传入，就用第二个参数
    switch(argc){
        case 1:
            mode = RUN_MODE;
            break;
        case 2:
        case 3:
            flag = false;
            for(int i = 0; i < 7; ++i){
                if(stricmp(args[1], inputModeMatchs[i]) == 0){
                    mode = (enum _mode) i ;
                    flag = true;
                }
            }
            if(!flag)
                mode = UNKNOWN_MODE;
            if(argc == 2)
                break;
            baseDir = string(args[2]);
            if(baseDir.length() > 0 && baseDir[baseDir.length()-1] == '\\'){
                if(baseDir.length() > 1 && baseDir[baseDir.length() - 2] != '\\')  //如果结尾只有一个正斜杠，就追加一个正斜杠
                    baseDir += "\\";
            }else if(baseDir.length() > 0 && baseDir[baseDir.length()-1] != '/'){ //如果结尾没正斜杠，就追加一个反斜杠
                baseDir += "/";
            }
            useDefaultBaseDir = false;
            break;
        default:
            mode = UNKNOWN_MODE;
            break;
    }

    if(UNKNOWN_MODE == mode){
        cout << translateUtf82GBK("输入参数不符合规定.") << endl;
        printHelpInfo();
        return -1;
    } else if(HELP_MODE == mode){
        printHelpInfo();
        return 0;
    }

    if(useDefaultBaseDir){ //使用默认获取的项目根目录
        char szbaseDir[MAX_PATH] = {0};
        GetCurrentDirectory(MAX_PATH,szbaseDir); //得到当前目录
        baseDir.append(szbaseDir).append("/");
    }


    //项目合法性检查
    try{
        if(!validateMyProject()){
            cout << translateUtf82GBK("当前工程目录下没有找到.myIde配置文件，请检查项目是否配置正确") << endl;
            return -1;
        }
    } catch(string & e){
        cout << translateUtf82GBK(e) << endl;
        return -1;
    }

    //获取默认的exeName
    exeName = getDefaultExeNameFromBaseDir();

    //配置输出目录
    debugDir = baseDir + "Debug/";
    oDir = debugDir + "o/";
    binDir = debugDir + "bin/";
    workDir = baseDir + "work/";
    iDir = debugDir + "i/";
    sDir = debugDir + "s/";

    //创建输出目录
    createDestDir(debugDir, baseDir);
    createDestDir(workDir, baseDir);
    createDestDir(oDir, debugDir);
    createDestDir(binDir, debugDir);
    createDestDir(iDir, debugDir);
    createDestDir(sDir, debugDir);

    //读取.myIde里面的 exe 的name
    string exeNameGotFromConfig = getPropertyFromConfig("exeName");
    exeName = exeNameGotFromConfig != "" ? exeNameGotFromConfig : exeName;

    //读取.myIde里面的 isCpp
    string isCppGotFromConfig = getPropertyFromConfig("isCpp");
    isCpp = isCppGotFromConfig != "" ? true : isCpp;

    //按照mode选择相应的操作
    switch(mode){
        case PREPROCESS_MODE :
            myPreprocess();
            break;
        case COMPLIE_MODE :
            myCompile();
            break;
        case ASSEMBLY_MODE :
            myAssembly();
            break;
        case LINK_MODE :
            try{
                myLink();
            }catch(string & e){
                cout << translateUtf82GBK("链接阶段出错，具体错误如下：\n" + e) << endl;
                break;
            }
            break;
        case RUN_MODE :
            myRun();
            break;
        case VAR_MODE :
            printEnv();
            break;
        default:
            printHelpInfo();
            break;
    }
    return 0;
}
