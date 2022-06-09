//桥模式实例用两种笔进行两种颜色的绘制
#include <string>
#include<iostream>

using namespace std;


//其中笔类包含颜色类，以组合的形式取代继承
//先实现颜色类
class Color {
public:
    virtual void bepaint(string pen_type, string name) = 0;
};

//两种颜色
//red
class Red : public Color{
public:
    virtual void bepaint(string pen_type, string name) override{
        cout<<pen_type << "红色的" << name << endl;
    }
};

//绿色
class Green : public Color{
public:
    virtual void bepaint(string pen_type, string name) override{
        cout<<pen_type << "绿色的" << name << endl;
    }
};


//笔的抽象接口类
class Pen {
public:
    Pen():m_color(nullptr){}
    virtual void draw(string name)=0;
    void set_color(Color* color){
        m_color = color;
    }

protected:
    Color* m_color;
};

//精确的抽象类
//小号铅笔
class SmallPen : public Pen{
public:
    virtual void draw(string name) override{
        string pen_type = "小号铅笔绘制";
        m_color->bepaint(pen_type, name);
    }
};



//大号钢笔
class BigPen : public Pen{
public:
    virtual void draw(string name) override{
        string pen_type = "大号钢笔绘制";
        m_color->bepaint(pen_type, name);
    }
};

int main(){

    //客户端自行选择采用什么颜色和笔绘制
    Color* color = new Green();
    Pen* pen = new SmallPen();

    pen->set_color(color);
    pen->draw("鲨鱼");

    delete color;
    delete pen;
    return 0;
}