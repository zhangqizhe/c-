#include<iostream>
#include<typeinfo>
#include<string>
using namespace std;

/*
1.�̳еı��ʺ�ԭ��
2.������Ĺ������
3.���ء����ǡ�����
4.��̬�󶨺Ͷ�̬��
5.��̬   vfptr��vftable
6.����������ԭ��
7.���ؼ̳��Լ�����
8.�����  vbptr��vbtable
9.RTTI
10.C++��������ǿת
11.�̳ж�̬�����������������
*/

/*
C++���Լ����ṩ����������ת����ʽ
int a = (int)b;
const_cast	ȥ���������Ե�һ������ת��
static_cast		�ṩ��������Ϊ��ȫ������ת��(û���κ���ϵ������֮���ת���ͱ�����)
reinterpret_cast	������C����ǿ������ת��
dynamic_cast	��Ҫ���ڼ̳нṹ�У�����֧��RTTI����ʶ�������ת��

static_cast����ʱ�ڵ�����ת�� dynamic_cast����ʱ�ڵ�����ת�� ֧��RTTIʶ��
*/
#if 0

class Base
{
public:
	virtual void func() = 0;
};
class Derive1 : public Base
{
public:
	void func() { cout << "call Derive1::func" << endl; }
};
class Derive2 : public Base
{
public:
	void func() { cout << "call Derive2::func" << endl; }
	//derive02ʵ���¹��ܵ�API�ӿں���
	void derive02func()
	{ 
		cout << "call Derive2::func" << endl; 
	}
};
void show(Base* p)
{
	//dynamic_cast����pָ���Ƿ�ָ�����һ��Derive2���͵Ķ���
	//p->vfptr->vftable RTTI��Ϣ ����ǣ�dynamic_castת�����ͳɹ�
	//����Derive2����ĵ�ַ����pd2;���򷵻�nullptr
	//static_cast����ʱ�ڵ�����ת�� dynamic_cast����ʱ�ڵ�����ת�� ֧��RTTIʶ��
	Derive2* pd2 = dynamic_cast<Derive2*>(p);
	if (pd2 != nullptr)
	{
		pd2->derive02func();
	}
	else
	{
		p->func();
	}
}
int main()
{
	Derive1 d1;
	Derive2 d2;
	show(&d1);
	show(&d2);

	/*
	//static_cast ��������  ��-�� ����������  ������static_cast����ת��
	//static_cast
	//int a = 10;
	//int* p = nullptr;
	//short* b = reinterpret_cast<short*>(p);

	//const int a = 10;
	//int* p = (int*)&a;
	//int* p2 = const_cast<int*>(&a);
	//const_cast<�����������ָ�������������>
	//int b = const_cast<int>(a);
	*/
	return 0;
}

#endif
/*
C++�Ķ��ؼ̳�  -  ���μ̳е�����  �������ж�ݼ�ӻ�������� ������Ƶ�����
�ô����������������ĸ��� 
*/

#if 0
class A
{
public:
	A(int data) :ma(data) { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl;  }
protected:
	int ma;
};
//===================================
class B : virtual public A
{
public:
	B(int data) : A(data),mb(data) { cout << "B()" << endl; }
	~B() { cout << "~B()" << endl; }
protected:
	int mb;
};
class C : virtual public A
{
public:
	C(int data) : A(data),mc(data) { cout << "C()" << endl; }
	~C() { cout << "~C()" << endl; }
protected:
	int mc;
};
//========================================
class D : public B,public C
{
public:
	//��A::A�� : û�к��ʵ�Ĭ�Ϲ��캯������
	//����� ��D����Ҫ���¹���
	D(int data) : A(data), B(data),C(data), md(data) { cout << "D()" << endl; }
	~D() { cout << "~D()" << endl; }
protected:
	int md;
};
int main()
{
	D d(10);
	return 0;
}

#endif

