#include<iostream>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

/*
指向类成员(成员变量和成员方法)的指针
*/

#if 0
class Test
{
public:
	void func()
	{
		cout << "call Test::func" << endl;
	}
	static void static_func()
	{
		cout << "Test::static_func" << endl;
	}
	int ma;
};
int main()
{
	Test t1;
	Test* t2 = new Test();
	int Test::*p = &Test::ma;

	delete t2;
	return 0;
}
# endif
/*
类的各种成员  - 成员方法/变量
普通成员方法 => 编译器会添加一个this形参变量
1、属于类的作用域
2、调用该方法时，need依赖一个对象(常对象是无法调用的 实参:const CGoods*  形参: CGoods *this)
3、可以任意访问对象的私有成员变量   （protect继承）  目前只考虑公有和私有 

static静态成员方法 => 不会生成this形参变量
1、属于类的作用域
2、用类名作用域来调用方法
3、可以任意访问对象的私有成员，仅限于不依赖对象的成员(只能调用其他的static静态成员)
 


普通方法和静态方法的区别？
普通方法是用对象来调用，静态方法是用类作用域来调
普通方法编译会产生this指针，接收当前对象的地址就得使用对象来调用，把地址当作实参传递进来
静态方法编译不会产生this指针，不need接收一个对象的地址

！！！如果这个方法访问的是所有对象共享的信息，那最好将这个方法写成静态的方法。

const常成员方法  =>  const CGoods *this
1、属于类的作用域
2、调用依赖一个对象，普通对象或者常对象都可以
3、可以任意访问对象的私有成员，但是只能读不能写
*/

