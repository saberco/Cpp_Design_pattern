#include <iostream>


using namespace std;



//将构造重载为私有，不能外部调用
class Singleten{
public:
    static Singleten* GetInstance(){
        return m_instance;
    }
private:
    Singleten(){};
    static Singleten* m_instance;
};


Singleten* Singleten::m_instance = new Singleten();
int main(){
    Singleten* s1 = Singleten::GetInstance();
    Singleten* s2 = Singleten::GetInstance();

    cout<<"s1地址: "<<s1<<endl;
    cout<<"s2地址: "<<s2<<endl;

    return 0;
}
