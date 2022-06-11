


#include <string>
#include <iostream>
#include <list>

using namespace std;



class Product;
class Apple;
class Book;
//抽象的访问者接口
class Vistor{
public:
    void set_name(string name){
        m_name = name;
    }
    //重载的多个接口，用来访问不同的类
    virtual void visit(Apple*) = 0;
    virtual void visit(Book*) = 0;
protected:
    string m_name;
};

//抽象的产品类
class Product{
public:
    virtual void accept(Vistor* vistor) = 0;
};

//具体的产品类
class Apple : public Product{
public:
    virtual void accept(Vistor* vistor)override{
        vistor->visit(this);
    }
};

class Book : public Product{
public:
    virtual void accept(Vistor* vistor)override{
        vistor->visit(this);
    }
};





//具体的访问者类
//顾客访问者类
class Customer:public Vistor{
public:
    virtual void visit(Apple*)override{
        cout<<"顾客"<<m_name<<"挑选苹果"<<endl;
    }
    virtual void visit(Book*)override{
        cout<<"顾客"<<m_name<<"买书"<<endl;
    }
};

//收银员访问者
class Saler : public Vistor{
public:
    virtual void visit(Apple*)override{
        cout<<"收银员"<<m_name<<"给苹果称量，然后计算价格"<<endl;
    }
    virtual void visit(Book*)override{
        cout<<"收银员"<<m_name<<"计算书的价格"<<endl;
    }
};


//客户端，通过访问者访问产品类
class ShoppingCart{
public:
    void accept(Vistor* vistor){
        for(auto prd : m_list){
            prd->accept(vistor);
        }
    }

    void addPro(Product* pro){
        m_list.push_back(pro);
    }

    void remPro(Product* pro){
        m_list.remove(pro);
    }

private:
    list<Product*> m_list;
};


//主
int main(){
    Book book;
    Apple apple;
    ShoppingCart bucket;

    bucket.addPro(&book);
    bucket.addPro(&apple);

    Customer customer;
    customer.set_name("小张");
    bucket.accept(&customer);

    Saler saler;
    saler.set_name("小李");
    bucket.accept(&saler);


    return 0;
}