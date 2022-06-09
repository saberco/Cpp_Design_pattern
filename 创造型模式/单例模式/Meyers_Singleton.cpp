
//返回局部静态变量的形式，线程安全
#include <iostream>

using namespace std;


class Singleton {
 public:
    static Singleton& GetInstance() {
        static Singleton instance;
        return instance;
    }
    //不允许拷贝构造
    // Singleton(const Singleton&) = delete;
    // Singleton& operator=(const Singleton&) = delete;

 private:
    Singleton() {}
};


int main(){
    Singleton s1 = Singleton::GetInstance();
    Singleton s2 = Singleton::GetInstance();

    return 0;
}