
/*
C++ STL standard template libaray ��׼ģ���
һ����׼����	C++11 array  forward_list
1.˳������
vector
deque
list
2.����������
stack
queue
priority_queue
3.��������
�����������  ��ʽ��ϣ�� ��ɾ��O(1)
set:���� key       map:ӳ���[key,value]
unordered_set	���ؼ���	������keyֵ�ظ�
unordered_multiset	���ؼ���	����keyֵ�ظ�
unordered_map	����ӳ���		������keyֵ�ظ�
unordered_multimap	����ӳ���	����keyֵ�ظ�

����������� ���ں���� ��ɾ��O(log2n) 2�ǵ���(���Ĳ��������ĸ߶�)
set
multiset
map
multimap

����������
����  string,bitset(λ����)

����������
iterator��const_iterator
reverse_iterator��const_reverse_iterator

�ġ���������(����C�ĺ���ָ��)
greater,less

�塢��������
sort,find,find_if,binary_search,for_each
*/
#include<iostream>
#include<vector>
#include<list>
#include<stack>	//stack
#include<queue>	//queue��priority_queue

//ʹ�������������������ͷ�ļ�
#include<set>
#include<map>

//ʹ�������������������ͷ�ļ�
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<algorithm>	//������c++ STL����ķ����㷨
#include<functional>	//�����˺�������Ͱ���
using namespace std;

/*
�����㷨 = template + ������ + ��������
�ص�һ:�����㷨�Ĳ������յĶ��ǵ�����
�ص��:�����㷨�Ĳ��������Խ��պ�������(c����ָ��)
sort,find,find_if,binary_search,for_each

���� + ��Ԫ�������� => һԪ��������
bind1st:�Ѷ�Ԫ���������operator()(a ,b)�ĵ�һ���βΰ�����
bind2nd:�Ѷ�Ԫ���������operator()(a ,b)�ĵڶ����βΰ�����
*/

#if 0
int main()
{
	int arr[] = { 12,5,68,1,6,8,1,5,79,984 };
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
	cout << endl;

	//���������н��ж��ֲ���	���ֲ���Ч�ʸ�
	if (binary_search(vec.begin(), vec.end(), 8))
	{
		cout<<"binary_search 8����"<<endl;
	}

	auto it1 = find(vec.begin(), vec.end(), 8);
	if (it1 != vec.end())
	{
		cout << "find 8����" << endl;
	}

	//���뺯������greater���ı�����Ԫ������ʱ�ıȽϷ���
	sort(vec.begin(), vec.end(),greater<int>());
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	//��48������뵽vector��������	�ҵ�һ��С��48������
	//find_if��Ҫ����һ��һԪ��������
	//greater  a > b    less  a < b
	//auto it2 = find_if(vec.begin(), vec.end(),bind1st(greater<int>(),48));
	auto it2 = find_if(vec.begin(), vec.end(),
		//bind2nd(less<int>(),48));
		[](int val)->bool {return val < 48; });
	vec.insert(it2, 48);
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	//for_each���Ա�������������Ԫ�أ�������������ʺϵĺ��������������Ԫ�ؽ��й���
	for_each(vec.begin(), vec.end(),
		[](int val)->void
		{
			if (val % 2 == 0)
			{
				cout << val << " ";
			}
		});
	cout << endl;

	return 0;
}

#endif
/*
��������	=>	c��������ĺ���ָ��


ͨ������ָ����ú�������û�а취�����ģ�Ч�ʺܵͣ���Ϊ�к������ÿ���
1.ͨ�������������operator(),����ʡ�Ժ����ĵ��ÿ�������ͨ������ָ����ú���(���ܹ�inline��������)Ч�ʸ�
2.��Ϊ�����������������ɵģ����Կ��������صĳ�Ա������������¼��������ʹ��ʱ�������Ϣ
*/



/*
�����ĵ�����
const_iterator:���������������  ֻ�ܶ���������д
iterator:��ͨ�����������
reverse_iterator:��ͨ�ķ��������
const_reverse_iterator:�����ķ��������
*/


