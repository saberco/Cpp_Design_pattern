//线程安全的懒汉,采用双检查锁的形式
#include <string>
#include <iostream>
#include <mutex>

using namespace std;

class Singleten{
public:
    static Singleten* GetInstance(){
        if(m_instance == nullptr){
            m_mutex.lock();
            if(m_instance == nullptr){
                m_instance = new Singleten();
            }
            m_mutex.unlock();
        }
        return m_instance;
    }
private:
    Singleten(){}
    static Singleten* m_instance;
    static mutex m_mutex;

};

Singleten* Singleten::m_instance = nullptr;
mutex Singleten::m_mutex;

int main(){
    Singleten* s1 = Singleten::GetInstance();
    Singleten* s2 = Singleten::GetInstance();

    cout<<"s1地址: "<<s1<<endl;
    cout<<"s2地址: "<<s2<<endl;
    return 0;
}