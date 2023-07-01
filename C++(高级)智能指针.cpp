#include<iostream>
#include<memory>
#include<thread>
#include<string>
using namespace std;

/*
智能指针的介绍
自己实现智能指针
不带引用计数的智能指针auto_ptr,scoped_ptr,unique_ptr
带引用计数的智能指针shared_ptr,weak_ptr
智能指针的交叉引用(循环引用)问题
多线程访问共享对象问题
自定义删除器
*/

/*
shared_ptr:强智能指针 可以改变资源的引用计数
weak_ptr:弱智能指针 不会改变资源的引用计数
weak_ptr  =>  shared_ptr  => 资源(内存)

强智能指针循环引用(交叉引用)是什么问题？什么结果？怎么解决？
造成new出来的资源无法释放!!!资源泄露问题!
定义对象的时候,用强智能指针;引用对象的地方,使用弱智能指针
*/



/*
智能指针的删除器  deletor
智能指针:能够保证资源绝对的释放  delete ptr;
*/


#if 0
/*
C++非常著名的开源网络库muduo库
多线程访问共享对象的线程安全方法
*/
class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
	void testA() { cout << "非常好用的方法!" << endl; }
};
//子线程
void handler01(weak_ptr<A> pw)
{
	

	shared_ptr<A> sp = pw.lock();
	if (sp != nullptr)
	{
		sp->testA();
	}
	else
	{
		cout << "A对象已经析构,不能再访问!" << endl;
	}

}
//main线程
int main()
{
	{

		shared_ptr<A> p(new A());

		thread t1(handler01, weak_ptr<A>(p));
		//q访问A对象的时候,需要侦测一下A对象是否存活。
		std::this_thread::sleep_for(std::chrono::seconds(2));
		t1.detach();

	}
	//阻塞等待子线程结束
	//t1.join();
	std::this_thread::sleep_for(std::chrono::seconds(20));

	return 0;
}


//对资源进行引用计数的类
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
	void addRef() { mcount++; }	//增加资源的引用计数
	int deRef() { return --mcount; }
private:
	T* mptr;
	int count;
};

//智能指针,保证能做到资源的自动释放!
//利用栈上的对象出作用域自动析构的特征,来做到资源的自动释放的!
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
	T* mptr;	//指向资源的指针
	RefCnt<T>* mpRefCnt;	//指向该资源的引用计数的指针
};

int main()
{
	/*
	带引用计数的智能指针shared_ptr和weak_ptr;
	带引用计数:多个智能指针可以管理同一个资源
	带引用计数:给每一个对象资源,匹配一个引用计数
	智能指针-》资源的时候-》引用计数+1
	智能指针-》不使用资源的时候-》引用计数-1 -》 !=0 0资源释放了
	*/

	return 0;
}


int main()
{




	/*
	不带引用计数的智能指针
	auto_ptr：C++库里面
	C++11新标准:
	scoped_ptr	只能使用单个对象

	scoped_ptr(const scoped_ptr<T>&) = delete;
	scoped_ptr<T>& operator=(const scoped_ptr<T>&) = delete;

	推荐使用:
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


	怎么解决浅拷贝问题？

	std::move  =》 C++  右值引用  std::move得到当前变量的右值类型
	*/

	//CSmartPtr<int>ptr1(new int);

	
	//转移对象的所有权,当ptr1持有这个对象的所有权,现在通过拷贝构造将所有权转给ptr2,原来的ptr1成空指针
	//auto_ptr<int>ptr1(new int);
	//auto_ptr<int>ptr2(ptr1);

	//不推荐使用auto_ptr  ,vector<auto_ptr<int>> vec1; vec2(vec1);NO

	//*ptr2 = 20;
	//cout << *ptr1 << endl;

	unique_ptr<int>p1(new int);
	unique_ptr<int>p2(std::move(p1));


	return 0;
}

#endif