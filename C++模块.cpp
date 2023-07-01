#include<iostream>
using namespace std;

/*
类模板 => 实现一个C++ STL里面的一个顺序容器 vector向量容器
SeqStack
Queue
容器：
空间配置器allocator 做4件事情  内存开辟/内存释放  对象构造/对象析构
*/
#if 0
//定义容器的空间配置器，和C++标准库的allocator实现一样
template<typename T>
struct Allocator
{
	T* allocate(size_t size)	//负责内存开辟
	{
		return (T*)malloc(sizeof(T) * size);
	}
	void deallocate(void* p)	//负责内存释放
	{
		free(p);
	}
	void construct(T* p, const T& val)	//负责对象构造
	{
		new (p) T(val);	//定位new
	}
	void destory(T* p)	//负责对象析构
	{
		p->~T();	//~T代表了T类型的析构函数
	}
};
/*
容器底层内存开辟，内存释放，对象构造和析构，都通过allocator空间配置器来实现
*/
template<typename T, typename Alloc = Allocator<T>>
class vector
{
public:
	vector(int size = 10)
	{
		//需要把内存开辟和对象构造分开处理
		//_first = new T[size];
		_first = _allocator.allocate(size);
		_last = _first;
		_end = _first + size;
	}
	~vector()
	{
		//析构容器有效的元素，然后释放_first指针指向的堆内存
		//elete[]_first;
		for (T* p = _first; p != _last; ++p)
		{
			_allocator.destory(p);	//把_first指针指向的数组的有效元素进行析构操作
		}
		_allocator.deallocate(_first);	//释放堆上的数组内存
		_first = _last = _end = nullptr;
	}
	vector(const vector<T>& rhs)
	{
		int size = rhs._end - rhs._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);
		int len = rhs._last - rhs._first;
		for (int i = 0; i < len; ++i)
		{
			//_first[i] = rhs._first[i];
			_allocator.construct(_first + i, rhs._first[i]);
		}
		_last = _first + len;
		_end = _first + size;
	}
	vector<T>& operator=(const vector<T>& rhs)
	{
		//1、防止自赋值
		if (this == &rhs)
			return *this;

		//2、将原来的空间释放掉
		//delete[]_first;
		for (T* p = _first; p != _last; ++p)
		{
			_allocator.destory(p);	//把_first指针指向的数组的有效元素进行析构操作
		}
		_allocator.dellocate(_first);	//释放堆上的数组内存

		//3、和拷贝构造一样
		int size = rhs._end - rhs._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);
		int len = rhs._last - rhs._first;
		for (int i = 0; i < len; ++i)
		{
			//_first[i] = rhs._first[i];
			_allocator.construct(_first + i, rhs._first[i]);
		}
		_last = _first + len;
		_end = _first + size;
		return *this;
	}
	void push_back(const T& val)	//向容器末尾添加元素
	{
		if (full())
			expand();
		//*_last++ = val;	
		_allocator.construct(_last, val);	//_last指针指向的内存构造一个值为val的对象
		_last++;
	}
	void pop_back()	//从容器末尾删除元素
	{
		if (empty())
			return;
		//--_last;
		--_last;
		_allocator.destory(_last);	//不仅要把_last指针--，还需要析构删除的元素。
	}
	T top()const	//返回容器末尾的元素的值
	{
		return *(_last - 1);
	}
	bool full()const	//判满
	{
		return _last == _end;
	}
	bool empty()const	//判空
	{
		return _first == _last;
	}
	int size()const
	{
		return _last - _first;
	}
private:
	T* _first;	//指向数组起始的位置
	T* _last;	//指向数组中有效元素的后继位置
	T* _end;	//指向数组空间的后继位置
	Alloc _allocator;	//定义容器的空间配置器对象

	void expand()
	{
		int size = _end - _first;
		T* ptmp = _allocator.allocate(2 * size);
		for (int i = 0; i < size; ++i)
		{

			_allocator.construct(ptmp + i, _first[i]);
		}
		//	delete[]_first;
		for (T* p = _first; p != _last; ++p)
		{
			_allocator.destory(p);	//把_first指针指向的数组的有效元素进行析构操作
		}
		_allocator.deallocate(_first);
		_first = ptmp;
		_last = _first + size;
		_end = _first + 2 * size;
	}
};

class Test
{
public:
	Test()
	{
		cout << "Test()" << endl;
	}
	~Test()
	{
		cout << "~Test()" << endl;
	}
	Test(const Test&)
	{
		cout << "Test(const Test&)" << endl;
	}
};
int main()
{
	Test t1, t2, t3;
	cout << "----------------" << endl;
	vector<Test>vec;
	vec.push_back(t1);
	vec.push_back(t2);
	vec.push_back(t3);
	cout << "---------------" << endl;
	vec.pop_back();	//只需要析构对象。要把对象的析构和内存释放分离开
	cout << "---------------" << endl;

	return 0;
}

#endif
/*
函数模板
模板的非类型参数  必须是整数类型(整数或者地址/引用都可以)都是常量，只能使用，而不能修改

类模板 => 实例化 => 模板类
*/

