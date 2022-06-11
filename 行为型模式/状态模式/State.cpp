//实例为模仿论坛账号积分形式

#include <string>
#include <memory>
#include <iostream>
#include <cstdio>

using namespace std;


//声明状态类
class AbstractState;
class PrimaryState;
class MiddleState;
class HighState;

//上下文（原始对象），委派任务
class Account{
public:
    //创建新手的账号
    explicit Account(string name):m_name(name), m_state(make_shared<PrimaryState>(this)){
        printf("账号%s注册成功!\n", name.c_str());
    }
    void set_state(shared_ptr<AbstractState> state){
        m_state = state;
    }
    shared_ptr<AbstractState> get_state(){
        return m_state;
    }

    string get_name(){
        return m_name;
    }

    void downloadFile(int score){
        m_state->downloadFile(score);
    }

    void writeNote(int score){
        m_state->writeNote(score);
    }

    void replyNote(int score){
        m_state->replyNote(score);
    }

private:
    string m_name;
    //指向状态对象的指针
    shared_ptr<AbstractState> m_state;
};

class AbstractState{
public:
    virtual void checkState() = 0;

    void set_point(int point){
        m_point = point;
    }

    int get_point(){
        return m_point;
    }

    void set_state_name(string name){
        m_state_name = name;
    }

    string get_state_name(){
        return m_state_name;
    }

    Account* get_account(){
        return m_account;
    }

    virtual void downloadFile(int score){
        printf("%s下载文件, 扣除%d积分。\n", m_account->get_name().c_str(), score);
        m_point -= score;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", m_account->get_name().c_str(), m_point, m_account->get_state()->get_state_name().c_str());
    }

    virtual void writeNote(int score){
        printf("%s发布留言, 增加%d积分。\n", m_account->get_name().c_str(), score);
        m_point += score;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", m_account->get_name().c_str(), m_point, m_account->get_state()->get_state_name().c_str());
    }

    virtual void replyNote(int score){
        printf("%s回复留言, 增加%d积分。\n", m_account->get_name().c_str(), score);
        m_point += score;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", m_account->get_name().c_str(), m_point, m_account->get_state()->get_state_name().c_str());
    }
protected:
    Account* m_account;
    int m_point;
    string m_state_name;
};

//具体的状态
//新手
class PrimaryState : public AbstractState{
public:
    explicit PrimaryState(AbstractState* state){
        m_account = state->get_account();
        m_point = state->get_point();
        m_state_name = "新手";
    }
    explicit PrimaryState(Account* account){
        m_account = account;
        m_point = 0;
        m_state_name = "新手";
    }

    virtual void downloadFile(int score) override{
        printf("对不起, %s没有下载文件的权限!\n", m_account->get_name().c_str());
    }
    //这就是转移状态的函数  
    virtual void checkState() override{
        if(m_point >= 1000){
            m_account->set_state(make_shared<HighState>(this));
        }else if(m_point>=100){
            m_account->set_state(make_shared<MiddleState>(this));
        }
    }

};

//高手
class MiddleState : public AbstractState{
public:
    explicit MiddleState(AbstractState* state){
        m_account = state->get_account();
        m_point = state->get_point();
        m_state_name = "高手";
    }

    virtual void writeNote(int score)override{
        printf("%s发布留言, 增加%d积分。\n", m_account->get_name().c_str(), score);
        m_point += score*2;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", m_account->get_name().c_str(), m_point, m_account->get_state()->get_state_name().c_str());
    }
    //这就是转移状态的函数  
    virtual void checkState() override{
        if(m_point >= 1000){
            m_account->set_state(make_shared<HighState>(this));
        }else if(m_point<100){
            m_account->set_state(make_shared<PrimaryState>(this));
        }
    }
};

//专家
class HighState : public AbstractState{
public:
    explicit HighState(AbstractState* state){
        m_account = state->get_account();
        m_point = state->get_point();
        m_state_name = "专家";
    }

    virtual void writeNote(int score)override{
        printf("%s发布留言, 增加%d积分。\n", m_account->get_name().c_str(), score*2);
        m_point += score*2;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", m_account->get_name().c_str(), m_point, m_account->get_state()->get_state_name().c_str());
    }
    virtual void downloadFile(int score)override{
        printf("%s下载文件, 扣除%d积分。\n", m_account->get_name().c_str(), score/2);
        m_point -= score/2;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", m_account->get_name().c_str(), m_point, m_account->get_state()->get_state_name().c_str());
    }
    //这就是转移状态的函数  
    virtual void checkState() override{
        if(m_point < 100){
            m_account->set_state(make_shared<PrimaryState>(this));
        }else if(m_point<1000){
            m_account->set_state(make_shared<MiddleState>(this));
        }
    }
};

int main(){
    //新建一个账号
    Account account("Coco");
    account.writeNote(20);
    account.downloadFile(20);
    account.replyNote(100);
    account.writeNote(40);
    account.downloadFile(80);
    account.writeNote(1000);
    account.downloadFile(80);



    return 0;
}