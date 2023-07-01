#include<iostream>
#include<string>
using namespace std;

/*
运算符的重载：成员方法、全局方法
内存池 进程池 线程池 连接池 对象池 

*/
template<typename T>

int main()
{
	return 0;
}
/*
new和delete
1.malloc和new的区别
a.malloc是按字节开辟内存的；new开辟内存时需要制定类型	new int[10]
	所以malloc开辟内存返回的都是void*  operator new -> int*
b.malloc只负责开辟空间，new不仅仅有malloc的功能，可以进行数据的初始化
	new int(20);	new int[20]();	int()
c.malloc开辟内存失败返回nullptr指针；new抛出的是bad_alloc类型的异常。
2.free和delete的区别
delete (int*)p:调用析构函数; 在free（p）

new -> operator new
delete -> operator delete

new和delete能混用吗？ C++为什么区分单个元素和数组的内存分配和释放呢？
new delete
new[] delete[]
对于普通的编译器内置类型  new/delete[]   new[]/delete

自定义的类类型，有析构函数，为了调用正确的析构函数，那么开辟对象数组的时候，
会多开辟4个字节，记录对象的个数。
*/
//先调用operator new开辟内存空间、然后调用对象的构造函数（初始化）

#if 0
void* operator new(size_t size)
{
	void* p = malloc(size);
	if (p == nullptr)
		throw bad_alloc();
	cout << "operator new addr:" << p << endl;
	return p;
}
//delete p； 调用p指向对象的析构函数、再调用operator delete释放内存空间
void operator delete(void* ptr)
{
	cout << "operator delete addr:" << ptr << endl;
	free(ptr);
}
int main()
{
	int* p = new int;
	delete p;

	return 0;
}
#endif

/*
迭代器的失效问题？
1、迭代器为什么会失效？
a:当容器调用erase方法后，当前位置到容器末尾元素的所有迭代器全部失效了
b:调用insert方法后，当前位置到容器末尾元素的所有迭代器全部失效了
	迭代器依然有效	迭代器全部失效					
首元素  ->  插入点/删除点  ->  末尾元素

c:insert来说，如果引起容器内存扩容
	原来容器的所有迭代器就全部失效了
首元素  ->  插入点/删除点  ->  末尾元素

d:不同容器的迭代器是不能进行比较运算的	

2、迭代器失效了以后，问题该怎么解决？
对插入/删除点的迭代器进行更新操作
*/


//迭代器一般实现成容器的嵌套类型

#if 0
//string类型
//自己实现一个字符串对象
class String
{
public:
	String(const char* p = nullptr)
	{
		if (p != nullptr)
		{
			_pstr = new char[strlen(p) + 1];
			strcpy(_pstr, p);
		}
		else
		{
			_pstr = new char[1];
			*_pstr = '\0';
		}
	}
	~String()
	{
		delete[]_pstr;
		_pstr = nullptr;
	}
	String(const String& str)
	{
		_pstr = new char[strlen(str._pstr) + 1];
		strcpy(_pstr, str._pstr);
	}
	String& operator=(const String& str)
	{
		if (this == &str)
			return *this;

		delete[]_pstr;

		_pstr = new char[strlen(str._pstr) + 1];
		strcpy(_pstr, str._pstr);

		return *this;
	}
	bool operator>(const String& str)const
	{
		return strcmp(_pstr, str._pstr) > 0;
	}
	bool operator<(const String& str)const
	{
		return strcmp(_pstr, str._pstr) < 0;
	}
	bool operator=(const String& str)const
	{
		return strcmp(_pstr, str._pstr) == 0;
	}
	int length()
	{
		return strlen(_pstr);
	}
	const char* c_str()const
	{
		return _pstr;
	}
	char& operator[](int index)
	{
		return _pstr[index];
	}
	const char& operator[](int index)const
	{
		return _pstr[index];
	}

	//给String字符串类型提供迭代器的实现
	class iterator
	{
	public:
		iterator(char *p=nullptr):_p(p){ }
		bool operator!=(const iterator& it)
		{
			return _p != it._p;
		}
		void operator++()
		{
			++_p;
		}
		char& operator*()
		{
			return *_p;
		}
	private:
		char* _p;
	};
	//begin返回的是容器底层首元素的迭代器的表示
	iterator begin()
	{
		return iterator(_pstr);
	}
	//end返回的是容器末尾元素后继位置的迭代器的表示
	iterator end()
	{
		return iterator(_pstr + length());
	}
private:
	char* _pstr;

