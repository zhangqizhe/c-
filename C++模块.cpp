#include<iostream>
using namespace std;

/*
��ģ�� => ʵ��һ��C++ STL�����һ��˳������ vector��������
SeqStack
Queue
������
�ռ�������allocator ��4������  �ڴ濪��/�ڴ��ͷ�  ������/��������
*/
#if 0
//���������Ŀռ�����������C++��׼���allocatorʵ��һ��
template<typename T>
struct Allocator
{
	T* allocate(size_t size)	//�����ڴ濪��
	{
		return (T*)malloc(sizeof(T) * size);
	}
	void deallocate(void* p)	//�����ڴ��ͷ�
	{
		free(p);
	}
	void construct(T* p, const T& val)	//���������
	{
		new (p) T(val);	//��λnew
	}
	void destory(T* p)	//�����������
	{
		p->~T();	//~T������T���͵���������
	}
};
/*
�����ײ��ڴ濪�٣��ڴ��ͷţ����������������ͨ��allocator�ռ���������ʵ��
*/
template<typename T, typename Alloc = Allocator<T>>
class vector
{
public:
	vector(int size = 10)
	{
		//��Ҫ���ڴ濪�ٺͶ�����ֿ�����
		//_first = new T[size];
		_first = _allocator.allocate(size);
		_last = _first;
		_end = _first + size;
	}
	~vector()
	{
		//����������Ч��Ԫ�أ�Ȼ���ͷ�_firstָ��ָ��Ķ��ڴ�
		//elete[]_first;
		for (T* p = _first; p != _last; ++p)
		{
			_allocator.destory(p);	//��_firstָ��ָ����������ЧԪ�ؽ�����������
		}
		_allocator.deallocate(_first);	//�ͷŶ��ϵ������ڴ�
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
		//1����ֹ�Ը�ֵ
		if (this == &rhs)
			return *this;

		//2����ԭ���Ŀռ��ͷŵ�
		//delete[]_first;
		for (T* p = _first; p != _last; ++p)
		{
			_allocator.destory(p);	//��_firstָ��ָ����������ЧԪ�ؽ�����������
		}
		_allocator.dellocate(_first);	//�ͷŶ��ϵ������ڴ�

		//3���Ϳ�������һ��
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
	void push_back(const T& val)	//������ĩβ���Ԫ��
	{
		if (full())
			expand();
		//*_last++ = val;	
		_allocator.construct(_last, val);	//_lastָ��ָ����ڴ湹��һ��ֵΪval�Ķ���
		_last++;
	}
	void pop_back()	//������ĩβɾ��Ԫ��
	{
		if (empty())
			return;
		//--_last;
		--_last;
		_allocator.destory(_last);	//����Ҫ��_lastָ��--������Ҫ����ɾ����Ԫ�ء�
	}
	T top()const	//��������ĩβ��Ԫ�ص�ֵ
	{
		return *(_last - 1);
	}
	bool full()const	//����
	{
		return _last == _end;
	}
	bool empty()const	//�п�
	{
		return _first == _last;
	}
	int size()const
	{
		return _last - _first;
	}
private:
	T* _first;	//ָ��������ʼ��λ��
	T* _last;	//ָ����������ЧԪ�صĺ��λ��
	T* _end;	//ָ������ռ�ĺ��λ��
	Alloc _allocator;	//���������Ŀռ�����������

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
			_allocator.destory(p);	//��_firstָ��ָ����������ЧԪ�ؽ�����������
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
	vec.pop_back();	//ֻ��Ҫ��������Ҫ�Ѷ�����������ڴ��ͷŷ��뿪
	cout << "---------------" << endl;

	return 0;
}

#endif
/*
����ģ��
ģ��ķ����Ͳ���  ��������������(�������ߵ�ַ/���ö�����)���ǳ�����ֻ��ʹ�ã��������޸�

��ģ�� => ʵ���� => ģ����
*/

#if 0
template<typename T>
class SeqStack	//ģ������ + ���Ͳ����б� = ������
{
public:
	//������������������ü�<T>,��������ģ��ĵط������ϲ����б�
	SeqStack<T>(int size = 10)
		: _pstack(new T[size])
		, _top(0)
		, _size(size)	//��Ա�����ĳ�ʼ��һ�㶼д�ڹ��캯���ĳ�ʼ���б���
	{}
	//��������
	~SeqStack<T>()
	{
		delete[]_pstack;
		_pstack = nullptr;
	}
	//�������캯��
	SeqStack<T>(const SeqStack<T>& stack)
		: _top(stack._top)
		, _size(stack._size)
	{
		_pstack = new T[_size];
		//��Ҫ��memcopy���п���
		for (int i = 0; i < _top; ++i)
		{
			_pstack[i] = stack._pstack[i];
		}
	}
	SeqStack<T>& operator=(const SeqStack<T>& stack)	//��ֵ����������غ���
	{
		if (this == &stack)
			return nullptr;

		delete[]_pstack;

		_top = stack._top;
		_size = stack._size;
		_pstack = new T[_size];

		//��Ҫ��memcopy���п���
		for (int i = 0; i < _top; ++i)
		{
			_pstack[i] = stack._pstack[i];
		}
		return *this;
	}

