//实例是实现图像编辑器中绘制一系列几何图形
#include <iostream>
#include <map>

using namespace std;
//几何图形的通用接口，客户端进行调用
class Graphic{
public:
    virtual void move2somewhere(int x,int y) = 0;
    virtual void draw() = 0;
};

//组合树的叶子节点
class Dot : public Graphic{
public:
    Dot(int x,int y) : m_x(x), m_y(y){}
    virtual void move2somewhere(int x,int y) override{
        m_x+=x;
        m_y+=y;
        return;
    }

    virtual void draw()override{
        cout<< "在("<<m_x <<","<<m_y<<")处绘制一个点"<<endl;
        return;
    }

private:
    int m_x;
    int m_y;
};


//圆
class Round : public Graphic{
public:
    Round(int r,int x,int y) : m_radius(r), m_x(x), m_y(y){}
    virtual void move2somewhere(int x,int y) override{
        m_x+=x;
        m_y+=y;
        return;
    }

    virtual void draw()override{
        cout<< "在("<<m_x<<","<<m_y<<")处绘制一个半径为"<<m_radius<<"的圆"<<endl;
        return;
    }

private:
    int m_radius;
    int m_x;
    int m_y;
};


//组合类
class CompoundGraphic : public Graphic {
public:
    void add(int id, Graphic* child){
        m_children[id] = child;
    }
    void remove(int id){
        m_children.erase(id);
    }
    virtual void move2somewhere(int x,int y) override{
        for(auto it = m_children.begin(); it != m_children.end(); ++it){
            it->second->move2somewhere(x,y);
        }
    }
    virtual void draw()override{
        for(auto it = m_children.begin(); it != m_children.end(); ++it){
            it->second->draw();
        }
    }

private:
    map<int, Graphic*> m_children;
};


int main(){
    CompoundGraphic* all = new CompoundGraphic();

    //添加子图
    Dot* dot1 = new Dot(1,2);
    Round* round = new Round(5,2,2);
    

    //子组合图
    CompoundGraphic* child_graph = new CompoundGraphic();
    Dot* dot2 = new Dot(3,4);
    Dot* dot3 = new Dot(5,6);
    child_graph->add(0, dot2);
    child_graph->add(1, dot3);

    //组合三个子图
    all->add(0, dot1);
    all->add(1, round );
    all->add(2, child_graph);

    //绘制
    all->draw();

    delete all;
    delete dot1;
    delete dot2;
    delete dot3;
    delete round;

    return 0;
}