
#include <iostream>
#include <string>
//原型接口类，原型实现类，客户端

using namespace std;


//抽象原型接口类
class Object{
public:
    virtual Object* clone() = 0;
};


//邮件的附件类型
class Attachment{
public:
    void set_content(string content){
        m_content = content;
    }
    string get_content(){
        return m_content;
    }

private:
    string m_content;
};

//邮件类型的原型
class Email : public Object{
public:
    Email(){}
    Email(string text, string attachment_content) 
        :m_text(text), m_attachment(new Attachment()){
            m_attachment->set_content(attachment_content);
        }
    ~Email(){
        if(m_attachment != nullptr){
            delete m_attachment;
            m_attachment = nullptr;
        }
    }

    void display(){
        cout<<"---------------查看邮件----------"<<endl;
        cout<<"正文："<<m_text<<endl;
        cout<<"附件："<<m_attachment->get_content()<<endl;
        cout<<"---------------查看完毕----------"<<endl;
    }

    Email* clone() override{
        return new Email(this->m_text, this->m_attachment->get_content());
    }


private:
    string m_text;
    Attachment* m_attachment = nullptr;  
};

int main(){
    Email* pEmail = new Email("正文", "附件");
    Email* pCloneEmail = pEmail->clone();
    pCloneEmail->display();

    return 0;
}