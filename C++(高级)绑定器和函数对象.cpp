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
�����ͺ�������
����������Ƕ���ӵ��operator()С������������غ���

1.C++ STL�еİ���
bind1st : operator()�ĵ�һ���βα����󶨳�һ��ȷ����ֵ
bind2nd : operator()�ĵڶ����βα����󶨳�һ��ȷ����ֵ

2.C++11��Boost����������bind������function�����������

3.lambda���ʽ  �ײ�����������������ʵ�ֻ���

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

	//greater ��Ԫ��������
	sort(vec.begin(), vec.end(), greater<int>());	//��С����
	ShowContainer(vec);


	/*
	��70��˳����뵽vec������  �ҵ�һ��С��70������
	С�������������ֻ��Ҫ����һ������ operator()(const T &val)
	greator  a > b
	less	 a < b
	���� + ��Ԫ�������� = һԪ��������
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
C++11�ṩ�İ����ͺ�������
			bind	function
			C++ STL	bind1st��bind2nd => ������һ����������
function : ��������������lambda���ʽ ����ֻ��ʹ����һ�������
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
	//��������һ������void(Test::*pfunc)(string)
	void hello(string str) { cout << str << endl; }
};
int main()
{
	/*
	1.�ú�������ʵ����function
	2.ͨ��function����operator()������ʱ����Ҫ���ݺ������ʹ�����Ӧ�Ĳ���
	*/
	//��function����ģ�嶨�崦������ϣ����һ����������ʵ����function
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
C++11  bind���� => ���صĽ������һ����������
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
	//bind�Ǻ���ģ��  �����Զ�����ģ�����Ͳ���
	bind(hello, "hello bind!")();
	cout << bind(sum, 10, 20)() << endl;
	cout << bind(&Test::sum, Test(), 20, 30)() << endl;

	//����ռλ��  ����������䣬�޷�����ʹ��
	bind(hello, _1)("hello bind 2!");
	cout << bind(sum, _1, _2)(200, 300) << endl;

	//�˴���bind���صİ���binder�͸���������
	function<void(string)> func1 = bind(hello, _1);
	func1("hello China!");
	return 0;
}
#endif

/*
C++11 ��������������� => lambda���ʽ
���������ȱ��:
ʹ�÷����㷨��������	�Ƚ�����/�Զ������		���ȼ�����	����ָ��

lambda���ʽ���﷨:
[�����ⲿ����](�β��б�)->����ֵ{��������};
�β��б����С������������غ������β��б�
����ֵ��С������������غ����ķ���ֵ

���lambda���ʽ�ķ���ֵ����Ҫ����ô"->����ֵ"����ʡ�Ե�

[�����ⲿ����]
[]:��ʾ�������κ��ⲿ����cz
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
��Ȼlambda���ʽֻ��ʹ������䵱�У����������ʹ��֮ǰ����õ�lambda���ʽ����ô�죿
��ʲô��������ʾlambda���ʽ?

lambda���ʽ => ��������

*/

