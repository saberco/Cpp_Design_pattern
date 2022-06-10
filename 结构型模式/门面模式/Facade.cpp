//实例为实现电脑开机动作，我只需要按下那个开机键，其他的都会执行
#include <iostream>


using namespace std;


//整个系统的开机操作
//内存
class Memory{
public:
    void selfcheck(){
        cout<<"内存自检中..."<<endl;
        cout<<"内存自检成功"<<endl;
    }
};
//cpu
class Processor{
public:  
    void run(){
        cout<<"cpu启动中..."<<endl;
        cout<<"cpu启动成功"<<endl;
    }
};
//硬盘
class HardDisk{
public:  
    void read(){
        cout<<"读取硬盘中..."<<endl;
        cout<<"硬盘读取成功"<<endl;
    }
};


//操作系统
class OS{
public:  
    void load(){
        cout<<"载入操作系统..."<<endl;
        cout<<"操作系统载入成功"<<endl;
    }
};

//可以看出每个子系统都提供了不同的接口，需要将其封装为一个完整的简单的接口
class ComputerOperator{
public:
    ComputerOperator(){
        m_memory = new Memory();
        m_processor = new Processor();
        m_harddisk = new HardDisk();
        m_os = new OS();
    }
    ~ComputerOperator(){
        delete m_memory;
        delete m_processor;
        delete m_harddisk;
        delete m_os;
        m_memory = nullptr;
        m_processor = nullptr;
        m_harddisk = nullptr;
        m_os = nullptr;
    }
    //一个对外的接口
    void powerOn(){
        cout<<"正在开机..."<<endl;
        m_memory->selfcheck();
        m_processor->run();
        m_harddisk->read();
        m_os->load();
        cout<<"开机成功"<<endl;
    }

private:
    Memory* m_memory;
    Processor* m_processor;
    HardDisk* m_harddisk;
    OS* m_os;
};



int main(){
    ComputerOperator* cmp = new ComputerOperator();
    cmp->powerOn();
    delete cmp;
    return 0;
}