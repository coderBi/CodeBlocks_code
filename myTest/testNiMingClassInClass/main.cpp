#include <iostream>

using namespace std;

class parent
{
    public:
        virtual void show()=0;


};

class outer: public parent  //����ʵ�� leimingouter����ʡ
{
    private:
        class inner:parent       //�ڲ����е� ����inner����ʡ��  ����γ��������ڲ���....  ���ǵ���������麯����  �����inner��������ʡ
                            //����ʵ�� �����java��ͬ  C++�е�����inner����Ҫһ���Ǽ̳л�ʵ��һ����  Ҳ���ǲ���Ҫ�̳�parent�ſ���ʡȥinner��
        {
            public:
                void show()
                {

                }

        };

        void show()
        {

        }

};

//C++����Ȼû�� interface��һ�ؼ���  ����ͨ�����麯��  ����һ��ʵ�ֽӿ�  ��ȻҲ����ͨ�����������һ��interface

int main()
{
    /*  ����û�а취��java���������������
    new parent()
    {
        void show()
        {

        }
    };
    */
    cout << "Hello world!" << endl;
    return 0;
}


