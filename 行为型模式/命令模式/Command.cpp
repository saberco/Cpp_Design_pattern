//实例为遥控器遥控电视命令
#include <memory>
#include <iostream>
#include <string>

using namespace std;



//命令的抽象接口，仅包含一个无参的执行函数
class Command{
public:
    virtual void execute() = 0;
};

//命令者,即遥控器
class Controller{
public:
    Controller():m_pcmd(nullptr){}
    //设置命令
    void setCommand(shared_ptr<Command> pcmd){
        m_pcmd = pcmd;
    }

    void executeCommand(){
        m_pcmd->execute();
    }

private:
    shared_ptr<Command> m_pcmd;
};

//接收者
class Tv{
public:
    void open(){
        cout<<"打开电视"<<endl;
    }

    void close(){
        cout<<"关闭电视"<<endl;
    }

    void changeChannel(){
        cout<<"切换频道"<<endl;
    }
};



//具体的一列命令
//打开电视命令
class TVOpenCommand : public Command{
public:
    explicit TVOpenCommand(shared_ptr<Tv> pTv) : m_pTv(pTv){}
    virtual void execute() override{
        m_pTv->open();
    }
private:
    shared_ptr<Tv> m_pTv;
};

//关闭电视命令
class TVCloseCommand : public Command{
public:
    explicit TVCloseCommand(shared_ptr<Tv> pTv) : m_pTv(pTv){}
    virtual void execute() override{
        m_pTv->close();
    }
private:
    shared_ptr<Tv> m_pTv;
};

//切换频道命令
class TVChangeCommand : public Command{
public:
    explicit  TVChangeCommand (shared_ptr<Tv> pTv) : m_pTv(pTv){}
    virtual void execute() override{
        m_pTv->changeChannel();
    }
private:
    shared_ptr<Tv> m_pTv;
};


int main(){
    shared_ptr<Tv> pTv = make_shared<Tv>();

    //命令
    shared_ptr<Command> pOp = make_shared<TVOpenCommand>(pTv);
    shared_ptr<Command> pCl = make_shared<TVCloseCommand>(pTv);
    shared_ptr<Command> pCh = make_shared<TVChangeCommand>(pTv);

    //遥控器
    shared_ptr<Controller> pController = make_shared<Controller>();

    //测试
    pController->setCommand(pOp);
    pController->executeCommand();
    pController->setCommand(pCl);
    pController->executeCommand();
    pController->setCommand(pCh);
    pController->executeCommand();


    return 0;
}

