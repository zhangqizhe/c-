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

	//Ĭ�ϴ�С���������
	sort(vec.begin(), vec.end());
	for (int v : vec)
	{
		cout << v << " ";
	}	
	cout << endl;*/

	return 0;

}

/*
move:�ƶ�����,�õ���ֵ����	move(��ֵ)=>��ֵ
forward:��������ת��,�ܹ�ʶ����ֵ����ֵ����
*/
//��ֵ���� + ��ֵ���� = ��ֵ����
//��ֵ���� + ��ֵ���� = ��ֵ����
int main1()
{
	//C++11 ��׼����������һ�����÷�ʽ����Ϊ��ֵ���ã��� "&&" ��ʾ��

	int a = 10;
	int& b = a;	//��ֵ:���ڴ桢������	��ֵ:û����(��ʱ��)��û�ڴ�
	//int &&c = a;	//�޷�����ֵ�󶨵���ֵ����

	/*
	int tmp = 20;
	const int &c = tmp;
	*/
	const int& c = 20;	//��������ֵ���ð�һ����ֵ
	/*
	int tmp = 20;
	int &&d = tmp;
	*/
	int&& d = 20;	//���԰�һ����ֵ�󶨵�һ����ֵ������
	//һ����ֵ���ñ���������һ����ֵ,��˲�������ֵ��������������(��Ҫ��ֵ��������������)	int &&f = d; NO!
	//�������֡���ʱ��������ֵ,��Ҫ������ֵ����
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
1.�����������ݹ�����,�������Ȱ����ô���,��Ҫ��ֵ����
2.�������ض����ʱ��,Ӧ�����ȷ���һ����ʱ����,����Ҫ����һ��������Ķ���
3.���շ���ֵ�Ƕ���ĺ������õ�ʱ��,���Ȱ���ʼ���ķ�ʽ����,��Ҫ����ֵ�ķ�ʽ����

*/
Test GetObject(Test t)	//���ܷ��ؾֲ��Ļ�����ʱ�����ָ�������
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
	//�������ã���ʵ�δ��ݸ��β��ǳ�ʼ���Ĺ���
	
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
	//Test(20) ��ʾ������ʱ����  ��������:���ڵ����
	//C++���������ڶ�������Ż�:����ʱ�������ɵ��¶����ʱ��,��ʱ����Ͳ�������,ֱ�ӹ����¶���Ϳ�����
	Test t4 = Test(20);		//Test t4(20);û������
	cout << "---------------------" << endl;
	t4 = t2;
	//��ʽ������ʱ����
	t4 = Test(30);	//�ȵ��ù��캯��������ʱ����������ʱ�����t4��ֵ(����һ�εȺ���������غ���),�����������������
	t4 = (Test)30;	// int->Test(int)	���ô����εĹ��캯��������ʱ����,�ٵ��ø�ֵ������t4��ֵ,�����������������

	//��ʽ������ʱ����  ���ô����εĹ��캯��������ʱ����,�ٵ��ø�ֵ������t4��ֵ,�����������������
	t4 = 30;  //int->Test(int)	char*->Test(char*) 

	cout << "---------------------" << endl;
	
	Test* p = &Test(40);	//��ָ��ָ����ʱ����,�����֮���Ҫ�����������
	//pָ�����һ���Ѿ���������ʱ����
	const Test& ref = Test(50);

	cout << "---------------------" << endl;
	return 0;
}

#endif

/*
C++�߼��γ�����
һ:�����Ӧ���Ż�����ֵ���õ��Ż�
��:ֻ��ָ��
��:�����ͺ�������lambda���ʽ
��:C++11���ݻ��ܡ����߳�Ӧ��ʵ��
��:���ģʽ
*/