#if 0
int main()
{
	vector<int>vec;
	
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100);
	}
	//auto it = vec.begin();
	//const_iterator	<=	iterator
	/*
	class const_iterator{ }  ����
	class iterator : public const_iterator{ }	������

	*/
	vector<int>::const_iterator it1 = vec.begin();
		for (; it1 != vec.end(); ++it1)
	{
		cout << *it1 << " ";
	}
	cout << endl;
	
	//rbegin();���ص������һ��Ԫ�صķ����������ʾ
	//rend: ���ص�����Ԫ��ǰ��λ�õĵ������ı�ʾ
	//vector<int>::reverse_iterator
	//vector<int>::reverse_iterator rit = vec.rbegin();
	vector<int>::const_reverse_iterator rit = vec.rbegin();
	for (; rit != vec.rend(); ++rit)
	{
		cout << *rit << " ";
	}
	cout << endl;
	
	/*for (int v : vec)
	{
		cout << v << " ";
	}
	*/
	cout << endl;
	return 0;
}

#endif

#if 0
class Student
{
public:
	Student(int id, string name)
		:_id(id), _name(name) { }
	bool operator<(const Student& stu)const
	{
		return _id < stu._id;
	}
private:
	int _id;
	string _name;
	friend ostream& operator<<(ostream& out, const Student& stu);
};
ostream& operator<<(ostream& out, const Student& stu)
{
	out << "id:" << stu._id << "name:" << stu._name << endl;
	return out;
}

int main()
{
	map<int, string> stuMap;
	stuMap.insert({ 1000,Student(1000,"����") });
	return 0;
}




class Student
{
public:
	Student(int id,string name)
		:_id(id),_name(name){ }
	bool operator<(const Student& stu)const
	{
		return _id < stu._id;
	}
private:
	int _id;
	string _name;
	friend ostream& operator<<(ostream& out, const Student& stu);
};
ostream& operator<<(ostream& out, const Student& stu)
{
	out << "id:" << stu._id << "name:" << stu._name << endl;
	return out;
}
int main()
{



	set<Student> set1;

	set1.insert(Student(1000, "����"));
	set1.insert(Student(2000, "����"));

	for (auto it = set1.begin();
		it != set1.end(); ++it)
	{
		cout << *it << endl;
	}

	/*
	set<int>set1;
	for (int i = 0; i < 20; ++i)
	{
		set1.insert(rand() % 20 + 1);
	}
	for (int v : set1)
	{
		cout << v << " ";
	}
	cout << endl;
	*/

	return 0;
}
#endif

