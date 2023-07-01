#include<iostream>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

/*
ָ�����Ա(��Ա�����ͳ�Ա����)��ָ��
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
��ĸ��ֳ�Ա  - ��Ա����/����
��ͨ��Ա���� => �����������һ��this�βα���
1���������������
2�����ø÷���ʱ��need����һ������(���������޷����õ� ʵ��:const CGoods*  �β�: CGoods *this)
3������������ʶ����˽�г�Ա����   ��protect�̳У�  Ŀǰֻ���ǹ��к�˽�� 

static��̬��Ա���� => ��������this�βα���
1���������������
2�������������������÷���
3������������ʶ����˽�г�Ա�������ڲ���������ĳ�Ա(ֻ�ܵ���������static��̬��Ա)
 


��ͨ�����;�̬����������
��ͨ�������ö��������ã���̬��������������������
��ͨ������������thisָ�룬���յ�ǰ����ĵ�ַ�͵�ʹ�ö��������ã��ѵ�ַ����ʵ�δ��ݽ���
��̬�������벻�����thisָ�룬��need����һ������ĵ�ַ

�������������������ʵ������ж��������Ϣ������ý��������д�ɾ�̬�ķ�����

const����Ա����  =>  const CGoods *this
1���������������
2����������һ��������ͨ������߳����󶼿���
3������������ʶ����˽�г�Ա������ֻ�ܶ�����д
*/

#if 0
class CDate
{
public:
	CDate(int a, int b, int c)	//�Զ���һ�����캯�����������Ͳ����ٲ���Ĭ�ϵĹ�����
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
		:_date(y, m, d)	//#1 ���캯���ĳ�ʼ���б� 
		, _amount(a)	//int _amount = a;
		,_price(p)
	{
		//#2 ��ǰ�����͹��캯����
		strcpy(_name, n);
		//_amount = a;	//int _amount;_amount = a; 
		_count++;	//��¼���в������¶��������
	}
	//��ͨ�ĳ�Ա����
	void show()		//��ӡ��Ʒ��˽�е���Ϣ	CGood *this
	{
		cout << "name:" << _name << endl;
		cout << "amount:" << _amount << endl;
		cout << "price:" << _price << endl;
		_date.show();
	}
	//����Ա����	ֻҪ��ֻ�������ĳ�Ա������һ��ʵ�ֳ�const����Ա����
	void show()const		// const CGood *this
	{
		cout << "name:" << _name << endl;
		cout << "amount:" << _amount << endl;
		cout << "price:" << _price << endl;
		_date.show();
	}
	//��̬�ĳ�Ա���� û��thisָ���
	static void showCGoodsCount()
	{
		cout << "������Ʒ�����������:" << _count << endl;
	}
private:
	char* _name;
	int _amount;
	double _price;
	CDate _date;	//��Ա����	1.�����ڴ�	2.���ù��캯��
	//��̬��Ա����  �����ڶ��󣬶������༶���	
    static int _count;	//���� ������¼��Ʒ�����������
}; 
//static��Ա����һ��Ҫ��������ж��岢�ҳ�ʼ��
int CGoods::_count = 0;
int main()
{
	CGoods good1("��Ʒ", 100, 35.0, 2019, 5, 12);
	good1.show();

	CGoods good2("��Ʒ", 100, 35.0, 2019, 5, 12);
	good2.show();

	CGoods good3("��Ʒ", 100, 35.0, 2019, 5, 12);
	good3.show();
	CGoods good4("��Ʒ", 100, 35.0, 2019, 5, 12);
	good4.show();

	//ͳ��������Ʒ��������
	//��̬�����������������������
	CGoods::showCGoodsCount();

	const CGoods good5("����Ʒ", 100, 35.0, 2019, 01, 8);
	good5.show();	//CGoods::show(&good5)	const CGoods* -> const CGoods *this
	return 0;
}

#endif

