#include<algorithm>
#include<iostream>
#include<stack>
#include<vector>
#include<string>
using namespace std;

int main2()
{
	vector<int>vec;
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100);
	}
	auto it = vec.begin();
	cout << *it << endl;
	/*int arr[] = { 12,5,68,1,6,8,1,5,79,984 };
	vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));

	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	//默认从小到大的排序
	sort(vec.begin(), vec.end());
	for (int v : vec)
	{
		cout << v << " ";
	}	
	cout << endl;*/

	return 0;

}

/*
move:移动语义,得到右值类型	move(左值)=>右值
forward:类型完美转发,能够识别左值和右值类型
*/
//左值引用 + 右值引用 = 左值引用
//右值引用 + 右值引用 = 右值引用
int main1()
{
	//C++11 标准新引入了另一种引用方式，称为右值引用，用 "&&" 表示。

	int a = 10;
	int& b = a;	//左值:有内存、有名字	右值:没名字(临时量)、没内存
	//int &&c = a;	//无法将左值绑定到右值引用

	/*
	int tmp = 20;
	const int &c = tmp;
	*/
	const int& c = 20;	//不能用左值引用绑定一个右值
	/*
	int tmp = 20;
	int &&d = tmp;
	*/
	int&& d = 20;	//可以把一个右值绑定到一个右值引用上
	//一个右值引用变量本身是一个左值,因此不能用右值引用来进行引用(需要左值引用来进行引用)	int &&f = d; NO!
	//常量数字、临时量都是右值,需要进行右值引用
	int& f = d;

	return 0;
}



#if 0
class Test
{
public:
	Test(int data = 10) :ma(data) { cout << "Test()" << endl; }
	~Test() { cout << "~Test()" << endl; }
	Test(const Test& t) :ma(t.ma) { cout << "Test(const Test&)" << endl; }
	Test& operator=(const Test& t)
	{
		cout << "operator=" << endl;
		ma = t.ma;
		return *this;
	}
	int getData()const { return ma; }
private:
	int ma;
};
/*
1.函数参数传递过程中,对象优先按引用传递,不要按值传递
2.函数返回对象的时候,应该优先返回一个临时对象,而不要返回一个定义过的对象
3.接收返回值是对象的函数调用的时候,优先按初始化的方式接收,不要按赋值的方式接收

*/
Test GetObject(Test t)	//不能返回局部的或者临时对象的指针或引用
{
	int val = t.getData();
	//Test tmp(val);
	//return tmp;
	return Test(val);
}
int main()
{
	Test t1;
	Test t2 = GetObject(t1);
	//t2 = GetObject(t1);
	//函数调用，从实参传递给形参是初始化的过程
	
	return 0;
}



class Test
{
public:
	Test(int a = 10) :ma(a) { cout << "Test()" << endl; }
	~Test() { cout << "~Test()" << endl; }
	Test(const Test& t) :ma(t.ma) { cout << "Test(consy Test&)" << endl; }
	Test& operator=(const Test& t)
	{
		cout << "operator=" << endl;
		ma = t.ma;
		return *this;
	}
private:
	int ma;
};

int main()
{

	Test t1;
	Test t2(t1);
	Test t3 = t1;
	//Test(20) 显示生成临时对象  生存周期:所在的语句
	//C++编译器对于对象构造的优化:用临时对象生成的新对象的时候,临时对象就不产生了,直接构造新对象就可以了
	Test t4 = Test(20);		//Test t4(20);没有区别
	cout << "---------------------" << endl;
	t4 = t2;
	//显式生成临时对象
	t4 = Test(30);	//先调用构造函数生成临时对象，再用临时对象给t4赋值(调用一次等号运算符重载函数),出语句后调用析构函数
	t4 = (Test)30;	// int->Test(int)	调用带整形的构造函数生成临时对象,再调用赋值函数给t4赋值,出语句后调用析构函数

	//隐式生成临时对象  调用带整形的构造函数生成临时对象,再调用赋值函数给t4赋值,出语句后调用析构函数
	t4 = 30;  //int->Test(int)	char*->Test(char*) 

	cout << "---------------------" << endl;
	
	Test* p = &Test(40);	//用指针指向临时对象,出语句之后就要对其进行析构
	//p指向的是一个已经析构的临时对象
	const Test& ref = Test(50);

	cout << "---------------------" << endl;
	return 0;
}

#endif

/*
C++高级课程内容
一:对象的应用优化、右值引用的优化
二:只能指针
三:绑定器和函数对象、lambda表达式
四:C++11内容汇总、多线程应用实践
五:设计模式
*/