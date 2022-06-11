//实例是银行业务的办理流程

#include <iostream>

using namespace std;



//抽象方法类
//实现的是一个算法框架

class BankMethod{
public:
    void takeNumber() {
        std::cout << "排队取号。" << std::endl;
    }
    //允许子类重写的部分
    virtual void transact() = 0;

    void evalute() {
        std::cout << "反馈评分。" << std::endl;
    }
    //算法框架
    void process() {
        takeNumber();
        transact();
        evalute();
    }
};

//取款流程
class Deposit : public BankMethod{
public: 
    virtual void transact()override{
        cout << "存款..." <<endl;
    }
};

//存款流程
class Withdraw : public BankMethod{
public: 
    virtual void transact()override{
        cout << "取款..." <<endl;
    }
};

//转账流程
class Transfer : public BankMethod{
public: 
    virtual void transact()override{
        cout << "转账..." <<endl;
    }
};

int main(){
    //存款
    BankMethod* deposit = new Deposit();
    deposit->process();
    delete deposit;

    //取款
    BankMethod* withdraw = new Withdraw();
    withdraw ->process();
    delete withdraw ;

    //转账
    BankMethod* transfer = new Transfer();
    transfer->process();
    delete transfer;


    return 0;
}