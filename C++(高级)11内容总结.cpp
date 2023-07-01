#include<iostream>
//#include<array>	//vector
//#include<forward_list>	//list
#include<thread>
#include<list>
#include<mutex>
#include<condition_variable>
//#include<string>
#include<queue>
#include<atomic>
using namespace std;


/*
C++11 标准相关的内容 总结一下
一:关键字和语法
auto:可以根据右值，推导出左边变量(右值)的类型
nullptr:给指针专用(能够和整数进行区别)  #define NULL 0
for_each: 可以遍历数组、容器等
for(Type val : container) => 底层就是通过指针或者迭代器来实现的
{
	cout<<val<<" ";
}
右值引用: move移动语义函数和forward类型完美转发函数
模板的一个新特性: typename.. A  表示可变参(类型参数)

二:绑定器和函数对象
function:函数对象
bind:绑定器		bind1st和bind2nd + 二元函数对象 = 一元函数对象
lambda表达式

三:智能指针
shared_ptr和weak_ptr

四:容器
set和map:红黑树 O(logn)
unordered_set和unordered_map:哈希表 O(1)
array: 数组
forward_list: 前向链表  list

五:C++语言级别支持的多线程编程
creatThread
pthread_creat
clone
*/

/*
C++语言级别的多线程编程 => 代码可以跨平台
thread/mutex/codition_variable
lock_guard/unique_lock	加锁/解锁
atomic 原子类型  基于CAS操作的原子类型 线程安全的
sleep_for

C++语言层面 thread
 windows					linux
	|						  |
 creatThread			pthread_create

 线程问题:
 一、怎么创建启动一个线程
 std::thread定义一个线程对象,传入线程所需要的线程函数和参数,线程自动启动

 二、子线程如何结束
 子线程函数运行完成,线程就完成了

 三、主线程如何处理子线程
 t1.join()	等待子线程设置为分离线程,主线程结束,整个进程结束,所有子线程都自动结束
 */

#if 0
void threadHandle1(int time)
{
	//让子线程睡眠2秒
	std::this_thread::sleep_for(chrono::seconds(2));
	cout << "hello thread1!" << endl;
}

int main()
{
	//定义了一个线程对象,传入一个线程函数,新线程就还是运行了
	std::thread t1(threadHandle1, 2);
	//主线程等待子线程结束,主线程继续往下运行
	//t1.join();
	//把子线程设置成分离线程
	t1.detach();

	cout << "main thread done!" << endl;

	//主线程运行完成,查看如果当前进程还有未进行完成的子线程
	//进程就会异常终止
	return 0;
}
#endif


/*
C++  thread模拟车站三个窗口卖票的程序

线程间的互斥 => 互斥锁mutex => lock_guard封装mutex
*/
int ticketcount = 100; //车站有100张车票,由三个窗口一起卖票
//std::mutex mtx;	//全局的一把互斥锁
/*
多线程程序
竞态条件:多线程程序执行的结果是一致的,不会随着CPU对线程不同的调用顺序,而产生不同的运行结果
*/
//模拟卖票的线程函数

#if 0
void sellTicket(int index)
{
	while (ticketcount > 0)		//锁+双重判断
	{
		//临界区代码段 => 原子操作 => 线程间互斥操作了 => mutex
		//mtx.lock();
		{
			lock_guard<std::mutex> lock(mtx);
			if (ticketcount > 0)
			{
				cout << "窗口:" << index << "卖出第:" << ticketcount << "张票！" << endl;
				//cout << ticketcount << endl;
				ticketcount--;
			}
		}
		//mtx.unlock();
		std::this_thread::sleep_for(std::chrono::microseconds(100));
	}
}
int main()
{


	list<std::thread>tlist;
	for (int i = 1; i <= 3; ++i)
	{
		tlist.push_back(std::thread(sellTicket, i));
	}
	for (std::thread& t : tlist)
	{
		t.join();
	}

	cout << "所有窗口卖票结束!" << endl;
	return 0;
}
#endif

/*
C++多线程编程 - 线程间的同步通信机制
多线程编程的两个问题:
1.线程间的互斥
竞态条件 => 临界区代码段 => 保证原子操作 => 互斥锁mutex 轻量级的无锁实现CAS
strace ./a.out mutex => pthread_mutex_t
2.线程间的同步通信
生产者消费者线程模型
*/


