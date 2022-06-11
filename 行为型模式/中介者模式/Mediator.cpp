//实例为：房东-》房产中介《-租客

#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

enum class PERSON_TYPE{
    Unknown,
    Landlord,
    Tenant
};

class Colleague;
//抽象的中介者
class Mediator{
public:
    //声明抽象的接口
    virtual void registerMethod(Colleague*) = 0;
    virtual void operation(Colleague*) = 0;
};

//房东和租客类的抽象基类
class Colleague{
public:
    void set_mediator(Mediator* m){
        m_mediator = m;
    }

    Mediator* get_mediator(){
        return m_mediator;
    }

    void set_person_type(PERSON_TYPE pt){
        m_person_type = pt;
    }

    PERSON_TYPE get_person_type(){
        return m_person_type;
    }

    virtual void ask() = 0;
    virtual void answer() = 0;
private:
    Mediator* m_mediator;
    PERSON_TYPE m_person_type;
};

//具体的房东类
class Landlord : public Colleague{
public:
    Landlord(){
        m_name = "unknown";
        m_price = -1;
        m_address = "unknown";
        m_phone_number = "unknown";
        set_person_type(PERSON_TYPE::Unknown);
    }

    Landlord(string name, int price, string address, string phone){
        m_name = name;
        m_price = price;
        m_address = address;
        m_phone_number = phone;
        set_person_type(PERSON_TYPE::Landlord);
    }
    virtual void answer() override{
        printf("房东姓名:%s 房租:%d 地址:%s 电话:%s\n",m_name.c_str(),m_price, m_address.c_str() ,m_phone_number.c_str());
    }

    virtual void ask()override{
        printf("房东%s查看租客信息: \n", m_name.c_str());
        this->get_mediator()->operation(this);
    }

private:
    string m_name;
    int m_price;
    string m_address;
    string m_phone_number;
};

//具体的租客类
class Tenant : public Colleague{
public:
    Tenant(){
        m_name = "unknown";
    }
    explicit Tenant(string name){
        m_name = name;
        set_person_type(PERSON_TYPE::Tenant);
    }

    virtual void answer() override{
        printf("租客姓名: %s\n", m_name.c_str());
    }
    virtual void ask()override{
        printf("租客%s询问房东信息:\n", m_name.c_str());
        this->get_mediator()->operation(this);
    }
private:
    string m_name;
};

//具体的中介者
class Agency : public Mediator{
public:
    virtual void registerMethod(Colleague* person)override{
        switch (person->get_person_type())
        {
        case PERSON_TYPE::Tenant:{
            m_tenant_lst.push_back(person);
            break;
        }
            
        case PERSON_TYPE::Landlord:{
            m_landlord_lst.push_back(person);
            break;
        }
        default:
            printf("wrong person\n");
            break;
        }
    }

    virtual void operation(Colleague* person)override{
        switch (person->get_person_type())
        {
        case PERSON_TYPE::Tenant:{
            for(int i = 0;i<m_landlord_lst.size();++i){
                m_landlord_lst[i]->answer();
            }
            break;
        }
            
        case PERSON_TYPE::Landlord:{
            for(int i = 0;i<m_tenant_lst.size();++i){
                m_tenant_lst[i]->answer();
            }
            break;
        }
        default:
            break;
        }
    }
private:
    //租客和房东列表
    vector<Colleague*> m_landlord_lst;
    vector<Colleague*> m_tenant_lst;
};


int main(){
    //中介
    Agency* pAgency = new Agency();

    //三位房东
    Landlord* l1 = new Landlord("张三", 2000, "天津", "123123");
    Landlord* l2 = new Landlord("李四", 6666, "四川", "234524");
    Landlord* l3 = new Landlord("王五", 8888, "北京", "23423");
    //注册方法
    l1->set_mediator(pAgency);
    l2->set_mediator(pAgency);
    l3->set_mediator(pAgency);
    pAgency->registerMethod(l1);
    pAgency->registerMethod(l2);
    pAgency->registerMethod(l3);

    //三位租客
    Tenant* t1 = new Tenant("Alex");
    Tenant* t2 = new Tenant("Bill");
    Tenant* t3 = new Tenant("Cindy");
    t1->set_mediator(pAgency);
    t2->set_mediator(pAgency);
    t3->set_mediator(pAgency);
    pAgency->registerMethod(t1);
    pAgency->registerMethod(t2);
    pAgency->registerMethod(t3);

    //业务逻辑
    //租客1问房东列表
    t1->ask();
    cout<<endl;
    //房东2问租客列表
    l2->ask();

    delete pAgency;
    delete l1;
    delete l2;
    delete l3;
    delete t1;
    delete t2;
    delete t3;
    return 0;
}