#if 0
template<typename T>
class SeqStack	//模板名称 + 类型参数列表 = 类名称
{
public:
	//构造和析构函数名不用加<T>,其它出现模板的地方都加上参数列表
	SeqStack<T>(int size = 10)
		: _pstack(new T[size])
		, _top(0)
		, _size(size)	//成员变量的初始化一般都写在构造函数的初始化列表当中
	{}
	//析构函数
	~SeqStack<T>()
	{
		delete[]_pstack;
		_pstack = nullptr;
	}
	//拷贝构造函数
	SeqStack<T>(const SeqStack<T>& stack)
		: _top(stack._top)
		, _size(stack._size)
	{
		_pstack = new T[_size];
		//不要用memcopy进行拷贝
		for (int i = 0; i < _top; ++i)
		{
			_pstack[i] = stack._pstack[i];
		}
	}
	SeqStack<T>& operator=(const SeqStack<T>& stack)	//赋值运算符的重载函数
	{
		if (this == &stack)
			return nullptr;

		delete[]_pstack;

		_top = stack._top;
		_size = stack._size;
		_pstack = new T[_size];

		//不要用memcopy进行拷贝
		for (int i = 0; i < _top; ++i)
		{
			_pstack[i] = stack._pstack[i];
		}
		return *this;
	}

	void push(const T& val)	//入栈操作
	{
		if (full())
			expand();
		_pstack[_top++] = val;
	}
	void pop()	//出栈操作
	{
		if (empty())
			return;
		--_top;
	}
	T top()const	//返回栈顶元素
	{
		if (empty())
			throw "stack is empty!";	//抛出异常也代表函数逻辑结束
		return _pstack[_top - 1];
	}
	bool full()const	//栈满
	{
		return _top == _size;
	}
	bool empty()const	//栈空
	{
		return _top == 0;
	}
private:
	T* _pstack;
	int _top;
	int _size;

	//顺序栈底层数组按2倍的方式扩容
	void expand()
	{
		T* ptmp = new T[_size * 2];
		for (int i = 0; i < _top; ++i)
		{
			_pstack[i] = stack._pstack[i];
		}
		delete[]_pstack;
		_pstack = ptmp;
		_size *= 2;
	}
};
int main()
{
	SeqStack<int> s1;
	s1.push(20);

	return 0;
}
#endif

#if 0 
template<typename T,int SIZE>
void sort(T* arr)
{
	for (int i = 0; i < SIZE - 1; ++i)
	{
		for (int j = 0; j < SIZE - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

int main()
{
	int arr[] = { 12,5,63,1,7,5 };
	const int size = sizeof(arr) / sizeof(arr[0]);
	sort<int ,size>(arr);
	for (int val : arr)
	{
		cout << val << " ";
	}
	cout << endl;
	return 0;
}
#endif
/*
C++  函数模板
模板的意义：对类型也可以进行参数化
int sum(int a,int b){ return a+b; }

函数模板	<=	是不进行编译的，因为类型还不知道
模板的实例化	<=	函数调用点进行实例化
模板函数	<=	才是要被编译器所编译的

模板类型参数 typename/class
模板非类型参数

模板的实参推演 => 可以根据用户传入的实参类型，来推到模板类型参数的具体类型
模板的特例化(专用化) 特殊(不是编译器提供的，而是用户提供的)的实例化
模板函数、模板的特例化、非模板函数的重载关系

模板代码是不能在一个文件中定义，在另一个文件中使用
模板代码调用之前，一定要看到模板定义的地方，这样的话，模板才能够进行正常的实例化，产生能够被编译器编译的代码

所以，模板代码都是放在头文件当中的，然后在源文件当中直接进行#include包含
*/
#if 0
//函数模板
template<typename T>		//定义一个模板参数列表
bool compare(T a, T b)		//compare是一个函数模板
{
	cout << "template compare" << endl;
	return a > b;
}
/*
在函数调用点，编译器用户指定的类型，从原模版实例化一份函数代码出来
模板函数
bool compare<int>(int a, int b)
{
	return a>b;
}
bool compare<double>(int a, int b)
{
	return a>b;
}
bool compare<const char*>(const char* a, const char* b)
{
	return strcmp(a ,b) > 0;
}
*/

//模板的特例化
//针对compare函数模板，提供const char * 类型的特例化版本
template<>
bool compare<const char*>(const char* a, const char* b)
{
	cout << "compare<const char*>" << endl;
	return strcmp(a, b) > 0;
}

//非模板函数	-	普通函数
bool compare(const char* a, const char* b)
{
	cout << "normal compare" << endl;
	return strcmp(a, b) > 0;
}
int main()
{
	//函数的调用点
	compare<int>(10, 20);
	compare<double>(10.5, 20.5);

	//函数模板实参的推演
	compare(10, 30);

	//函数模板实参的推演 T const char*
	//对于某些类型来说，依赖编译器默认实例化的模板代码，代码处理逻辑是有错误的
	//编译器优先把compare处理成函数名字，没有的话，才去找compare模板
	compare("aaa", "bbb");
	return 0;
}
#endif