/*
���캯���ĳ�ʼ���б�����ָ����ǰ�����Ա�����ĳ�ʼ����ʽ
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
	//��Ա�����ĳ�ʼ�������Ƕ����˳���йأ��͹��캯����ʼ���б��г��ֵ��Ⱥ�˳���޹�!
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
//������
class CDate
{
public:
	CDate(int a, int b, int c)	//�Զ���һ�����캯�����������Ͳ����ٲ���Ĭ�ϵĹ�����
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
		:_date(y,m,d)	//#1 ���캯���ĳ�ʼ���б� 
		, _amount(a)	//int _amount = a;
	{
		//#2 ��ǰ�����͹��캯����
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
	CDate _date;	//��Ա����	1.�����ڴ�	2.���ù��캯��
};
int main()
{
	CGoods goood("��Ʒ", 100, 35.0, 2019, 5, 12);
	return 0;
}
#endif

/*
ǳ����Ҫ�Զ��忽�����캯���͸�ֵ���غ���
String����
ѭ������ Queue
*/

//��д��String�Ĺ��캯�������������͸�ֵ����

#if 0
class String
{
public:
	String(const char *str = nullptr)	//��ͨ���캯��
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
	String(const String& other)		//�������캯��
	{
		m_data = new char[strlen(other.m_data) + 1];
		strcpy_s(m_data, other.m_data);
	}
	~String(void)						//��������
	{
		delete[]m_data;
		m_data = nullptr;
	}
	//String& ��Ϊ��֧��������operator=��ֵ����
	String& operator = (const String & other)//��ֵ����
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
	char *m_data;		//���ڱ����ַ���

};


int main()
{
	//���ô�const char*�����Ĺ��캯��
	String str1;
	String str2("hello");
	String str3;

	//���ÿ������캯��
	String str4 = str3;
	String str5(str3);

	//���ø�ֵ���غ���
	str1 = str2;

	return 0;
}
#endif
/*
thisָ�룺һ��������ĺܶ����ÿһ���������Լ���һ�׳�Ա������������һ�����͵Ķ�����һ�׳�Ա������ �������������ж���
��Ա�����������Ĳ����������һ��thisָ��


���캯����
	�������ʱ���Զ����ã��������أ�������ɣ����������
����������
	�����������������أ�ֻ��һ��������������������ˣ�����Ͳ�������
.data(���ݶ�)�Ķ������ڳ��������ǹ��죬������������
heap(�Ѷ�)�Ķ�������new��ʱ����й��죬delete��ʱ������
stack(ջ��)�Ķ���  ���뺯����������ĵط�ȥ���죬���˺������������������Ҫ����
		
�����ǳ���������
����Ĭ�ϵĿ������������ڴ�����ݿ���
�ؼ��Ƕ������ռ���ⲿ��Դ,��ôǳ�����ͳ���������
*/

#if 0
class SeqStack
{
public:
	//���캯����������Դ
	SeqStack(int size = 10)
	{
		cout << this << " SeqStack()" << endl;
		_pstack = new int[size];
		_top = -1;
		_size = size;
	}
	//�Զ��忽�����캯��	��=		�����ǳ����������������
	SeqStack(const SeqStack& src)
	{
		cout << "SeqStack(const Se
			qStack& src)" << endl;
		_pstack = new int[src._size];
		for (int i = 0; i <= src._top; ++i)
		{
			_pstack[i] = src._pstack[i];
		}//���
		_top = src._top;
		_size = src._size;
	}
	//�����������ͷ���Դ
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
	int* _pstack;		//��̬�������飬�洢˳��ջ��Ԫ��
	int _top;		//ָ��ջ��Ԫ�ص�λ��
	int _size;		//�������ݵĴ�С

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
	SeqStack s;	//û���ṩ�κι��캯����ʱ�򣬻�Ϊ������Ĭ�Ϲ����Ĭ���������ǿպ���
	SeqStack s1(10);
	//#1��#2һģһ��
	SeqStack s2 = s1;	//#1	Ĭ�Ͽ������캯��-> ��ֱ���ڴ����ݿ���
	//SeqStack s3(s1);	//#2
	return 0;
}
#endif