/*
���ؼ̳�:����ĸ���  һ���������ж������
class C : public A,public B


������(�д��麯������)	/	����� ����̳е��࣬��������� vbptr vbtable
virtual
1.���γ�Ա�������麯��
2.�������μ̳з�ʽ������̳С�����̳е��࣬���������
*/
#if 0
class A
{
public:
	virtual void func()
	{
		cout << "call A:func()" << endl;
	}
private:
	int ma;
};
class B : virtual public A
{
public:
	void func()
	{
		cout << "call B:func()" << endl;
	}
private:
	int mb;
};
/*
A a;	4���ֽ�
B b,ma,mb	8���ֽ�+4=12�ֽ�
*/
int main()
{
	//����ָ��ָ�������������Զָ�������������ಿ�ֵ���ʼ��ַ
	A* p = new B();
	p->func();
	delete p;
	return 0;
}
#endif
#if 0
class Base
{
public:
	Base()
	{
		cout << "call Base()" << endl;
		clear();
	}
	void clear()
	{
		memset(this, 0, sizeof(*this));
	}
	virtual void show()
	{
		cout << "call Base::show()" << endl;
	}
};
class Derive : public Base
{
public:
	Derive()
	{
		cout << "call Derive()" << endl;
	}
	void show()
	{
		cout << "call Derive::show()" << endl;
	}
};
/*
���������ڴ�ָ��Base->vftable
*/
int main()
{
	Base* pb1 = new Base();
	/*
	mov eax,dword ptr[pb1]
	mov ecx,dword ptr[eax]	ecx:0x00000000 ����Base::show()
	call ecx
	*/
	pb1->show();	//��̬��
	delete pb1;

	Base *pb2 = new Derive();
	/*
	
	*/
	pb2->show();	//��̬��
	delete pb2;

	return 0;
}

class Base
{
public:
	virtual void show(int i = 10)
	{
		cout << "call Baswe::show i" << i << endl;
	}
};
class Derive : public Base
{
public:
	void show(int i = 20)
	{
		cout << "call Derive::show i" << i << endl;
	}
};
int main()
{
	Base* p = new Derive();		//����������
	/*
	
	*/
	p->show();		//��̬�� p->Derive vfptr -> Dervie vftable
	delete p;
	return 0;
}

#endif

/*
���������ͨ����ʲô����
һ���ʲô����Ƴɳ�����
*/


#if 0 
//����Ļ���  ��ָ  ��->����һ��ʵ�������
/*
����Animal�ĳ��ԣ���������Animal����ĳ��ʵ�������
1.string _name;	�����еĶ���ʵ����ͨ���̳�Animalֱ�Ӹ��ø�����
2.�����е������ౣ��ͳһ�ĸ���/��д�ӿ�

ӵ�д��麯�����࣬����������!(Animal)

�����಻����ʵ�������󣬵��ǿ��Զ���ָ������ñ���
*/
class Animal
{
public:
	Animal(string name) :_name(name) {}
	//���麯��
	virtual void bark() {}
protected:
	string _name;
};
class Cat : public Animal
{
public:
	Cat(string name) :Animal(name) { }
	void bark() { cout << _name << " bark:miaomiao" << endl; }
};
class Dog : public Animal
{
public:
	Dog(string name) :Animal(name) { }
	void bark() { cout << _name << " bark:wangwang" << endl; }
};
class Pig : public Animal
{
public:
	Pig(string name) :Animal(name) { }
	void bark() { cout << _name << " bark:laolao" << endl; }
};
void bark(Animal* p)
{
	p->bark();	//Animal::bark�麯������̬����
}

//�����Ļ���
class Car	//������
{
public:
	Car(string name,double oil):_name(name),_oil(oil){}
	//��ȡ����ʣ�����������ܵĹ�����
	double getLeftMiles()
	{
		return _oil * this->getMilesPerGallon();	//������̬��
	}
	string getName()const { return _name; }
protected:
	string _name;
	double _oil;
	virtual double getMilesPerGallon() = 0;	//���麯��
};
class Bnze : public Car
{
public:
	Bnze(string name, double oil):Car(name,oil){}
	double getMilesPerGallon() { return 20.0; }
};
class Audi : public Car
{
public:
	Audi(string name, double oil) :Car(name, oil) {}
	double getMilesPerGallon() { return 18.0; }
};
class BMW : public Car
{
public:
	BMW(string name, double oil) :Car(name,oil) {}
	double getMilesPerGallon() { return 20.0; }
};

//���ⲿ�ṩһ��ͳһ�Ļ�ȡ����ʣ��·������API
void showCarLeftMiles(Car& car)
{
	cout << car.getName() << "left miles:" << car.getLeftMiles() <<"����"<< endl;
		//��̬�� call Car::getLeftMiles()
}
int main()
{
	Bnze b1("����",20.0);
	Audi a("�µ�",20.0);
	BMW b2("����",20.0);

	showCarLeftMiles(b1);
	showCarLeftMiles(a);
	showCarLeftMiles(b2);
	return 0;
}

#endif

