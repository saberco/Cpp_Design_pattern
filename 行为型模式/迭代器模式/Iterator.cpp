


#include <vector>
#include <iostream>
#include <string>
#include <memory>

using namespace std;


//抽象的迭代器接口
class TVIterator{
public:
    virtual void setChannel(int i) = 0;
    virtual void next() = 0;
    virtual void pre() = 0;
    virtual bool isLast() = 0;
    virtual bool isFirst() = 0;
    virtual string currentChannel() = 0;
};

//具体的迭代器
class myIterator : public TVIterator{
public:
    explicit myIterator (vector<string>& tvs):m_tvs(tvs) {}
    virtual void setChannel(int i) override{
        m_cur = i;
    }
    virtual void next()override{
        if(m_cur < m_tvs.size())
            m_cur++;
    }
    virtual void pre()override{
        if(m_cur > 0)
            m_cur--;
    }
    virtual bool isLast()override{
        return m_cur == m_tvs.size();
    }
    virtual bool isFirst()override{
        return m_cur == 0;
    }
    virtual string currentChannel()override{
        return m_tvs[m_cur];
    }

private:
    vector<string>& m_tvs;
    int m_cur;
};


//抽象集合
class Tv{
public:
    virtual shared_ptr<TVIterator> createIterator() = 0;
};

//电视实体类
class myTv:public Tv{
public:
    virtual shared_ptr<TVIterator> createIterator() override{
        return make_shared<myIterator>(m_tvs);
    }

    void addItem(string Item){
        m_tvs.push_back(Item);
    }

private:
    vector<string> m_tvs;
};

int main(){
    myTv tv;
    tv.addItem("CCTV-1");
    tv.addItem("CCTV-2");
    tv.addItem("CCTV-3");
    tv.addItem("CCTV-4");
    tv.addItem("CCTV-5");

    auto iter = tv.createIterator();
    while(!iter->isLast()){
        cout<<iter->currentChannel()<<endl;
        iter->next();
    }

    return 0;
}