#if 0
class CDate
{
public:
	CDate(int a, int b, int c)	//自定义一个构造函数，编译器就不会再产生默认的构造了
	{
		_year = a;
		_month = b;
		_day = c;
	}
	void show()const
	{
		cout << _year << "/" << _month << "/" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

class CGoods
{
public:
	CGoods(const char* n, int a, double p, int y, int m, int d)
		:_date(y, m, d)	//#1 构造函数的初始化列表 
		, _amount(a)	//int _amount = a;
		,_price(p)
	{
		//#2 当前类类型构造函数体
		strcpy(_name, n);
		//_amount = a;	//int _amount;_amount = a; 
		_count++;	//记录所有产生的新对象的数量
	}
	//普通的成员方法
	void show()		//打印商品的私有的信息	CGood *this
	{
		cout << "name:" << _name << endl;
		cout << "amount:" << _amount << endl;
		cout << "price:" << _price << endl;
		_date.show();
	}
	//常成员方法	只要是只读操作的成员方法，一律实现成const常成员方法
	void show()const		// const CGood *this
	{
		cout << "name:" << _name << endl;
		cout << "amount:" << _amount << endl;
		cout << "price:" << _price << endl;
		_date.show();
	}
	//静态的成员方法 没有this指针的
	static void showCGoodsCount()
	{
		cout << "所有商品种类的数量是:" << _count << endl;
	}
private:
	char* _name;
	int _amount;
	double _price;
	CDate _date;	//成员对象	1.分配内存	2.调用构造函数
	//静态成员变量  不属于对象，而属于类级别的	
    static int _count;	//声明 用来记录商品对象的总数量
}; 
//static成员变量一定要在类外进行定义并且初始化
int CGoods::_count = 0;
int main()
{
	CGoods good1("商品", 100, 35.0, 2019, 5, 12);
	good1.show();

	CGoods good2("商品", 100, 35.0, 2019, 5, 12);
	good2.show();

	CGoods good3("商品", 100, 35.0, 2019, 5, 12);
	good3.show();
	CGoods good4("商品", 100, 35.0, 2019, 5, 12);
	good4.show();

	//统计所有商品的总数量
	//静态方法，用类的作用域来调用
	CGoods::showCGoodsCount();

	const CGoods good5("非卖品", 100, 35.0, 2019, 01, 8);
	good5.show();	//CGoods::show(&good5)	const CGoods* -> const CGoods *this
	return 0;
}

#endif

/*
构造函数的初始化列表：可以指定当前对象成员变量的初始化方式
*/

#if 0
class Test
{public:
	Test(int data = 10) :mb(data), ma(mb)
	{}
	void show()
	{
		cout << "ma:" << ma << "mb:" << mb << endl;
	}
private:
	//成员变量的初始化和它们定义的顺序有关，和构造函数初始化列表中出现的先后顺序无关!
	int ma;
	int mb;		
	};
int main()
{
	Test t;
	t.show();
	return 0;
}

#endif

#if 0
//日期类
class CDate
{
public:
	CDate(int a, int b, int c)	//自定义一个构造函数，编译器就不会再产生默认的构造了
	{
		_year = a;
		_month = b;
		_day = c;
	}
	void show()
	{
		cout << _year << "/" << _month << "/" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

class CGoods
{
public:
	CGoods(const char* n, int a, double p,int y,int m,int d)
		:_date(y,m,d)	//#1 构造函数的初始化列表 
		, _amount(a)	//int _amount = a;
	{
		//#2 当前类类型构造函数体
		strcpy(_name, n);
		_amount = a;	//int _amount;_amount = a; 
		_price = p;
	}
	void show()
	{
		cout << "name:" << _name << endl;
		cout << "amount:" << _amount << endl;
		cout << "price:" << _price << endl;
		_date.show();
	}
private:
	char* _name;
	int _amount;
	double _price;
	CDate _date;	//成员对象	1.分配内存	2.调用构造函数
};
int main()
{
	CGoods goood("商品", 100, 35.0, 2019, 5, 12);
	return 0;
}
#endif

/*
浅拷贝要自定义拷贝构造函数和赋值重载函数
String类型
循环队列 Queue
*/

//编写类String的构造函数、析构函数和赋值函数

#if 0
class String
{
public:
	String(const char *str = nullptr)	//普通构造函数
	{
		if (str != nullptr)
		{
			m_data = new char[strlen(str) + 1];
			strcpy_s(this->m_data, str);
		}
		else
		{
			m_data = new char[1];
			*m_data = '\0';
		}
	};
	String(const String& other)		//拷贝构造函数
	{
		m_data = new char[strlen(other.m_data) + 1];
		strcpy_s(m_data, other.m_data);
	}
	~String(void)						//析构函数
	{
		delete[]m_data;
		m_data = nullptr;
	}
	//String& 是为了支持连续的operator=赋值操作
	String& operator = (const String & other)//赋值函数
	{
		if (this == &other)
		{
			return *this;
		}
		
		delete[]m_data;
		m_data = new char[strlen(other.m_data) + 1];
		strcpy_s(m_data, other.m_data);
		return *this;
	}

private:
	char *m_data;		//用于保存字符串

};


int main()
{
	//调用带const char*参数的构造函数
	String str1;
	String str2("hello");
	String str3;

	//调用拷贝构造函数
	String str4 = str3;
	String str5(str3);

	//调用赋值重载函数
	str1 = str2;

	return 0;
}
#endif
/*
this指针：一个类产生的很多对象，每一个对象都有自己的一套成员变量，但是用一个类型的对象共享一套成员方法。 用于区分类型中对象
成员方法，方法的参数都会添加一个this指针


构造函数：
	定义对象时，自动调用，可以重载；构造完成，对象产生了
析构函数：
	不带参数，不带重载，只有一个析构函数；析构完成了，对象就不存在了
.data(数据段)的对象，是在程序启动是构造，结束是析构。
heap(堆段)的对象，是在new的时候进行构造，delete的时候析构
stack(栈段)的对象  进入函数到它定义的地方去构造，出了函数作用域，这个函数就要析构
		
对象的浅拷贝和深拷贝
对象默认的拷贝构造是做内存的数据拷贝
关键是对象如果占用外部资源,那么浅拷贝就出现问题了
*/

#if 0
class SeqStack
{
public:
	//构造函数：开辟资源
	SeqStack(int size = 10)
	{
		cout << this << " SeqStack()" << endl;
		_pstack = new int[size];
		_top = -1;
		_size = size;
	}
	//自定义拷贝构造函数	《=		对象的浅拷贝现在有问题了
	SeqStack(const SeqStack& src)
	{
		cout << "SeqStack(const Se
			qStack& src)" << endl;
		_pstack = new int[src._size];
		for (int i = 0; i <= src._top; ++i)
		{
			_pstack[i] = src._pstack[i];
		}//深拷贝
		_top = src._top;
		_size = src._size;
	}
	//析构函数：释放资源
	~SeqStack()		
	{
		cout << this << " ~SeqStack()" << endl;
		delete[]_pstack;
		_pstack = nullptr;
	}
	void push(int val)
	{
		if (full())
			resize();
		_pstack[++_top] = val;
	}
	void pop()
	{
		if (empty())
			return;
		--_top;
	}
	int top()
	{
		return _pstack[_top];
	}
	bool empty()
	{
		return _top == -1;
	}
	bool full()
	{
		return _top == _size - 1;
	}
private:
	int* _pstack;		//动态开辟数组，存储顺序栈的元素
	int _top;		//指向栈顶元素的位置
	int _size;		//数组扩容的大小

	void resize()
	{
		int* ptmp = new int[_size * 2];
		for (int i = 0; i < _size; ++i)
		{
			ptmp[i] = _pstack[i];
		}
		delete[]_pstack;
		_pstack = ptmp;
		_size *= 2;
	}
};
int main()
{
	SeqStack s;	//没有提供任何构造函数的时候，会为你生成默认构造和默认析构，是空函数
	SeqStack s1(10);
	//#1和#2一模一样
	SeqStack s2 = s1;	//#1	默认拷贝构造函数-> 做直接内存数据拷贝
	//SeqStack s3(s1);	//#2
	return 0;
}
#endif

/*
构造函数和析构函数  OOP编程复习
函数的名字和类名一样，没有返回值

在主函数中不用调用构造函数和析构函数，在开辟函数的时候，自动调用构造函数，出作用域的时候，可以自动调用析构函数(都是自动调用)

先构造的后析构，后构造的先析构(顺序相反)

全局和局部都会自动进行构造和析构
堆上定义的，能够自动构造，但是不能自动析构，必须手动delete
*/
#if 0
//OOP实现一个顺序栈
class SeqStack 
{
public:
	//构造函数：开辟资源
	//可以带参数，因此可以提供多个构造函数，叫做构造函数的重载
	//重载：函数名相同，参数列表不同的一组函数，就可以构成重载操作。
	SeqStack(int size = 10)
	{ 
		cout << this << " SeqStack()" << endl;
		_pstack = new int[size];
		_top = -1;
		_size = size;
	}
	//析构函数：释放资源
	~SeqStack()		//是不带参数的，所以析构函数只能有一个
	{
		cout << this << " ~SeqStack()" << endl;
		delete[]_pstack;
		_pstack = nullptr;
	}
	void push(int val)
	{
		if (full())
			resize();
		_pstack[++_top] = val;
	}
	void pop()
	{
		if (empty())
			return;
		--_top;
	}
	int top()
	{
		return _pstack[_top];
	}
	bool empty()
	{
		return _top == -1;
	}
	bool full()
	{
		return _top == _size - 1;
	}
private:
	int* _pstack;		//动态开辟数组，存储顺序栈的元素
	int _top;		//指向栈顶元素的位置
	int _size;		//数组扩容的大小

	void resize()
	{
		int* ptmp = new int[_size * 2];
		for (int i = 0; i < _size; ++i)
		{
			ptmp[i] = _pstack[i];
		}
		delete[]_pstack;
		_pstack = ptmp;
		_size *= 2;
	}
};
int main()
{
	SeqStack* ps = new SeqStack(60);
	ps->push(70);
	ps->push(80);
	ps->pop();
	cout << ps->top() << endl;
	delete ps;	//先调用ps->~SeqStack()+然后free(ps)   delete和free的区别

	//1.开辟函数  2.调用构造函数 
	SeqStack s;
	//s.init(5);	//对象成员变量的初始化操作

	for (int i = 0; i < 15; ++i)
	{
		s.push(rand() % 100);
	}
	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}

	SeqStack s1(50);

	s1.~SeqStack();		//析构函数调用以后，我们说对象不存在了

	s1.push();	//堆内存的非法访问
	//s.release();	//释放对象成员变量占用的外部堆内存(外部资源)
	return 0;	//
}

#endif
/*
C++ OOP面向对象		OOP编程，this指针
C：各种各样的函数的定义  Struct
C++：类		=>  实体的抽象类型
实体（属性、行为）		->		ADT(abstract data type)(抽象数据类型)
	  |									|
	对象				<-（实例化）类（属性：成员变量 行为：成员方法）


OOP语言的四大特征是什么？
抽象	封装/隐藏	继承	多态

类  ->  商品实体
在类中通过访问限定符体现出来：public共有的 private私有的 protected保护的

属性一般写成私有的   方法一般写成公有的
*/

#if 0
const int NAME_LEN = 20;
class CGoods		// =>商品的抽象数据类型   这个类型不占空间
{
public:	//给外部提供公有的成员方法，来访问私有的属性
	//做商品数据初始化用的
	void init(const char* name, double price, int amount);
	//打印商品信息
	void show();
	//给成员变量提供一个getxxx或setxxx的方法 类体内实现的方法，自动处理成inline函数
	void setName(char* name)
	{
		strcpy_s(_name, name);
	};
	void setPrice(double price)
	{
		_price = price;
	};
	void setAmount(int amount)
	{
		_amount = amount;
	};

	const char* getName()
	{
		return _name;
	};
	double getPrice()
	{
		return _price;
	};
	int getAmount()
	{
		return _amount;
	};
private:	//属性一般都是私有的成员变量
	char _name[NAME_LEN];   //名称
	double _price;			//单价
	int _amount;			//数量
};
void CGoods::init(const char* name, double price, int amount)
{
	strcpy_s(_name, name);
	_price = price;
	_amount = amount;
};
void CGoods::show()
{
	cout << "name:" << _name << endl;
	cout << "price:" << _price << endl;
	cout << "amount:" << _amount << endl;
};
int main()
{
	/*
	CGoods可以定义无数的对象，每一个对象都有自己的成员变量，但是它们共享一套成员方法

	show() => 怎么知道处理哪个对象的信息？
	init(name,price,amount) => 怎么知道把信息初始化给哪一个对象的呢？

	类的成员方法一经编译，所有的方法参数，都会加一个this指针，接受调用该方法的对象的地址
	*/
	//cl 02c++面向对象.cpp /dlreportSingleClassLayoutCGoods		借助指令查看内存大小
	//计算对象内存大小的时候     对象内存大小 => 成员变量有关
	CGoods good;	//类实例化了一个对象

	good.init("面包",10.0,20);
	good.show();
	good.setPrice(20.5);
	good.setAmount(100);
	good.show();

	return 0;
}

#endif