/*
��ν��Ͷ�̬?
��̬(����ʱ��)�Ķ�̬:�������ء�ģ��(����ģ�����ģ��)
bool compare(int,int){	}
bool compare(double,double){	}

compare(10,20);	call compare_int_int		�ڱ���׶ξ�ȷ���ú������õİ汾
compare(10.5,20.5);	call compare_double_double		�ڱ���׶ξ�ȷ���ú������õİ汾

template<typename T>
bool compare(T a,T b){	}

compare<int>(10,20);		=>	int ʵ����һ�� compare<int>		ģ���ʵ���������ڱ���׶�
compare(10.5,20.5);		=>	double  ʵ����һ�� compare<double>		ģ���ʵ���������ڱ���׶�
	
��̬(����ʱ��)�Ķ�̬:
�ڼ̳нṹ�У�����ָ��(����)ָ�����������ͨ����ָ��(����)����ͬ�����Ƿ���(�麯��)��
����ָ��ָ���Ǹ���������󣬾ͻ�����Ǹ�����������ͬ�����Ƿ�������Ϊ��̬
pbase->show();
��̬�ײ�ʹͨ����̬����ʵ�ֵ�,pbase-> ����˭��vfptr->��������˭��vftable
									-> ��Ȼ���õ��Ƕ�Ӧ�����������ķ�����

�̳еĺô���ʲô?
1.����������ĸ���
2.�ڻ������ṩͳһ���麯���ӿڣ��������������д��Ȼ��Ϳ���ʹ�ö�̬��
*/

//�����Ƶ�6��ԭ��   "��-��ԭ��"  ���޸Ĺرգ�����չ����

#if 0
class Animal
{
public:
	Animal(string name) :_name(name){}
	virtual void bark(){}
protected:
	string _name;
};
class Cat : public Animal
{
public:
	Cat(string name):Animal(name){ }
	void bark() { cout << _name << "bark:miaomiao" << endl; }
};
class Dog : public Animal
{
public:
	Dog(string name) :Animal(name) { }
	void bark() { cout << _name << "bark:wangwang" << endl; }
};
class Pig : public Animal
{
public:
	Pig(string name) :Animal(name) { }
	void bark() { cout << _name << "bark:laolao" << endl; }
};
void bark(Animal* p)
{
	p->bark();
	/*
	p->cat Cat vftable &Cat::bark
	p->dog Dog vftable &Dog::bark
	p->pig Pig vftable &Pig::bark
	*/
}

int main()
{
	Cat cat("è��");
	Dog dog("����");
	Pig pig("����");

	bark(&cat);
	bark(&dog);
	bark(&pig);
	return 0;
}

#endif

/*
�麯���Ͷ�̬�� ����:�ǲ����麯���ĵ���һ���Ƕ�̬��?	�϶����ǵ�!
����Ĺ��캯�����У������麯����Ҳ�Ǿ�̬��(���캯���е��������麯�������ᷢ����̬��)
�������ͨ��ָ��������ñ����������麯�����Ǿ��Ǿ�̬��

��̬�󶨱�����ָ��������ñ����ſ���

*/

#if 0
class Base
{
public:
	Base(int data) :ma(data) { cout << "Base()" << endl; }
	virtual void show() { cout << "Base::show()" << endl; }
protected:
	int ma;
};
class Derive :public Base
{
public:
	Derive(int data = 0) :Base(data), mb(data) {}
	void show() { cout << "Derive::show()" << endl; }
private:
	int mb;
};
int main()
{
	Base b;
	Derive d;

	//��̬��  �ö���������麯�����Ǿ�̬��
	b.show();	//�麯��	call Base::show
	d.show();	//�麯��	call Derive::show

	//��̬��(������ָ������麯��)
	Base* pb1 = &b;
	pb1->show();
	Base* pb2 = &d;
	pb2->show();

	//��̬��(���������ñ��������麯��)
	Base& rb1 = b;
	rb1.show();
	Base& rb2 = d;
	rb2.show();

	//��̬��(�麯��ͨ��ָ��������ñ������ã��ŷ�����̬��)
	Derive* pd1 = &d;
	pd1->show();
	Derive& pd2 = d;
	pd2.show();

	Derive* pd2 = &b;	
	return 0;
}

