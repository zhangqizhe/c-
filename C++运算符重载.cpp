#include<iostream>
#include<string>
using namespace std;

/*
����������أ���Ա������ȫ�ַ���
�ڴ�� ���̳� �̳߳� ���ӳ� ����� 

*/
template<typename T>

int main()
{
	return 0;
}
/*
new��delete
1.malloc��new������
a.malloc�ǰ��ֽڿ����ڴ�ģ�new�����ڴ�ʱ��Ҫ�ƶ�����	new int[10]
	����malloc�����ڴ淵�صĶ���void*  operator new -> int*
b.mallocֻ���𿪱ٿռ䣬new��������malloc�Ĺ��ܣ����Խ������ݵĳ�ʼ��
	new int(20);	new int[20]();	int()
c.malloc�����ڴ�ʧ�ܷ���nullptrָ�룻new�׳�����bad_alloc���͵��쳣��
2.free��delete������
delete (int*)p:������������; ��free��p��

new -> operator new
delete -> operator delete

new��delete�ܻ����� C++Ϊʲô���ֵ���Ԫ�غ�������ڴ������ͷ��أ�
new delete
new[] delete[]
������ͨ�ı�������������  new/delete[]   new[]/delete

�Զ���������ͣ�������������Ϊ�˵�����ȷ��������������ô���ٶ��������ʱ��
��࿪��4���ֽڣ���¼����ĸ�����
*/
//�ȵ���operator new�����ڴ�ռ䡢Ȼ����ö���Ĺ��캯������ʼ����

#if 0
void* operator new(size_t size)
{
	void* p = malloc(size);
	if (p == nullptr)
		throw bad_alloc();
	cout << "operator new addr:" << p << endl;
	return p;
}
//delete p�� ����pָ�����������������ٵ���operator delete�ͷ��ڴ�ռ�
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
��������ʧЧ���⣿
1��������Ϊʲô��ʧЧ��
a:����������erase�����󣬵�ǰλ�õ�����ĩβԪ�ص����е�����ȫ��ʧЧ��
b:����insert�����󣬵�ǰλ�õ�����ĩβԪ�ص����е�����ȫ��ʧЧ��
	��������Ȼ��Ч	������ȫ��ʧЧ					
��Ԫ��  ->  �����/ɾ����  ->  ĩβԪ��

c:insert��˵��������������ڴ�����
	ԭ�����������е�������ȫ��ʧЧ��
��Ԫ��  ->  �����/ɾ����  ->  ĩβԪ��

d:��ͬ�����ĵ������ǲ��ܽ��бȽ������	

2��������ʧЧ���Ժ��������ô�����
�Բ���/ɾ����ĵ��������и��²���
*/


//������һ��ʵ�ֳ�������Ƕ������

#if 0
//string����
//�Լ�ʵ��һ���ַ�������
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

	//��String�ַ��������ṩ��������ʵ��
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
	//begin���ص��������ײ���Ԫ�صĵ������ı�ʾ
	iterator begin()
	{
		return iterator(_pstr);
	}
	//end���ص�������ĩβԪ�غ��λ�õĵ������ı�ʾ
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
//����������͸���ķ��������ڲ���Ԫ�ص�ֵ
int main()
{
	//�������Ĺ��ܣ��ṩһ��ͳһ�ķ�ʽ����͸���ı�������
	String str1 = "hello world";
	//�����ĵ���������
	String::iterator it = str1.begin();
	for (; it != str1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	//C++11  foreach�ķ�ʽ�������������ڲ�Ԫ�ص�ֵ=>�ײ㻹��ͨ�����������б���
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
	strcpy(buf, str6.c_str());	//�ַ���.c_str() ���Խ�c_str()������ַ������س�const char*����
	cout << "buf:" << buf << endl;

	return 0;
}
#endif

/*
C++ ��������أ�ʹ�����������ֵĺͱ�������������һ��
template<typename T>
T sum(T a,T b)
{
	return a+b;		//a�����Լ��ļӷ�������b����ʵ�δ��ݽ�ȥ a.operator+(b)
}

cout  ::operator<<(cout,comp1)	void<<endl;
ostream &operator<<(ostream &out,const CComplex &src)
*/


#if 0
//������
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
		return *this;	//��������this���Ǵ��ڵģ����Ҫ��CComplex������
	}
private:
	int mreal;	//ʵ��
	int mimage;	//�鲿

	friend CComplex operator+(const CComplex& lhs, const CComplex& rhs);	//��Ԫ����
	friend ostream& operator<<(ostream& out, const CComplex& src);
	friend istream& operator>>(istream& in, CComplex& src);
};
CComplex operator+(const CComplex& lhs, const CComplex& rhs)
{
	return CComplex(lhs.mreal + rhs.mreal, lhs.mimage + rhs.mimage);
}
ostream& operator<<(ostream& out, const CComplex& src)	//��������������
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
	//comp1.operator+(comp2)	�ӷ�����������غ���
	CComplex comp3 = comp1 + comp2;
	comp3.show();

	CComplex comp4 = comp1 + 20;	//comp1.operator+(20)	int->CComplex  CComplex(int)
	comp4.show();
	//�����������������ʱ�򣬻���ö������������غ���(���ȵ��ó�Ա����);���û�г�Ա����,
	//����ȫ���������Һ��ʵ���������غ���
	//					::operator+(30,comp1);
	CComplex comp5 = 30 + comp1;
	comp5.show();

	//ǰ��++  ��++���ٸ�ֵ	++��--�ǵ�Ŀ����� operator++()	operator++(int)	������û����������ǰ��++;��һ�����β������Ǻ���++
	//CComplex operator++(int)
	comp5 = comp1++;
	comp1.show();
	comp5.show();
	//����++  �ȸ�ֵ����++
	//CComplex operator++()
	comp5 = ++comp1;
	comp1.show();
	comp5.show();
	
	cout << comp1 << endl;
	cin >> comp1 >> endl;
	

	return 0;
}
#endif