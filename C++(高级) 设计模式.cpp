#include<iostream>
#include<mutex>
#include<string>
#include<memory>
using namespace std;

/*
����ģʽ:һ���಻�ܴ������ٴζ���,��Զֻ�ܵõ������͵�һ�������ʵ��

���õ���,������־ģ��,���ݿ�ģ��

����ģʽ:
����ʽ����ģʽ:��û�л�ȡʵ������,ʵ��������Ѿ�������
����ʽ����ģʽ:Ψһ��ʵ������,ֱ����һ�λ�ȡ����ʱ��,�Ų���
*/

#if 0
//����ʽ����ģʽ  һ�����̰߳�ȫ��
class Singleton
{
public:
	static Singleton* getInstance()	//#3 ��ȡ���Ψһʵ������Ľӿڷ���
	{
		return &instance;
	}
private:
	static Singleton instance;	//#2 ����һ��Ψһ�����ʵ������
	Singleton()		//#1 ���캯��˽�л�
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
//����ʽ����ģʽ => �ǲ����̰߳�ȫ?		=> �̰߳�ȫ������ʽ����ģʽ
class Singleton
{
public:
	//�ǲ��ǿ����뺯��?		�� + ˫���ж�
	static Singleton* getInstance()	//#3 ��ȡ���Ψһʵ������Ľӿڷ���
	{
		//lock_guard<std::mutex> guard(mtx);	//��������̫����
		if (instance == nullptr)
		{
			lock_guard<std::mutex> guard(mtx);
			if (instance == nullptr)
			{
				/*
				1.�����ڴ�
				2.�������
				3.��instance��ֵ
				*/
				instance = new Singleton();
			}
		}
		return instance;
	}
private:
	static Singleton *volatile instance;	//#2 ����һ��Ψһ�����ʵ������
	Singleton()		//#1 ���캯��˽�л�
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
�򵥹���	Simple Factory
��������	Factory Method
���󹤳�	Abstract Factory

����ģʽ:��Ҫ�Ƿ�װ�˶���Ĵ���
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
		cout << "�����һ����������:" << _name << endl;
	}
};
class Audi :public Car
{
public:
	Audi(string name) :Car(name) {}
	void show()
	{
		cout << "�����һ���µ�����:" << _name << endl;
	}
};

//��������
class Factory
{
public:
	virtual Car* creatCar() = 0;	//��������
};
//������
class BMWFactory : public Factory
{
public:
	Car* creatCar(string name)
	{
		return new Bmw(name);
	}
};
//�µϹ���
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
	//���ڿ��ǲ�Ʒ һ���Ʒ(�й�����ϵ��ϵ�в�Ʒ)

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
//�򵥹���
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
			cerr << "���빤���Ĳ�������ȷ:" << ct << endl;
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