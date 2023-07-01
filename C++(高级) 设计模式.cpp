#include<iostream>
#include<mutex>
#include<string>
#include<memory>
using namespace std;

/*
单例模式:一个类不管创建多少次对象,永远只能得到该类型的一个对象的实例

常用到的,比如日志模块,数据库模块

单例模式:
饿汉式单例模式:还没有获取实例对象,实例对象就已经产生了
懒汉式单例模式:唯一的实例对象,直到第一次获取它的时候,才产生
*/

#if 0
//饿汉式单例模式  一定是线程安全的
class Singleton
{
public:
	static Singleton* getInstance()	//#3 获取类的唯一实例对象的接口方法
	{
		return &instance;
	}
private:
	static Singleton instance;	//#2 定义一个唯一的类的实例对象
	Singleton()		//#1 构造函数私有化
	{

	}
	Singleton(const Singleton&) = delete;
	Singleton& operator = (const Singleton&) = delete;
};
Singleton Singleton::instance;
int main()
{
	//Singleton* p1 = Singleton::getInstance();
	//Singleton* p2 = Singleton::getInstance();
	//Singleton* p3 = Singleton::getInstance();

	//Singleton t = *p1;

	return 0;
}
#endif

#if 0
std::mutex mtx;
//懒汉式单例模式 => 是不是线程安全?		=> 线程安全的懒汉式单例模式
class Singleton
{
public:
	//是不是可重入函数?		锁 + 双重判断
	static Singleton* getInstance()	//#3 获取类的唯一实例对象的接口方法
	{
		//lock_guard<std::mutex> guard(mtx);	//锁的粒度太大了
		if (instance == nullptr)
		{
			lock_guard<std::mutex> guard(mtx);
			if (instance == nullptr)
			{
				/*
				1.开辟内存
				2.构造对象
				3.给instance赋值
				*/
				instance = new Singleton();
			}
		}
		return instance;
	}
private:
	static Singleton *volatile instance;	//#2 定义一个唯一的类的实例对象
	Singleton()		//#1 构造函数私有化
	{

	}
	Singleton(const Singleton&) = delete;
	Singleton& operator = (const Singleton&) = delete;
};
Singleton * volatile Singleton::instance = nullptr;

int main()
{
	Singleton* p1 = Singleton::getInstance();
	Singleton* p2 = Singleton::getInstance();
	Singleton* p3 = Singleton::getInstance();
	 
	return 0;
}
#endif

/*
简单工厂	Simple Factory
工厂方法	Factory Method
抽象工厂	Abstract Factory

工厂模式:主要是封装了对象的创建
*/
class Car
{
public:
	Car(string name):_name(name){}
	virtual void show() = 0;
protected:
	string _name;
};
class Bmw :public Car
{
public:
	Bmw(string name):Car(name){}
	void show()
	{
		cout << "获得了一辆宝马汽车:" << _name << endl;
	}
};
class Audi :public Car
{
public:
	Audi(string name) :Car(name) {}
	void show()
	{
		cout << "获得了一辆奥迪汽车:" << _name << endl;
	}
};

//工厂方法
class Factory
{
public:
	virtual Car* creatCar() = 0;	//工厂方法
};
//宝马工厂
class BMWFactory : public Factory
{
public:
	Car* creatCar(string name)
	{
		return new Bmw(name);
	}
};
//奥迪工厂
class AudiFactory : public Factory
{
public:
	Car* creatCar(string name)
	{
		return new Audi(name);
	}
};
#if 0
int main()
{
	//现在考虑产品 一类产品(有关联关系的系列产品)

	unique_ptr<Factory> bmwfty(new BMWFactory());
	unique_ptr<Factory> audifty(new AudiFactory());
	unique_ptr<Car> p1(bmwfty->creatCar("X6"));
	unique_ptr<Car> p2(audifty->creatCar("A8"));s
	p1->show();
	p2->show();


	return 0;
}
#endif
#if 0
//简单工厂
enum CarType
{
	BMW,AUDI
};
class SimpleFactory
{
public:
	Car* creatFactory(CarType ct)
	{
		switch (ct)
		{
		case BMW:
			return new Bmw("X1");
		case AUDI:
			return new Audi("A6");
		default:
			cerr << "传入工厂的参数不正确:" << ct << endl;
			break;
		}
		return nullptr;
	}
};
int main()
{
	//Car* p1 = new BMW("X1");
	//Car* p2 = new Audi("A6");
	unique_ptr<SimpleFactory> factory(new SimpleFactory());
	unique_ptr<Car> p1 (factory->creatFactory(BMW));
	unique_ptr<Car> p2 (factory->creatFactory(AUDI));
	p1->show();
	p2->show();

	/*delete p1;
	delete p2;
	delete factory;*/
	return 0;
}
#endif