//发布者为猫，订阅者为狗，猫叫为信息，狗接收到追猫，老鼠接收到逃跑

#include <vector>
#include <iostream>

using namespace std;

//订阅者的统一接口
class AbstractObserver{
public:
    virtual void response() = 0;
};

//具体的观察者
//老鼠
class Mouse:public AbstractObserver{
public:
    virtual void response() override{
        cout<<"老鼠逃跑"<<endl;
    } 
};

//狗
class Dog:public AbstractObserver{
public:
    virtual void response() override{
        cout<<"狗追猫"<<endl;
    } 
};


//发布者猫
class Cat{
public:
    //注册观察者
    void add(AbstractObserver* ob){
        m_observers.push_back(ob);
    }
    //注销观察者
    void remv(AbstractObserver* ob){
        for(auto it = m_observers.begin(); it != m_observers.end();++it){
            if(*it == ob){
                m_observers.erase(it);
                break;
            }
        }
    }
    //消息叫
    void cry(){
        cout<<"猫叫"<<endl;
        for(auto ob:m_observers){
            ob->response();
        }
    }

private:
    vector<AbstractObserver*> m_observers;
};

int main(){
    Cat cat;
    Dog dog;
    Mouse mouse;

    //添加订阅关系
    cat.add(&dog);
    cat.add(&mouse);

    //发布消息
    cat.cry();

    return 0;
}