//实例为保存文本编辑器的上一个状态

#include <string>
#include <memory>
#include <cstdio>
#include <iostream>

using namespace std;


//备忘录类
class Snapshot{
public:
    Snapshot(string text, int x, int y, double w)
        : m_text(text), m_curx(x), m_cury(y), m_width(w){}
    
    string get_text(){
        return m_text;
    }

    int get_cur_x(){
        return m_curx;
    }

    int get_cur_y(){
        return m_cury;
    }

    double get_width(){
        return m_width;
    }

private:
    const string m_text;
    const int m_curx;
    const int m_cury;
    const double m_width;
};

//原发器包含了一些可能会随时间变化的重要数据
//它还定义了在备忘录中保存自身状态的方法, 以及从备忘录中恢复状态的方法

class Editor{
public:
    void set_text(string text){
        m_text = text;
    }

    void set_cursor(int x,int y){
        m_curx = x;
        m_cury = y;
    }

    void set_width(double width){
        m_width = width;
    }

    //在备忘录保存当前状态
    shared_ptr<Snapshot> createSnapshot(){
        auto res = make_shared<Snapshot>(m_text, m_curx,m_cury, m_width);
        printf("创建编辑器快照成功, text:%s x:%d y:%d width:%.2f\n", m_text.c_str(), m_curx,m_cury, m_width);
        return res;
    }
    //从备忘录恢复当前状态

    void restore(shared_ptr<Snapshot> sptr){
        m_text = sptr->get_text();
        m_curx = sptr->get_cur_x();
        m_cury = sptr->get_cur_y();
        m_width = sptr->get_width();
        printf("恢复编辑器状态成功, text:%s x:%d y:%d width:%.2f\n", m_text.c_str(), m_curx,m_cury, m_width);
    }

    void display(){
        printf("当前状态为 text:%s x:%d y:%d width:%.2f\n", m_text.c_str(), m_curx,m_cury, m_width);
    }
private:
    //文本
    string m_text;
    //光标位置
    int m_curx;
    int m_cury;
    //滚动条位置
    double m_width;
};

//负责人，负责执行备忘和恢复
class Command{
public:
    explicit Command(Editor* e):m_editor(e), m_backup(nullptr){}
    void makeBackup(){
        m_backup = m_editor->createSnapshot();
    }

    void undo(){
        if(m_backup != nullptr){
            m_editor->restore(m_backup);
        } 
    }

private:
    Editor* m_editor;
    shared_ptr<Snapshot> m_backup;
};


int main(){
    Editor* peditor = new Editor();
    Command command(peditor);

    //设置初始状态
    peditor->set_text("TOMO");
    peditor->set_cursor(22,33);
    peditor->set_width(3.14);
    //打印初始状态
    peditor->display();
    //保存状态
    command.makeBackup();
    //更改状态
    peditor->set_text("ABDDS");
    peditor->set_cursor(11,44);
    peditor->set_width(5.43);
    //打印更改状态
    peditor->display();
    //撤销
    command.undo();

    peditor->display();

    delete peditor;
    return 0;
}