#endif
/*
����һ:��Щ��������ʵ�ֳ��麯��

�麯������:
1.�麯���ܲ�����ַ���洢��vftable����
2.����������(vfptr -> vftable -> �麯����ַ)

���캯��:
1.vritual+���캯��   NO
2.���캯����(���õ��κκ��������Ǿ�̬�󶨵�)�����麯����Ҳ���ᷢ����̬��

���������Ĺ������	1.�ȵ�ͨ���ǻ���Ĺ��캯��	2.�ŵ���������Ĺ��캯��

static��̬��Ա����	NO�� vritual+static

�����:����������	�����������õ�ʱ�򣬶����Ǵ��ڵ�!
ʲôʱ��ѻ����������������ʵ�ֳ��麯����
�����ָ��(����)ָ�����new����������������ʱ��delete pb(�����ָ��)��
����������������ʱ�򣬱��뷢����̬�󶨣�����ᵼ������������������޷�����

���������������virtual�麯������ô����������������Զ���Ϊ�麯��
*/
#if 0
class Base
{
public:
	Base(int data) :ma(data) { cout << "Base()" << endl; }
	~Base() { cout << "~Base()" << endl; }
	void show() { cout << "call Base::show()" << endl;  }
protected:
	int ma;
};
class Derive : public Base
{
public:
	Derive(int data)
		:Base(data), mb(data)
	{
		cout << "Derive()" << endl;
	}
	~Derive()
	{
		cout << "~Derive()" << endl;
	}
private:
	int mb;
};
int main()
{
	Derive d(10);
	Base* pb = &d;
	pb->show();

	return 0;
}
#endif

/*
�麯������̬�󶨺Ͷ�̬��

����:
�����������ķ���������ֵ���������Լ������б���ͬ�����һ���ķ������麯����
��ô������ķ������Զ�������麯��������֮���Ϊ���ǹ�ϵ

�ܽ�һ:
һ�������涨�����麯������ô����׶Σ�����������������Ͳ���һ��Ψһ��vftable�麯����
�麯��������Ҫ�洢�����ݾ���RTTIָ����麯���ĵ�ַ��
����������ʱ��ÿһ���麯����������ص��ڴ�.rodata��(ֻ��)

�ܽ��:
һ�������涨�����麯������ô����ඨ��Ķ���������ʱ���ڴ��п�ʼ���֣���洢һ��vfptr�麯��ָ�룬
ָ����Ӧ���͵��麯����vftable��һ�����Ͷ����n���������ǵ�vfptrָ�����ͬһ���麯����

�ܽ���:
һ���������麯���ĸ�������Ӱ������ڴ��С(vfptr),Ӱ������麯����Ĵ�С

�ܽ���:
����������еķ������ͻ���̳�����ĳ������������ֵ���������������б���ͬ��
���һ���ķ�����virtual�麯������ô�����������������Զ�������麯��
*/

#if 0
class Base
{
public:
	Base(int data=10):ma(data) {}
	//�麯��
	virtual void show() { 	cout << "Base::show()" << endl; 	}
	//�麯��
	virtual void show(int) {   cout << "Base::show(int)" << endl;  	}
protected:
	int ma;
};
class Derive : public Base
{
public:
	Derive(int data = 20) :Base(data),mb(data){ }
	/*
	�ܽ���:
	����������еķ������ͻ���̳�����ĳ������������ֵ���������������б���ͬ��
	���һ���ķ�����virtual�麯������ô�����������������Զ�������麯��
	*/
	void show() { 	cout << "Derive::show()" << endl;  }
private:
	int mb;
};
int main()
{
	Derive d(50);
	Base* pb = &d;
	/*
	pb->Base Base::show �������show����ͨ�������ͽ��о�̬��
														call  Base::show
	pb->Base Base::show �������show���麯�����ͽ��ж�̬��
	mov eax,dword ptr[pb]	��pb�е�ǰ�ĸ��ֽڷŵ�eax��
	mov ecx,dwprd ptr[eax]
	call ecx	(�麯���ĵ�ַ)	��̬(����ʱ��)�İ�(�����ĵ���)
	
	*/
	pb->show();		//��̬(����ʱ��)�İ�(�����ĵ���)	call  Base::show (0331037h)

	/*
	pb->Base Base::show(int)	��һ���麯������ʱ�͵ö�̬����
	mov eax,dword ptr[pb]
	mov ecx,dwprd ptr[eax]
	call ecx	(�麯���ĵ�ַ)	��̬(����ʱ��)�İ�(�����ĵ���)
	*/
	pb->show(10);	//��̬��			call  Base::show (03312F8h)

	cout << sizeof(Base) << endl;		//4	8	
	cout << sizeof(Derive) << endl;		//8	12

	cout << typeid(pb).name() << endl;		//class Base *
	/*
	pb�����ͣ�Base->��û���麯��
	���Baseû���麯����*pbʶ��ľ��Ǳ���ʱ�ڵ�����	*pb <=>Base����
	���Base���麯����*pbʶ��ľ�������ʱ�ڵ����� ��RTTI����
	pb->d(vfptr)->Derive vftable	  class Derive
	*/
	cout << typeid(*pb).name() << endl;		//class Base
	return 0;
}

#endif