/*
���캯������������  OOP��̸�ϰ
���������ֺ�����һ����û�з���ֵ

���������в��õ��ù��캯���������������ڿ��ٺ�����ʱ���Զ����ù��캯�������������ʱ�򣬿����Զ�������������(�����Զ�����)

�ȹ���ĺ������������������(˳���෴)

ȫ�ֺ;ֲ������Զ����й��������
���϶���ģ��ܹ��Զ����죬���ǲ����Զ������������ֶ�delete
*/
#if 0
//OOPʵ��һ��˳��ջ
class SeqStack 
{
public:
	//���캯����������Դ
	//���Դ���������˿����ṩ������캯�����������캯��������
	//���أ���������ͬ�������б�ͬ��һ�麯�����Ϳ��Թ������ز�����
	SeqStack(int size = 10)
	{ 
		cout << this << " SeqStack()" << endl;
		_pstack = new int[size];
		_top = -1;
		_size = size;
	}
	//�����������ͷ���Դ
	~SeqStack()		//�ǲ��������ģ�������������ֻ����һ��
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
	int* _pstack;		//��̬�������飬�洢˳��ջ��Ԫ��
	int _top;		//ָ��ջ��Ԫ�ص�λ��
	int _size;		//�������ݵĴ�С

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
	delete ps;	//�ȵ���ps->~SeqStack()+Ȼ��free(ps)   delete��free������

	//1.���ٺ���  2.���ù��캯�� 
	SeqStack s;
	//s.init(5);	//�����Ա�����ĳ�ʼ������

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

	s1.~SeqStack();		//�������������Ժ�����˵���󲻴�����

	s1.push();	//���ڴ�ķǷ�����
	//s.release();	//�ͷŶ����Ա����ռ�õ��ⲿ���ڴ�(�ⲿ��Դ)
	return 0;	//
}

#endif
/*
C++ OOP�������		OOP��̣�thisָ��
C�����ָ����ĺ����Ķ���  Struct
C++����		=>  ʵ��ĳ�������
ʵ�壨���ԡ���Ϊ��		->		ADT(abstract data type)(������������)
	  |									|
	����				<-��ʵ�������ࣨ���ԣ���Ա���� ��Ϊ����Ա������


OOP���Ե��Ĵ�������ʲô��
����	��װ/����	�̳�	��̬

��  ->  ��Ʒʵ��
������ͨ�������޶������ֳ�����public���е� private˽�е� protected������

����һ��д��˽�е�   ����һ��д�ɹ��е�
*/

#if 0
const int NAME_LEN = 20;
class CGoods		// =>��Ʒ�ĳ�����������   ������Ͳ�ռ�ռ�
{
public:	//���ⲿ�ṩ���еĳ�Ա������������˽�е�����
	//����Ʒ���ݳ�ʼ���õ�
	void init(const char* name, double price, int amount);
	//��ӡ��Ʒ��Ϣ
	void show();
	//����Ա�����ṩһ��getxxx��setxxx�ķ��� ������ʵ�ֵķ������Զ������inline����
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
private:	//����һ�㶼��˽�еĳ�Ա����
	char _name[NAME_LEN];   //����
	double _price;			//����
	int _amount;			//����
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
	CGoods���Զ��������Ķ���ÿһ���������Լ��ĳ�Ա�������������ǹ���һ�׳�Ա����

	show() => ��ô֪�������ĸ��������Ϣ��
	init(name,price,amount) => ��ô֪������Ϣ��ʼ������һ��������أ�

	��ĳ�Ա����һ�����룬���еķ��������������һ��thisָ�룬���ܵ��ø÷����Ķ���ĵ�ַ
	*/
	//cl 02c++�������.cpp /dlreportSingleClassLayoutCGoods		����ָ��鿴�ڴ��С
	//��������ڴ��С��ʱ��     �����ڴ��С => ��Ա�����й�
	CGoods good;	//��ʵ������һ������

	good.init("���",10.0,20);
	good.show();
	good.setPrice(20.5);
	good.setAmount(100);
	good.show();

	return 0;
}

#endif