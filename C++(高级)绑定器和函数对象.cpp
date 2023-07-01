#include<iostream>
#include<functional>
#include<vector>
#include<algorithm>
#include<ctime>
#include<map>
#include<string>
using namespace std;
using namespace placeholders;


/* 
绑定器和函数对象
函数对象就是对象拥有operator()小括号运算符重载函数

1.C++ STL中的绑定器
bind1st : operator()的第一个形参变量绑定成一个确定的值
bind2nd : operator()的第二个形参变量绑定成一个确定的值

2.C++11从Boost库中引入了bind绑定器和function函数对象机制

3.lambda表达式  底层就是依赖函数对象的实现机制

*/

#if 0
template<typename Container>
void ShowContainer(Container& con)
{
	typename Container::iterator it = con.begin();
	for (; it != con.end(); ++it)
	{
		cout << *it <<" ";
	}
	cout << endl;
}
int main()
{
	vector<int>vec;
	srand(time(nullptr));
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}

	ShowContainer(vec);
	sort(vec.begin(), vec.end());
	ShowContainer(vec);

	//greater 二元函数对象
	sort(vec.begin(), vec.end(), greater<int>());	//大到小排序
	ShowContainer(vec);


	/*
	把70按顺序插入到vec容器中  找第一个小于70的数字
	小括号运算符重载只需要接收一个参数 operator()(const T &val)
	greator  a > b
	less	 a < b
	绑定器 + 二元函数对象 = 一元函数对象
	bind1st + greater bool operator()(70,const _Ty& _Right)
	bind2nd + greater bool operator()(const _Ty& _Left,70)
	*/

	//auto it1 = find_if(vec.begin(), vec.end(), 
		//bind1st(greater<int>(),70));
	auto it1 = find_if(vec.begin(), vec.end(),
		bind2nd(less<int>(), 70 ));
	if (it1 != vec.end())
	{
		vec.insert(it1, 70);
	}
	ShowContainer(vec);

	return 0;
}
#endif

/*
C++11提供的绑定器和函数对象
			bind	function
			C++ STL	bind1st和bind2nd => 本身还是一个函数对象
function : 绑定器，函数对象，lambda表达式 它们只能使用在一条语句中
*/

#if 0
void hello1()
{
	cout << "hello world" << endl;
}
void hello2(string str)
{
	cout << str << endl;
}
int sum(int a, int b)
{
	return a + b;
}
class Test
{
public:
	//必须依赖一个对象void(Test::*pfunc)(string)
	void hello(string str) { cout << str << endl; }
};
int main()
{
	/*
	1.用函数类型实例化function
	2.通过function调用operator()函数的时候，需要根据函数类型传入相应的参数
	*/
	//从function的类模板定义处，看到希望用一个函数类型实例化function
	function<void()> func1 = hello1;
	func1();	//func1.operator() => hello1()

	function<void(string)>func2 = hello2;
	func2("hello hello2");	//func2.operator()(string str)=> hello2(str)

	function<int(int, int)>func3 = sum;
	cout << func3(20, 30) << endl;

	function<int(int, int)> func4 = [](int a, int b)->int {return a + b; };
	cout << func4(100, 200) << endl;

	function<void(Test*, string)>func5 = &Test::hello;
//	func5(&Test(), "call Test::hello!");
	return 0;
}

#endif


/*
C++11  bind绑定器 => 返回的结果还是一个函数对象
*/

#if 0
void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }
class Test
{
public:
	int sum(int a, int b) { return a + b; }
};
int main()
{
	//bind是函数模板  可以自动推演模板类型参数
	bind(hello, "hello bind!")();
	cout << bind(sum, 10, 20)() << endl;
	cout << bind(&Test::sum, Test(), 20, 30)() << endl;

	//参数占位符  绑定器出了语句，无法继续使用
	bind(hello, _1)("hello bind 2!");
	cout << bind(sum, _1, _2)(200, 300) << endl;

	//此处把bind返回的绑定器binder就复用起来了
	function<void(string)> func1 = bind(hello, _1);
	func1("hello China!");
	return 0;
}
#endif

/*
C++11 函数对象的升级版 => lambda表达式
函数对象的缺点:
使用泛型算法参数传递	比较性质/自定义操作		优先级队列	智能指针

lambda表达式的语法:
[捕获外部变量](形参列表)->返回值{操作代码};
形参列表就是小括号运算符重载函数的形参列表
返回值是小括号运算符重载函数的返回值

如果lambda表达式的返回值不需要，那么"->返回值"可以省略的

[捕获外部变量]
[]:表示不捕获任何外部变量cz
*/

#if 0
template<typename T=void>
class TestLambda01
{
public:
	TestLambda01()
	{

	}
	void operator()()
	{
		cout << "hello world!" << endl;
	}
};
template<typename T = int>
class TestLambda02
{
public:
	TestLambda02()
	{

	}
	int operator()(int a,int b)
	{
		return a + b;
	}
};
int main()
{
	auto func1 = []()->void {cout << "hello world" << endl; };
	func1();

	auto func2 = [](int a, int b)->int {return a + b;  };
	cout << func2(20, 30) << endl;

	TestLambda01<>t1;
	t1();

	TestLambda02<>t2;
	cout << t2(20, 30) << endl;
	return 0;
}

#endif
/*
既然lambda表达式只能使用在语句当中，如果想跨语句使用之前定义好的lambda表达式，怎么办？
用什么类型来表示lambda表达式?

lambda表达式 => 函数对象

*/