	friend ostream& operator<<(ostream& out, const String& str);
	friend String operator+(const String& lhs, const String& rhs);
};
String operator+(const String& lhs, const String& rhs)
{
	//char* ptmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
	String tmp;
	tmp._pstr= new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
	strcpy(tmp._pstr, lhs._pstr);
	strcat(tmp._pstr, rhs._pstr);
	//String tmp(tmp);
	//delete[]ptmp;
	return tmp;
	//return String(ptmp);
}
ostream& operator<<(ostream& out, const String& str)
{
	out << str._pstr;
	return out;
}
//迭代器可以透明的访问容器内部的元素的值
int main()
{
	//迭代器的功能：提供一种统一的方式，来透明的遍历容器
	String str1 = "hello world";
	//容器的迭代器类型
	String::iterator it = str1.begin();
	for (; it != str1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	//C++11  foreach的方式来遍历容器的内部元素的值=>底层还是通过迭代器进行遍历
	for (char ch : str1)
	{
		cout << ch << " ";
	}
	cout << endl;
}

#endif

#if 0
int main()
{
	string str1;
	string str2 = "aaa";	//string(const char*)
	string str3 = "bbb";
	string str4 = str2 + str3;
	string str5 = str2 + "ccc";
	string str6 = "ddd" + str2;

	cout << "str6:" << str6 << endl;
	if (str5 > str6)
	{
		cout << str5 << ">" << str6 << endl;
	}
	else
	{
		cout << str5 << "<" << str6 << endl;
	}
		
	int len = str6.length();
	for (int i = 0; i < len; ++i)
	{
	//  char & str6.operator[](i)
		cout << str6[i] << " ";
	}
	cout << endl;

	//string -> char*
	char buf[1024] = { 0 };
	strcpy(buf, str6.c_str());	//字符串.c_str() 可以将c_str()管理的字符串返回成const char*类型
	cout << "buf:" << buf << endl;

	return 0;
}
#endif

/*
C++ 运算符重载：使对象的运算表现的和编译器内置类型一样
template<typename T>
T sum(T a,T b)
{
	return a+b;		//a调用自己的加法函数把b当作实参传递进去 a.operator+(b)
}

cout  ::operator<<(cout,comp1)	void<<endl;
ostream &operator<<(ostream &out,const CComplex &src)
*/


#if 0
//复数类
class CComplex
{
public:
	CComplex(int r = 0, int i = 0)
		:mreal(r),mimage(i){ }
	CComplex operator+(const CComplex& src)
	{
		//CComplex comp;
		//comp.mreal = this->mreal + src.mreal;
		//comp.mreal = this->mimage + src.mimage;
		//return comp;
		return CComplex(this->mreal + src.mreal
			, this->mimage + src.mimage);
	}
	void show()
	{
		cout << "real:" << mreal << "image:" << mimage << endl;
	}
	CComplex operator++(int)
	{
		/*CComplex comp = *this;
		mreal += 1;
		mimage += 1;
		return comp;*/
		return CComplex(mreal++, mimage++);
	}
	CComplex& operator++()
	{
		mreal += 1;
		mimage += 1;
		return *this;	//出函数后，this还是存在的，因此要给CComplex加引用
	}
private:
	int mreal;	//实部
	int mimage;	//虚部

	friend CComplex operator+(const CComplex& lhs, const CComplex& rhs);	//友元函数
	friend ostream& operator<<(ostream& out, const CComplex& src);
	friend istream& operator>>(istream& in, CComplex& src);
};
CComplex operator+(const CComplex& lhs, const CComplex& rhs)
{
	return CComplex(lhs.mreal + rhs.mreal, lhs.mimage + rhs.mimage);
}
ostream& operator<<(ostream& out, const CComplex& src)	//输出运算符的重载
{
	out << "mreal:" << src.mreal << "mimage:" << src.mimage << endl;
}
istream& operator>>(istream& in, CComplex& src)
{
	in >> src.mreal >> src.mimage;
	return in;
}
int main()
{
	CComplex comp1(10, 10);
	CComplex comp2(20, 20);
	//comp1.operator+(comp2)	加法运算符的重载函数
	CComplex comp3 = comp1 + comp2;
	comp3.show();

	CComplex comp4 = comp1 + 20;	//comp1.operator+(20)	int->CComplex  CComplex(int)
	comp4.show();
	//编译器做对象运算的时候，会调用对象的运算符重载函数(优先调用成员方法);如果没有成员方法,
	//就在全局作用域找合适的运算符重载函数
	//					::operator+(30,comp1);
	CComplex comp5 = 30 + comp1;
	comp5.show();

	//前置++  先++，再赋值	++、--是单目运算符 operator++()	operator++(int)	括号内没参数，就是前置++;带一个整形参数就是后置++
	//CComplex operator++(int)
	comp5 = comp1++;
	comp1.show();
	comp5.show();
	//后置++  先赋值，再++
	//CComplex operator++()
	comp5 = ++comp1;
	comp1.show();
	comp5.show();
	
	cout << comp1 << endl;
	cin >> comp1 >> endl;
	

	return 0;
}
#endif