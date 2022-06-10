//实例是在画布上渲染数百万个树状对象，降低内存的使用

#include <string>
#include <iostream>
#include <map>
#include <mutex>
#include <vector>
using namespace std;
//享元类，这个类保存了树状对象的部分状态，也是不可变的那一部分，被所有树状对象复用，占用较少的内存。
//比如很多树包含共同的名字，颜色和纹理，保存在享元对象中
class TreeType{
public:
    TreeType(string n, string c, string t)
        : m_name(n), m_color(c), m_texture(t){}
    void draw(string canvas, double x, double y){
        //画的具体细节，在这里不进行实现
        //主要是创建位图和在画布某个位置绘图
        return;
    }

private:
    string m_name;
    string m_color;
    string m_texture;
};

//情景对象存储的是类的外在状态
class Tree{
public:
    Tree(double x, double y, TreeType* type)
        :m_x(x), m_y(y), m_type(type){}
    void draw(string canvas){
        return m_type->draw(canvas, m_x, m_y);
    }
private:
    double m_x;
    double m_y;
    TreeType* m_type;
};

//享元工厂，决定是否复用已有的享元或者是创建一个新的对象，同时工厂是单例的
class TreeFactory{
public:
    static TreeFactory* GetInstance(){
        if(m_instance == nullptr){
            m_mutex.lock();
            if(m_instance == nullptr){
                m_instance = new TreeFactory();
            }
            m_mutex.unlock();
        }
        return m_instance;
    }
    TreeType* GetTreeType(string name, string color, string texture){
        string key = name + "_" + color + "_" + texture;
        auto iter = m_tree_type.find(key);
        //创建新的享元模型
        if(iter == m_tree_type.end()){
            TreeType* new_type = new TreeType(name, color, texture);
            m_tree_type[key] = new_type;
            return new_type;
        }else{
            return iter->second;
        }
    }

private:
    static TreeFactory* m_instance;
    static mutex m_mutex;
    TreeFactory(){}
    //共享池，对应不同的享元类
    //key为name_color_texture
    map<string, TreeType*> m_tree_type;
};
TreeFactory* TreeFactory::m_instance = nullptr;
mutex TreeFactory::m_mutex;

//客户端，需求数量极其庞大的tree对象
class Forest{
public:
    void planTree(double x, double y, string name, string color, string texture){
        TreeType* type = TreeFactory::GetInstance()->GetTreeType(name, color, texture);
        Tree tree = Tree(x,y,type);
        m_trees.push_back(tree);
    }
    void draw(){
        for(auto tree: m_trees){
            tree.draw("canvas");
        }
    }
private:
    vector<Tree> m_trees;
};

int main(){
    Forest* pForest = new Forest();

    //在森林中种植很多树
    for(int i=0;i<500;++i){
        for(int j=0;j<500;++j){
            double x = i;
            double y = j;
            pForest->planTree(x,y,"杉树", "红色", "");
            pForest->planTree(x,y,"榕树", "绿色", "");
            pForest->planTree(x,y,"桦树", "白色", "");
        }
    }
    pForest->draw();
    delete pForest;

    return 0;
}
