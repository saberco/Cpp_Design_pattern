#include <string>
#include <iostream>

using namespace std;

//产品类，车
class Car{
public:
    Car(){}
    void set_car_tire(string t){
        m_tire = t;
        cout<<"set tire: "<< m_tire << endl;
    }

    void set_car_steering_wheel(string t){
        m_steering_wheel = t;
        cout<<"set steering wheel:  "<< m_steering_wheel<< endl;
    }

    void set_car_engine(string t){
        m_engine = t;
        cout<<"set engine: "<< m_engine << endl;
    }


private:
    string m_tire;
    string m_steering_wheel;
    string m_engine;

};

//抽象的生产者
//定义如何建造一辆车
class CarBuilder{
public:
    Car getCar(){
        return m_car;
    }
    //抽象的方法
    virtual void buildTire() = 0;
    virtual void buildSteeringWheel() = 0;
    virtual void buildEngine() = 0;
protected:
    Car m_car;
};

//具体的生产者
class BenzBuilder : public CarBuilder{
public:
    virtual void buildTire() override {
        m_car.set_car_tire("benz_tire");
    }

    virtual void buildSteeringWheel()override{
        m_car.set_car_steering_wheel("benz_steering_wheel");
    }

    virtual void buildEngine() override{
        m_car.set_car_engine("benz_car_engine");
    }

};

class AudiBuilder : public CarBuilder{
public:
    virtual void buildTire() override {
        m_car.set_car_tire("Audi_tire");
    }

    virtual void buildSteeringWheel()override{
        m_car.set_car_steering_wheel("Audi_steering_wheel");
    }

    virtual void buildEngine() override{
        m_car.set_car_engine("Audi_car_engine");
    }
};

//管理者，管理如何搭建一辆车，比如要几个轮胎，几个引擎等等
class Director{
public:
    Director(): m_builder(nullptr){}

    void set_builder(CarBuilder* cb){
        m_builder = cb;
    }

    //组装汽车
    Car ConstructCar(){
        m_builder->buildTire();
        m_builder->buildSteeringWheel();
        m_builder->buildEngine();
        return m_builder->getCar();
    }

private:
    CarBuilder* m_builder;

};

int main(){
    CarBuilder* pBuilder = nullptr;
    Director* pDirector = new Director();
    //产品
    Car car;

    //造奔驰
    cout<<"================造奔驰================"<<endl;
    pBuilder = new BenzBuilder();
    pDirector->set_builder(pBuilder);
    car = pDirector->ConstructCar();
    delete pBuilder;
    pBuilder = nullptr;

    //造奥迪
    cout<<"================造奥迪================"<<endl;
    pBuilder = new AudiBuilder();
    pDirector->set_builder(pBuilder);
    car = pDirector->ConstructCar();
    delete pBuilder;
    pBuilder = nullptr;

    return 0;
}