/*
����������
1.���������ײ�����ݽṹ  O(1) O(log2n)
2.������ɾ�鷽��

����:insert(val)
����:iterator�Լ�����������find��Ա����
ɾ��:erase(key)  erase(it)
*/
#if 0
int main()
{
	//���������ݲ��ظ�;ȥ�ظ���ʱ��
	const int ARR_LEN = 100;
	int arr[ARR_LEN] = { 0 };
	for (int i = 0; i < ARR_LEN; ++i)
	{
		arr[i] = rand() % 20 + 1;
	}
	//�����10���������,�����ֽ���ȥ�ش�ӡ

	unordered_set<int>set;
	for (int v : arr)	//O(n)
	{
		set.insert(v);
	}
	for (int v : set)
	{
		cout << v << " ";
	}
	cout << endl;





	//�����10��������У�ͳ����Щ�����ظ���,����ͳ�������ظ��Ĵ���
	unordered_map<int, int> map1;
	for (int k : arr)
	{
		auto it = map1.find(k);
		if (it == map1.end())
		{
			map1.insert({ k,1 });
		}
		else
		{
			it->second++;	
		}
	}

	/*foreach���д�ӡ
	for (const pair<int, int>& p : map1)
	{
		if (p.second > 1)
		{
			cout << "key:" << p.first << "count:" << p.second << endl;
		}
	}
	*/

	auto it1 = map1.begin();
	for (; it1 != map1.end(); ++it1)
	{
		if (it1->second > 1)
		{	
			cout << "key:" << it1->first << "count:" << it1->second << endl;
		}	
	}

	/*
	[key,value]
	class Pair
	{
		first; => key
		second; => value
	};

	map��operator[](map�����������غ���)
	1.��ѯ
	2.���key�����ڣ��������һ������[key,string()]
	V& operator[](const K &key)
	{
		insert({key,V()});
	}
	*/

	/*
	unordered_map<int, string> map1;
	map1.insert(make_pair(1000, "����"));	//map�����Ӻ���
	map1.insert({ 1010,"����"});
	map1.insert({ 1020,"����"});
	map1.insert({ 1030,"����"});
	map1.erase(1020);	//ɾ��Ԫ��

	auto it1 = map1.find(1030);
	if (it1 != map1.end())
	{
		cout << "key:" << it1->first << "value:" << it1->second << endl;
	}

	*/


	//cout << map1.size() << endl;
	// map operator[](key) => value
	//cout << map1[1000] << endl;




	unordered_set<int> set1;	//����洢keyֵ�ظ���Ԫ��
	//unordered_multiset<int> set1;
	for (int i = 0; i < 50; ++i)
	{
		set1.insert(rand() % 20 + 1);
	}
	//cout << set1.size() << endl;
	//cout << set1.count(15) << endl;

	auto it1 = set1.begin();
	for (; it1 != set1.end(); ++it1)
	{
		cout << *it1 << " ";
	}
	cout << endl;

	set1.erase(20);	//��keyֵɾ��Ԫ��

	for (it1 = set1.begin(); it1 != set1.end(); )
	{
		if (*it1 == 30)
		{
			it1 = set1.erase(it1);	//����erase��it1��������ʧЧ��
		}
		else
		{
			++it1;
		}
	}

	it1 = set1.find(20);
	if (it1 != set1.end())
	{
		set1.erase(it1);
	}

	for (int v : set1)
	{
		cout << v << " ";
	}
	cout << endl;

	return 0;
}

#endif

/*
��׼���� - ����������	=>	���ģʽ���ͽ���������ģʽ
��ô�����������
1.�������ײ�û���Լ������ݽṹ��������һ�������ķ�װ�����ķ���ȫ���ɵײ���������������ʵ��
2.û��ʵ���Լ��ĵ�����

template<typename T,typename Container = deque<T>>
class Stack
{
public:
	void push(const T& val) { con.push_back(val); }
	void pop() { con.pop_back(); }
	T top()const { return con.back(); }
private:
	Container con;
}

stack:push��ջ  pop��ջ  top�鿴ջ��Ԫ��  empty�ж�ջ��   size����Ԫ�ظ���

queue:push���  pop����  front�鿴��ͷԪ��  back�鿴��βԪ��   empty�ж��ӿ�  size����Ԫ�ظ���
queue->deque  Ϊʲô������vector�أ�
stack->deque  Ϊʲô������vector�أ�
1.vector�ĳ�ʼ�ڴ�ʹ��Ч��̫���ˣ� û��deque��
2.����deque��˵����Ҫ֧��β�����룬ͷ��ɾ��   ���queue����vector�������Ч�ʺܵ�
3.vector��Ҫ��Ƭ�������ڴ棬��dequeֻ��Ҫ�ֶε��ڴ棬���洢��������ʱ����Ȼdeque�����ڴ�������ʸ���һЩ

priority_queue: push���  pop����  top�鿴�Զ�Ԫ��  empty�ж϶ӿ�  size����Ԫ�ظ���	  Ĭ��:�����
priority_queue->vector   Ϊʲô����vector��
�ײ�Ĭ���ǰ��������һ������ѽṹ����һ���ڴ������������Ϲ���һ������ѻ���С���ѵ�

*/

