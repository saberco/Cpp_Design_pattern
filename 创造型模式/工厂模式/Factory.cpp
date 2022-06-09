#include <memory>
#include <string>
#include <iostream>

using namespace std;

//抽象的产品类，
class Movie{
public:
    virtual string get_a_movie() = 0;
};

//具体的产品类

class ChineseMovie : public Movie{
public:
    virtual string get_a_movie() override{
        return "《让子弹飞》";
    }
};
class JapaneseMovie : public Movie{
public:
    virtual string get_a_movie() override{
        return "《千与千寻》";
    }
};
class AmericanMovie : public Movie{
public:
    virtual string get_a_movie() override{
        return "《复仇者联盟》";
    }
};




//抽象的工厂类，定义的接口，具体实现由子类实现
class Factory{
public:
    virtual shared_ptr<Movie> get_movie() = 0;
};

//具体的工厂类，依赖于抽象工厂
class ChineseProducer : public Factory{
public:
    virtual shared_ptr<Movie> get_movie() override {
        return make_shared<ChineseMovie>();
    }
};

class JapaneseProducer : public Factory{
public:
    virtual shared_ptr<Movie> get_movie() override {
        return make_shared<JapaneseMovie>();
    }
};
class AmericanProducer : public Factory{
public:
    virtual shared_ptr<Movie> get_movie() override {
        return make_shared<AmericanMovie>();
    }
};


int main(){
    //工厂指针
    shared_ptr<Factory> pFactory;
    shared_ptr<Movie>   pMovie;
    string conf = "Japan";

    // 程序根据当前配置或环境选择创建者的类型
    if (conf == "China") {
        pFactory = make_shared<ChineseProducer>();
    } else if (conf == "Japan") {
        pFactory = make_shared<JapaneseProducer>();
    } else if (conf == "America") {
        pFactory = make_shared<AmericanProducer>();
    } else {
        cout << "error conf" << endl;
    }
    
    pMovie = pFactory->get_movie();
    cout << "获取一部电影: " << pMovie->get_a_movie() << endl;

    return 0;
}