/*
���ء����ǡ�����
1.���ع�ϵ
	һ�麯��Ҫ���أ��������ͬһ���������У����Һ���������ͬ�������б�ͬ

2.����(�����������)�Ĺ�ϵ
�ڼ̳нṹ���У��������ͬ����Ա���ѻ����ͬ����Ա�����ص�����

=================================================================
1.�Ѽ̳нṹ��Ҳ˵�ɴ���(����)����(������)�Ľṹ
2.
������� -> ���������	���ʹ��µ��ϵ�ת��	Y
��������� -> �������	���ʹ��ϵ��µ�ת��	N

����ָ��(����) -> ���������	���ʹ��µ��ϵ�ת��	Y
������ָ��(����) -> �������	���ʹ��µ��ϵ�ת��	N	����ȫ���漰���ڴ�ķǷ�����
�ڼ̳нṹ�н������µ�����ת����Ĭ��ֻ֧�ִ��ϵ��µ�����ת��
*/

#if 0

int main()
{

	return 0;
}

#endif
/*

1.������Ӽ̳п��Լ̳������еĳ�Ա(�����ͷ���)���������캯������������

��������ô��ʼ���ӻ���̳����ĳ�Ա�����أ�
���ͨ�����û�����Ӧ�Ĺ��캯������ʼ��

������Ĺ��캯�������������������ʼ�������������ಿ��
������ӻ���̳����ĳ�Ա�ĳ�ʼ����������˭�����أ����ɻ���Ĺ������������������ 

�����������������Ĺ����ǣ�
1.��������û���Ĺ��캯������ʼ���ӻ���̳����ĳ�Ա
2.�����������Լ��Ĺ��캯������ʼ���������Լ����еĳ�Ա
......��������������������
3.����������������������ͷ��������Ա����ռ�õ��ⲿ��Դ(���ڴ棬�ļ�)
4.���û���������������ͷ��������ڴ��У��ӻ���̳����ĳ�Ա����ռ�õ��ⲿ��Դ(���ڴ棬�ļ�)
*/
#if 0
class Base
{
public:
	Base(int data) :ma(data) { cout << "Base()" << endl; }
	~Base() { cout << "~Base()" << endl; }
protected:
	int ma;
};
class Derive : public Base
{
public:
	Derive(int data)
		:Base(data), mb(data)
	{
		cout << "Derive()" << endl;
	}
	~Derive()
	{
		cout << "~Derive()" << endl;
	}
private:
	int mb;
};
int main()
{
	Derive d(20);

	return 0;
}
#endif

/*
1.�̳еı��ʺ�ԭ��
�̳еı��ʣ�a.����ĸ���	b.ʵ�ֶ�̬�Ļ���
�����֮��Ĺ�ϵ��
��ϣ� a part of...  ...һ���ֵĹ�ϵ
�̳У� a kind of...  ...һ�ֵĹ�ϵ

�̳з�ʽ		����ķ����޶�		������ķ����޶�		(main)�ⲿ�ķ����޶�
public
					public				public						Y
				  protected			  protected						N
					private			   ���ɼ���						N
protected(����ĳ�Ա�ķ���Ȩ�ޣ��������������ǲ����ܳ����̳з�ʽ��)
					public				protected					N
					protected			protected					N
					private				���ɼ���					N
private
					public				private						N
					protected			private						N
					private			    ���ɼ���					N

�ܽ᣺
1.�ⲿֻ�ܷ��ʶ���public�ĳ�Ա��protected��private�ĳ�Ա�޷�ֱ�ӷ���
2.�ڼ̳нṹ�У�������ӻ�����Լ̳й���private�ĳ�Ա������������ȱ�޷�ֱ�ӷ���
3.protected��private������ �ڻ����ж���ĳ�Ա���뱻��������ʣ����ǲ��뱻�ⲿ���ʣ���ô�ڻ����У�����س�Ա�����protected��;
							 �����������ⲿ����������ʣ���ô�ڻ����У��Ͱ���س�Ա�����private˽�еġ�

Ĭ�ϵļ̳з�ʽ��ʲô��
Ҫ������������class����ģ�����struct�����
class����������࣬Ĭ�ϵļ̳з�ʽ����private˽�е�
struct����������࣬Ĭ�ϵļ̳з�ʽ����public���е�
*/

#if 0
class A
{
public:
	int ma;
protected:
	int mb;
private:	
	int mc;		//ֻ���Լ�������Ԫ�ܷ���˽�еĳ�Ա
};
class B : public A		//�̳� A->����/����  B->������/����   
{
public:
	int md;
protected:
	int me;
private:
	int mf;
};
int main()
{

	return 0;
}
#endif