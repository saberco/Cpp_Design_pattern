//实例是磁盘读取文件，采用两个装饰器，一个是进行加密，一个是进行压缩,特点是不改变接口，只是对接口的功能进行一个加强
#include<string>
#include <iostream>
#include <cstdio>

using namespace std;
//装饰器和具体部件的共同基类， 是客户端访问的具体接口
class DataSource{
public:
    virtual void writeData(string data) = 0;
};

//具体组件的实现，封装了基础功能
class FileDataSource : public DataSource{
public:
    explicit FileDataSource(string file_name):m_file_name(file_name){}
    virtual void writeData(string data) override{
        printf("写入文件%s 中： %s\n", m_file_name.c_str(), data.c_str());
        return;
    }

private:
    string m_file_name;
};

//基础的装饰器类，是其他组件和装饰器的基类。该类的主要任务是定义所有具体装饰的封装接口。
// 封装的默认实现代码中可能会包含一个保存被封装组件的成员变量，并且负责对其进行初始化。
class DataSourceDecorator : public DataSource{
public:
    explicit DataSourceDecorator(DataSource* ds) : m_data_source(ds){}
    void writeData(string data) override{
        m_data_source->writeData(data);
    }

protected:
    DataSource* m_data_source;
};

//两个装饰器，一个加密一个压缩
class EncryptionDecorator : public DataSourceDecorator{
public: 
    using DataSourceDecorator::DataSourceDecorator;
    void writeData(string data) override{
        data = "已加密(" + data + ")";
        m_data_source->writeData(data);
        return;
    }
};

class CompressionDecorator : public DataSourceDecorator{
public: 
    using DataSourceDecorator::DataSourceDecorator;
    void writeData(string data) override{
        data = "已压缩(" + data + ")";
        m_data_source->writeData(data);
        return;
    }
};


int main(){
    FileDataSource* source1 = new FileDataSource("stdout");

    //明码写入文件
    source1->writeData("tomo");
    //压缩
    CompressionDecorator* source2 = new CompressionDecorator(source1);
    source2->writeData("tomo");
    //压缩且加密
    EncryptionDecorator* source3 = new EncryptionDecorator(source2);
    source3->writeData("tomo");

    delete source1;
    delete source2;
    delete source3;
    return 0;
}