	void push(const T& val)	//��ջ����
	{
		if (full())
			expand();
		_pstack[_top++] = val;
	}
	void pop()	//��ջ����
	{
		if (empty())
			return;
		--_top;
	}
	T top()const	//����ջ��Ԫ��
	{
		if (empty())
			throw "stack is empty!";	//�׳��쳣Ҳ�������߼�����
		return _pstack[_top - 1];
	}
	bool full()const	//ջ��
	{
		return _top == _size;
	}
	bool empty()const	//ջ��
	{
		return _top == 0;
	}
private:
	T* _pstack;
	int _top;
	int _size;

	//˳��ջ�ײ����鰴2���ķ�ʽ����
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
C++  ����ģ��
ģ������壺������Ҳ���Խ��в�����
int sum(int a,int b){ return a+b; }

����ģ��	<=	�ǲ����б���ģ���Ϊ���ͻ���֪��
ģ���ʵ����	<=	�������õ����ʵ����
ģ�庯��	<=	����Ҫ���������������

ģ�����Ͳ��� typename/class
ģ������Ͳ���

ģ���ʵ������ => ���Ը����û������ʵ�����ͣ����Ƶ�ģ�����Ͳ����ľ�������
ģ���������(ר�û�) ����(���Ǳ������ṩ�ģ������û��ṩ��)��ʵ����
ģ�庯����ģ�������������ģ�庯�������ع�ϵ

ģ������ǲ�����һ���ļ��ж��壬����һ���ļ���ʹ��
ģ��������֮ǰ��һ��Ҫ����ģ�嶨��ĵط��������Ļ���ģ����ܹ�����������ʵ�����������ܹ�������������Ĵ���

���ԣ�ģ����붼�Ƿ���ͷ�ļ����еģ�Ȼ����Դ�ļ�����ֱ�ӽ���#include����
*/
#if 0
//����ģ��
template<typename T>		//����һ��ģ������б�
bool compare(T a, T b)		//compare��һ������ģ��
{
	cout << "template compare" << endl;
	return a > b;
}
/*
�ں������õ㣬�������û�ָ�������ͣ���ԭģ��ʵ����һ�ݺ����������
ģ�庯��
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

//ģ���������
//���compare����ģ�壬�ṩconst char * ���͵��������汾
template<>
bool compare<const char*>(const char* a, const char* b)
{
	cout << "compare<const char*>" << endl;
	return strcmp(a, b) > 0;
}

//��ģ�庯��	-	��ͨ����
bool compare(const char* a, const char* b)
{
	cout << "normal compare" << endl;
	return strcmp(a, b) > 0;
}
int main()
{
	//�����ĵ��õ�
	compare<int>(10, 20);
	compare<double>(10.5, 20.5);

	//����ģ��ʵ�ε�����
	compare(10, 30);

	//����ģ��ʵ�ε����� T const char*
	//����ĳЩ������˵������������Ĭ��ʵ������ģ����룬���봦���߼����д����
	//���������Ȱ�compare����ɺ������֣�û�еĻ�����ȥ��compareģ��
	compare("aaa", "bbb");
	return 0;
}
#endif
