#include<iostream>
#include<memory>
#include<thread>
#include<string>
using namespace std;

/*
����ָ��Ľ���
�Լ�ʵ������ָ��
�������ü���������ָ��auto_ptr,scoped_ptr,unique_ptr
�����ü���������ָ��shared_ptr,weak_ptr
����ָ��Ľ�������(ѭ������)����
���̷߳��ʹ����������
�Զ���ɾ����
*/

/*
shared_ptr:ǿ����ָ�� ���Ըı���Դ�����ü���
weak_ptr:������ָ�� ����ı���Դ�����ü���
weak_ptr  =>  shared_ptr  => ��Դ(�ڴ�)

ǿ����ָ��ѭ������(��������)��ʲô���⣿ʲô�������ô�����
���new��������Դ�޷��ͷ�!!!��Դй¶����!
��������ʱ��,��ǿ����ָ��;���ö���ĵط�,ʹ��������ָ��
*/



/*
����ָ���ɾ����  deletor
����ָ��:�ܹ���֤��Դ���Ե��ͷ�  delete ptr;
*/


#if 0
/*
C++�ǳ������Ŀ�Դ�����muduo��
���̷߳��ʹ��������̰߳�ȫ����
*/
class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
	void testA() { cout << "�ǳ����õķ���!" << endl; }
};
//���߳�
void handler01(weak_ptr<A> pw)
{
	

	shared_ptr<A> sp = pw.lock();
	if (sp != nullptr)
	{
		sp->testA();
	}
	else
	{
		cout << "A�����Ѿ�����,�����ٷ���!" << endl;
	}

}
//main�߳�
int main()
{
	{

		shared_ptr<A> p(new A());

		thread t1(handler01, weak_ptr<A>(p));
		//q����A�����ʱ��,��Ҫ���һ��A�����Ƿ��
		std::this_thread::sleep_for(std::chrono::seconds(2));
		t1.detach();

	}
	//�����ȴ����߳̽���
	//t1.join();
	std::this_thread::sleep_for(std::chrono::seconds(20));

	return 0;
}


//����Դ�������ü�������
template<typename T>
class RefCnt
{
public:
	RefCnt(T* ptr = nullptr)
		:mptr(ptr)
	{
		if (mptr != nullptr)
			mcount = 1;
	}
	void addRef() { mcount++; }	//������Դ�����ü���
	int deRef() { return --mcount; }
private:
	T* mptr;
	int count;
};

//����ָ��,��֤��������Դ���Զ��ͷ�!
//����ջ�ϵĶ�����������Զ�����������,��������Դ���Զ��ͷŵ�!
template<typename T>
class CSmartPtr
{
public:
	CSmartPtr(T *ptr = nullptr)
		:mptr(ptr)
	{
		mpRefCnt = new RefCnt<T>(mptr);
	}
	~CSmartPtr() 
	{
		if (0 == mpRefCnt->deRef())
		{
			delete mptr;
			mptr = nullptr;
		}
	}

	T& operator*() { return *mptr; }
	T* operator->() { return mptr; }

	CSmartPtr(const CSmartPtr<T>& src)
		:mptr(src.mptr),mpRefCnt(src.mpRefCnt)
	{
		if(mptr!=nullptr)
			mpRefCnt->addRef();
	}
	CSmartPtr<T>& operator=(const CSmartPtr<T>& src)
	{
		if (this == &src)
			return *this;
		if (0 == mpRefCnt->deRef())
		{
			delete mptr;
		}
		mptr = src.mptr;
		mpRefCnt = src.mpRefCnt;
		mpRefCnt->addRef();
		return *this;
	}
private:
	T* mptr;	//ָ����Դ��ָ��
	RefCnt<T>* mpRefCnt;	//ָ�����Դ�����ü�����ָ��
};

int main()
{
	/*
	�����ü���������ָ��shared_ptr��weak_ptr;
	�����ü���:�������ָ����Թ���ͬһ����Դ
	�����ü���:��ÿһ��������Դ,ƥ��һ�����ü���
	����ָ��-����Դ��ʱ��-�����ü���+1
	����ָ��-����ʹ����Դ��ʱ��-�����ü���-1 -�� !=0 0��Դ�ͷ���
	*/

	return 0;
}


int main()
{




	/*
	�������ü���������ָ��
	auto_ptr��C++������
	C++11�±�׼:
	scoped_ptr	ֻ��ʹ�õ�������

	scoped_ptr(const scoped_ptr<T>&) = delete;
	scoped_ptr<T>& operator=(const scoped_ptr<T>&) = delete;

	�Ƽ�ʹ��:
	unique_ptr
	unique_ptr(const unique_ptr<T>&) = delete;
	unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;

	unique_ptr(unique_ptr<T> &&src)
	unique_ptr<T>& operator=(unique_ptr<T> &&src)

	unique_ptr<T> getSmartPtr()
	{
		unique_ptr<T> ptr(new T());
		return ptr;
	}

	unique_ptr<int> ptr1 = getSmartPtr<int>();
	ptr1=getSmartPtr<int>();


	��ô���ǳ�������⣿

	std::move  =�� C++  ��ֵ����  std::move�õ���ǰ��������ֵ����
	*/

	//CSmartPtr<int>ptr1(new int);

	
	//ת�ƶ��������Ȩ,��ptr1����������������Ȩ,����ͨ���������콫����Ȩת��ptr2,ԭ����ptr1�ɿ�ָ��
	//auto_ptr<int>ptr1(new int);
	//auto_ptr<int>ptr2(ptr1);

	//���Ƽ�ʹ��auto_ptr  ,vector<auto_ptr<int>> vec1; vec2(vec1);NO

	//*ptr2 = 20;
	//cout << *ptr1 << endl;

	unique_ptr<int>p1(new int);
	unique_ptr<int>p2(std::move(p1));


	return 0;
}

#endif