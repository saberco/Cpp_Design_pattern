//实例为员工申请处理票据，需要上报给上级，如果上级无权处理就再上报

#include <iostream>
#include <string>

using namespace std;
//抽象的处理者接口
class ApproveInterface{
public:
    virtual void setSuperior(ApproveInterface* sup) = 0;
    virtual void handleRequest(double amount) = 0;
};

//基础处理者，封装了一切处理者的操作
class BaseSup : public ApproveInterface{
public:
    BaseSup(double maxamount, string name)
        :m_maxAmount(maxamount), m_name(name), m_sup(nullptr){}
    
    virtual void setSuperior(ApproveInterface* sup) override{
        m_sup = sup;
    }
    //处理票据
    virtual void handleRequest(double amount)override{
        if(amount <= m_maxAmount ){
            printf("%s处理了该票据, 票据面额:%f\n", m_name.c_str(), amount);
            return;
        }
        //无法处理交付给下一个处理者
        if(m_sup != nullptr){
            printf("%s无权处理, 转交上级...\n", m_name.c_str());
            m_sup->handleRequest(amount);
            return;
        }

        //最上级依旧无法处理
        printf("无人有权限处理该票据, 票据金额:%f\n", amount);
    }
private:
    double m_maxAmount;
    string m_name;
    ApproveInterface* m_sup;    //指向下一个处理者
};

//设置具体的处理者
class GroupLeader : public BaseSup{
    //委托构造
public:
    explicit GroupLeader(string name) : BaseSup(10, name) {}
};

class Manager : public BaseSup{
    //委托构造
public:
    explicit Manager(string name) : BaseSup(100, name) {}
};

class  Boss : public BaseSup{
    //委托构造
public:
    explicit  Boss(string name) : BaseSup(1000, name) {}
};


int main(){
    GroupLeader* pGroupLeader = new GroupLeader("张组长");
    Manager* pManager = new Manager("王经理");
    Boss* pBoss = new Boss("李老板");

    //进行上下级设置
    pGroupLeader->setSuperior(pManager);
    pManager->setSuperior(pBoss);

    //不同面额统一交付给组长先审批
    pGroupLeader->handleRequest(8);
    pGroupLeader->handleRequest(88);
    pGroupLeader->handleRequest(888);
    pGroupLeader->handleRequest(8888);

    delete pGroupLeader;
    delete pManager;
    delete pBoss;
    return 0;
}