#if 0
std::mutex mtx;		//定义互斥锁,做线程间的互斥操作
std::condition_variable cv;		//定义条件变量,做线程间的通信操作

//生产者生产一个物品，通知消费者消费一个;消费完了，消费者通知生产者再生产一个。
class Queue
{
public:
	void put(int val)	//升产商品
	{
		//lock_guard<std::mutex> guard(mtx);
		unique_lock<std::mutex> lck(mtx);
		while (!que.empty())
		{
			//que不为空,生产者应该通知消费者去消费,消费完了,再继续生产
			//生产者线程进入#1等待状态,并且#2把mtx互斥锁释放掉
			
			cv.wait(lck);
		}
		que.push(val);
		/*
		notify_one:通知另外的一个线程的
		notify_all:通知其他所有线程的
		通知其他所有的线程,生产了一个物品,可以消费了。
		其他线程得到该通知，从等待状态 => 阻塞状态 => 获得互斥锁才能继续执行
		*/
		cv.notify_all();	
		cout << "生产者:升产" << val << "号物品" << endl;
	}
	int get()	//消费物品
	{
		//lock_guard<std::mutex> guard(mtx);
		unique_lock<std::mutex> lck(mtx);
		while (que.empty())
		{
			//消费者线程发现que是空的,通知生产者线程先生产物品
			//#1 进入等待状态 #2 把互斥锁mutex释放
			
			cv.wait(lck);
		}
		int val = que.front();
		que.pop();
		cv.notify_all();	//通知生产者线程消费完了,赶紧生产
		cout << "消费者 消费" << val << "号物品" << endl;
		return val;
	}
private:
	queue<int> que;
};
void producer(Queue* que)
{
	for (int i = 1; i <= 10; ++i)
	{
		que->put(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
void consumer(Queue* que)
{
	for (int i = 1; i <= 10; ++i)
	{
		que->get();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
int main()
{
	Queue que;	//两个线程共享的队列


	std::thread t1(producer);
	std::thread t2(consumer);

	t1.join();
	t2.join();
	return 0;
}
#endif


/*
unique_lock  condition_variable
1.lock_guard和uniqe_lock
2.condition_variable   wait和notify_all方法
*/

#if 0

std::mutex mtx;		//pthread_mutex_t
std::condition_variable cv;		//pthread_condition_t
int main()
{
	/*
	通知在cv上等待的线程,条件成立,起来干活
	其他在cv上等待的线程,收到通知,从等待状态 => 阻塞状态 => 获取互斥锁 => 线程继续往下执行
	*/
	cv.notify_all();

	//它不仅可以使用在简单的临界区代码段的互斥操作中,还能用在函数调用过程中
	//unique_lock<std::mutex> lck(mtx);
	//cv.wait(lck);	// => #1.使线程进入等待状态 #2.lck.unlock可以把mtx给释放掉	

	//不可能用在函数参数传递和返回过程中,只能用在简单的临界区代码段的互斥操作中
	//lock_guard<std::mutex> guard(mtx);	//用的是智能指针 


	//mtx.lock();
	//mtx.unlock();

	return 0;
}
#endif

/*
C++11
互斥锁是比较重的,临界区代码做的事情稍稍复杂,多
系统理论上:CAS来保证上面++ --操作的原子特性就足够了    无锁操作
			exchange/swap	无锁队列 => CAS来实现的
*/
#if 0
volatile std::atomic_bool isReady = false;
volatile std::atomic_int mycount = 0;
void task()
{
	while (!isReady)
	{
		std::this_thread::yield();	//线程让出当前cpu时间片,等待下一次调度
	}
	for (int i = 0; i < 100; ++i)
	{
		mycount++;
	}

}
int main()
{
	list<std::thread> tlist;
	for (int i = 0; i < 10; ++i)
	{
		tlist.push_back(std::thread(task));
	}
	std::this_thread::sleep_for(std::chrono::seconds(3));
	isReady = true;
	

	for (std::thread& t : tlist)
	{
		t.join();
	}
	cout << "mycount:" << mycount << endl;
	return 0;
}
#endif