#if 0
int main()
{
	priority_queue<int> pque;
	for (int i = 0; i < 20; ++i)
	{
		pque.push(rand() % 100 + 1);
	}
	cout << pque.size() << endl;
	while (!pque.empty())
	{
		cout << pque.top() << " ";
		pque.pop();
	}

	queue<int> que;
	for (int i = 0; i < 20; ++i)
	{
		que.push(rand() % 100 + 1);
	}
	cout << que.size() << endl;
	while (!que.empty())
	{
		cout << que.front() << " ";
		que.pop();
	}

	/*
	stack<int> s1;
	for (int i = 0; i < 20; ++i)
	{
		s1.push(rand() % 100 + 1);
	}
	cout << s1.size() << endl;
	while (!s1.empty())
	{
		cout << s1.top() << " ";
		s1.pop();
	}
	*/
	return 0;
}

#endif

/*
vector�ص�:��̬���飬�ڴ��������ģ�2���ķ�ʽ�������ݣ�vector<int> vec;0-1-2-4-8... reserve(20)/resize(20)
deque�ص�:��̬���ٵĶ�ά����ռ䣬�ڶ�ά�ǹ̶����ȵ�����ռ䣬���ݵ�ʱ��(��һά���������2������)
		�澭����:deque�ײ��ڴ��Ƿ�������	������  ÿһ���ڶ�ά�������ģ�

���������򿼲�:�������յ����
�����ĺ��򿼲�:������������֮��ĶԱ�


vector��deque֮�������
1.�ײ����ݽṹ:
2.ǰ�к����ɾ��Ԫ�ص�ʱ�临�Ӷ�:  �м��ĩβO(1)  ǰdeque	O(1)  vector O(n)
3.�����ڴ��ʹ��Ч��: vector��Ҫ���ڴ�ռ������������  deque ���Էֿ�������ݴ洢������Ҫ�ڴ�ռ������һƬ������
4.���м����insert����erase��vector��deque���ǵ�Ч��˭�ܺ�һ�㣿˭�ܲ�һ�㣿  O(n)
		����deque�ĵڶ�ά�ڴ�ռ䲻�������ģ�������deque�м����insert����erase�����Ԫ���ƶ���ʱ��Ҫ��vector��

		
vector��list֮�������	����:����ɾ��O(n) ��ѯO(n) 	�������O(1)	����:(����������ʱ��)����ɾ��O(1)  ��ѯO(n)
1.�ײ����ݽṹ: ����    ˫��ѭ������
*/




/*
deque:˫�˶�������
�ײ����ݽṹ:��̬���ٵĶ�ά���飬һά�����2��ʼ����2���ķ�ʽ�������ݣ�ÿ�����ݺ�ԭ���ڶ�ά�����飬
���µĵ�һά�����±�oldsize/2��ʼ��ţ����¶�Ԥ����ͬ�Ŀ��У�����֧��deque����βԪ�����

deque<int> deq;
����
deq.push_back(20);  ��ĩβ���Ԫ��  O(1)
deq.push_front(20);	���ײ����Ԫ��  O(1)
deq.insert(it,20);  itָ���λ�����Ԫ��  O(n)	

ɾ��
deq.pop_back();		��ĩβɾ��Ԫ��  O(1)
deq.pop_front();	���ײ�ɾ��Ԫ��  O(1)
deq.erase(it);		��itָ���λ��ɾ��Ԫ��  O(n)

��ѯ����
iterator(������insert��eraseһ��Ҫ���ǵ�����ʧЧ������)

list: ��������
�ײ����ݽṹ: ˫���ѭ������

list<int> mylist;
����
mylist.push_back(20);  ��ĩβ���Ԫ��  O(1)
mylist.push_front(20);	���ײ����Ԫ��  O(1)
mylist.insert(it,20);  itָ���λ�����Ԫ��  O(1)	�����н���insert��ʱ��Ҫ����һ��query��ѯ����
	����������˵����ѯ����Ч�ʱȽ���

ɾ��
mylist.pop_back();		��ĩβɾ��Ԫ��  O(1)
mylist.pop_front();	���ײ�ɾ��Ԫ��  O(1)
mylist.erase(it);		��itָ���λ��ɾ��Ԫ��  O(1)

��ѯ����
iterator(������insert��eraseһ��Ҫ���ǵ�����ʧЧ������)

deque��list����vector���������������ɾ�������ӿ�:
pop_front��push_front
*/



