
//实例是让方钉适配圆孔
#include <cmath>
#include <iostream>

using namespace std;
//服务端-方钉
class SquarePeg{
public:
    explicit SquarePeg(int w) : m_width(w){}
    int get_width() const {
        return m_width;
    }
private:
    int m_width;
};

//客户端接口-圆钉
class RoundPeg{
public:
    RoundPeg(){}
    virtual int get_radius() = 0;
};

//客户端-圆孔
class RoundHole{
public:
//禁止隐式转换，仅能显示调用
    explicit RoundHole(int r) : m_radius(r){}
    int get_radius() const {
        return m_radius;
    }
    bool isFit(RoundPeg* rp){
        return m_radius >= rp->get_radius();
    }

private:
    int m_radius;
};




//适配器，将方钉转化为圆钉的测算，即方钉对应的圆钉是方钉的外接圆
class SquarePegAdaptor : public RoundPeg{
public:
    explicit SquarePegAdaptor(SquarePeg* sp) : m_square_peg(sp){}
    virtual int get_radius() override{
        int w = m_square_peg->get_width();
        return w * sqrt(2) / 2;
    }

private:
    SquarePeg* m_square_peg = nullptr;
};


int main(){
    //一个半径为10的圆孔
    RoundHole* hole = new RoundHole(10);

    //半径为5和20的方钉和他们的适配器
    SquarePeg* small_square_peg = new SquarePeg(5);
    SquarePeg* large_square_peg = new SquarePeg(20);
    SquarePegAdaptor* small_square_peg_adaptor = new SquarePegAdaptor(small_square_peg);
    SquarePegAdaptor* large_square_peg_adaptor = new SquarePegAdaptor(large_square_peg);

    // hole->isFit(samll_square_peg);  // 编译报错
    // hole->isFit(large_square_peg);  // 编译报错

    if(hole->isFit(small_square_peg_adaptor)){
        cout<<"small square peg fits the hole"<<endl;
    }else{
        cout <<"small square peg doesn't fit the hole"<<endl;
    }
    if(hole->isFit(large_square_peg_adaptor)){
        cout<<"large square peg fits the hole"<<endl;
    }else{
        cout <<"large square peg doesn't fit the hole"<<endl;
    }
    return 0;
}