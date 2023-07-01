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
C++11 ��׼��ص����� �ܽ�һ��
һ:�ؼ��ֺ��﷨
auto:���Ը�����ֵ���Ƶ�����߱���(��ֵ)������
nullptr:��ָ��ר��(�ܹ���������������)  #define NULL 0
for_each: ���Ա������顢������
for(Type val : container) => �ײ����ͨ��ָ����ߵ�������ʵ�ֵ�
{
	cout<<val<<" ";
}
��ֵ����: move�ƶ����庯����forward��������ת������
ģ���һ��������: typename.. A  ��ʾ�ɱ��(���Ͳ���)

��:�����ͺ�������
function:��������
bind:����		bind1st��bind2nd + ��Ԫ�������� = һԪ��������
lambda���ʽ

��:����ָ��
shared_ptr��weak_ptr

��:����
set��map:����� O(logn)
unordered_set��unordered_map:��ϣ�� O(1)
array: ����
forward_list: ǰ������  list

��:C++���Լ���֧�ֵĶ��̱߳��
creatThread
pthread_creat
clone
*/

/*
C++���Լ���Ķ��̱߳�� => ������Կ�ƽ̨
thread/mutex/codition_variable
lock_guard/unique_lock	����/����
atomic ԭ������  ����CAS������ԭ������ �̰߳�ȫ��
sleep_for

C++���Բ��� thread
 windows					linux
	|						  |
 creatThread			pthread_create

 �߳�����:
 һ����ô��������һ���߳�
 std::thread����һ���̶߳���,�����߳�����Ҫ���̺߳����Ͳ���,�߳��Զ�����

 �������߳���ν���
 ���̺߳����������,�߳̾������

 �������߳���δ������߳�
 t1.join()	�ȴ����߳�����Ϊ�����߳�,���߳̽���,�������̽���,�������̶߳��Զ�����
 */

#if 0
void threadHandle1(int time)
{
	//�����߳�˯��2��
	std::this_thread::sleep_for(chrono::seconds(2));
	cout << "hello thread1!" << endl;
}

int main()
{
	//������һ���̶߳���,����һ���̺߳���,���߳̾ͻ���������
	std::thread t1(threadHandle1, 2);
	//���̵߳ȴ����߳̽���,���̼߳�����������
	//t1.join();
	//�����߳����óɷ����߳�
	t1.detach();

	cout << "main thread done!" << endl;

	//���߳��������,�鿴�����ǰ���̻���δ������ɵ����߳�
	//���̾ͻ��쳣��ֹ
	return 0;
}
#endif


/*
C++  threadģ�⳵վ����������Ʊ�ĳ���

�̼߳�Ļ��� => ������mutex => lock_guard��װmutex
*/
int ticketcount = 100; //��վ��100�ų�Ʊ,����������һ����Ʊ
//std::mutex mtx;	//ȫ�ֵ�һ�ѻ�����
/*
���̳߳���
��̬����:���̳߳���ִ�еĽ����һ�µ�,��������CPU���̲߳�ͬ�ĵ���˳��,��������ͬ�����н��
*/
//ģ����Ʊ���̺߳���

#if 0
void sellTicket(int index)
{
	while (ticketcount > 0)		//��+˫���ж�
	{
		//�ٽ�������� => ԭ�Ӳ��� => �̼߳以������� => mutex
		//mtx.lock();
		{
			lock_guard<std::mutex> lock(mtx);
			if (ticketcount > 0)
			{
				cout << "����:" << index << "������:" << ticketcount << "��Ʊ��" << endl;
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

	cout << "���д�����Ʊ����!" << endl;
	return 0;
}
#endif

/*
C++���̱߳�� - �̼߳��ͬ��ͨ�Ż���
���̱߳�̵���������:
1.�̼߳�Ļ���
��̬���� => �ٽ�������� => ��֤ԭ�Ӳ��� => ������mutex ������������ʵ��CAS
strace ./a.out mutex => pthread_mutex_t
2.�̼߳��ͬ��ͨ��
�������������߳�ģ��
*/


#if 0
std::mutex mtx;		//���廥����,���̼߳�Ļ������
std::condition_variable cv;		//������������,���̼߳��ͨ�Ų���

//����������һ����Ʒ��֪ͨ����������һ��;�������ˣ�������֪ͨ������������һ����
class Queue
{
public:
	void put(int val)	//������Ʒ
	{
		//lock_guard<std::mutex> guard(mtx);
		unique_lock<std::mutex> lck(mtx);
		while (!que.empty())
		{
			//que��Ϊ��,������Ӧ��֪ͨ������ȥ����,��������,�ټ�������
			//�������߳̽���#1�ȴ�״̬,����#2��mtx�������ͷŵ�
			
			cv.wait(lck);
		}
		que.push(val);
		/*
		notify_one:֪ͨ�����һ���̵߳�
		notify_all:֪ͨ���������̵߳�
		֪ͨ�������е��߳�,������һ����Ʒ,���������ˡ�
		�����̵߳õ���֪ͨ���ӵȴ�״̬ => ����״̬ => ��û��������ܼ���ִ��
		*/
		cv.notify_all();	
		cout << "������:����" << val << "����Ʒ" << endl;
	}
	int get()	//������Ʒ
	{
		//lock_guard<std::mutex> guard(mtx);
		unique_lock<std::mutex> lck(mtx);
		while (que.empty())
		{
			//�������̷߳���que�ǿյ�,֪ͨ�������߳���������Ʒ
			//#1 ����ȴ�״̬ #2 �ѻ�����mutex�ͷ�
			
			cv.wait(lck);
		}
		int val = que.front();
		que.pop();
		cv.notify_all();	//֪ͨ�������߳���������,�Ͻ�����
		cout << "������ ����" << val << "����Ʒ" << endl;
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
	Queue que;	//�����̹߳���Ķ���


	std::thread t1(producer);
	std::thread t2(consumer);

	t1.join();
	t2.join();
	return 0;
}
#endif


/*
unique_lock  condition_variable
1.lock_guard��uniqe_lock
2.condition_variable   wait��notify_all����
*/

#if 0

std::mutex mtx;		//pthread_mutex_t
std::condition_variable cv;		//pthread_condition_t
int main()
{
	/*
	֪ͨ��cv�ϵȴ����߳�,��������,�����ɻ�
	������cv�ϵȴ����߳�,�յ�֪ͨ,�ӵȴ�״̬ => ����״̬ => ��ȡ������ => �̼߳�������ִ��
	*/
	cv.notify_all();

	//����������ʹ���ڼ򵥵��ٽ�������εĻ��������,�������ں������ù�����
	//unique_lock<std::mutex> lck(mtx);
	//cv.wait(lck);	// => #1.ʹ�߳̽���ȴ�״̬ #2.lck.unlock���԰�mtx���ͷŵ�	

	//���������ں����������ݺͷ��ع�����,ֻ�����ڼ򵥵��ٽ�������εĻ��������
	//lock_guard<std::mutex> guard(mtx);	//�õ�������ָ�� 


	//mtx.lock();
	//mtx.unlock();

	return 0;
}
#endif

/*
C++11
�������ǱȽ��ص�,�ٽ������������������Ը���,��
ϵͳ������:CAS����֤����++ --������ԭ�����Ծ��㹻��    ��������
			exchange/swap	�������� => CAS��ʵ�ֵ�
*/
#if 0
volatile std::atomic_bool isReady = false;
volatile std::atomic_int mycount = 0;
void task()
{
	while (!isReady)
	{
		std::this_thread::yield();	//�߳��ó���ǰcpuʱ��Ƭ,�ȴ���һ�ε���
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