/*
vector:��������
�ײ����ݽṹ����̬���ٵ����飬ÿ����ԭ���ռ�Ĵ�С��2���������ݵ�

vector<int>vec;
����:
vec.push_back(20);  ������ĩβ���Ԫ��  O(1)  ������������
vec.insert(it,20);  �ڵ�����ָ���λ������һ��Ԫ��20	O(n)	������������

ɾ��:
vec.pop_back();  ĩβɾ��Ԫ��  O(1)
vec.erase(it);   ɾ��it������ָ���Ԫ��  O(n)

��ѯ:
operator[] ͨ�������±��������vec[5]   O(1)
iterator ���������б���
find,for_each
foreach => ͨ��iterator��ʵ�ֵ�

ע�⣺���������������������ɾ������(insert/erase),һ��Ҫ���µ������������һ��insert����erase��ɣ���������ʧЧ��

���÷�������
size()
empty()
reserve(20); vectorԤ���ռ�		ֻ�������ײ㿪��ָ����С���ڴ�ռ䣬����������µ�Ԫ��
resize(20) :���������õ�		�����������ײ㿪��ָ����С���ڴ�ռ䣬��������µ�Ԫ��
swap  :������������Ԫ�ؽ���


��ע��
����push_back()�������������Ԫ�ص�ʱ�򣬻��ȵ��ù��캯������һ����ʱ����Ȼ���ٵ��ÿ������캯���������ʱ������뵽�������У�
�ٽ�ԭ������ʱ������ռ�õ���Դ�����ͷţ����������ʱ����������Դ���˷ѡ�

��������ֵ���ã�ת�ƹ��캯����push_back()��ֵʱ�ͻ���ù��캯����ת�ƹ��캯��,��������ڲ����ʱ��ֱ�ӹ��죬��ֻ��Ҫ����һ�μ��ɡ������c++11 �¼ӵ�emplace_back��

��C++11��emplace_back()������������β�����һ��Ԫ�أ����Ԫ��ԭ�ع��죬����Ҫ�������������ת�ƹ��졣���ҵ�����ʽ���Ӽ�ֱ࣬�Ӹ��ݲ�����ʼ����ʱ����ĳ�Ա��

�÷���push_back()����һ�������ǲ���Ҫ�������������ת�ƹ���
*/
#if 0
int main()
{
	vector<int> vec;	
	//vec.reserve(20);	//������vector����Ԥ���ռ�
	vec.resize(20);

	cout << vec.empty() << endl;
	cout << vec.size() << endl;

	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}
	cout << vec.empty() << endl;
	cout << vec.size() << endl;




	//vector��operator[]��������غ���
	int size = vec.size();
	for (int i = 0; i < size; ++i)
	{
		cout << vec[i] << " ";
	}
	cout << endl;

	//��vec���������е�ż��ȫ��ɾ��
	auto it2 = vec.begin();
	while (it2 != vec.end())
	{
		if (*it2 % 2 == 0)
		{
			it2 = vec.erase(it2);
		}
		else
		{
			++it2;
		}
	}
	
	//ͨ������������vector����
	auto it1 = vec.begin();
	for (; it1 != vec.end(); ++it1)
	{
		cout << *it1 << " ";
	}
	cout << endl;

	//��vector���������е����������һ��С������1��ż��
	for (it1 = vec.begin(); it1 < vec.end(); ++it1)
	{
		if (*it1 % 2 != 0)
		{
			it1 = vec.insert(it1, *it1 - 1);
			++it1;
		}
	}
	for (it1 = vec.begin(); it1 < vec.end(); ++it1)
	{
		cout << *it1 << " ";
	}
	cout << endl;



	return 0;
}
#endif