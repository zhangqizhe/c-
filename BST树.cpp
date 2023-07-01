#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include<cmath>
using namespace std;

//BST������ʵ��
template<typename T,typename Comp=less<T>>
class BSTree
{
public:
	//��ʼ�����ڵ�ͺ�������
	BSTree(Comp comp = Comp())
		:root_(nullptr)
		,comp_(comp)
	{ }
	//�������˼���ͷ�BST�����нڵ���Դ
	~BSTree()
	{
		if (root_ != nullptr)
		{
			queue<Node*> s;
			s.push(root_);
			while (!s.empty())
			{
				Node* front = s.front();
				s.pop();

				if (front->left_ != nullptr)
				{
					s.push(front->left_);
				}
				if (front->right_ != nullptr)
				{
					s.push(front->right_);
				}
				delete front;
			}
		}
	}
	//�ǵݹ�������
	void n_insert(const T& val)
	{
		//��Ϊ��,���ɸ��ڵ�
		if (root_ == nullptr)
		{
			root_ = new Node(val);
			return;
		}
		//�������ʵĲ���λ��,��¼���ڵ��λ��
		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				//������Ԫ����ͬ��ֵ
				return;
			}
			else if (comp_(cur->data_, val))	//С�ڹ�ϵ
			{
				parent = cur;
				cur = cur->right_;
			}
			else	//���ڹ�ϵ
			{
				parent = cur;
				cur = cur->left_;
			}
		}
		//���½ڵ���뵽parent�ڵ�ĺ�����
		if (comp_(val, parent->data_))
		{
			parent->left_ = new Node(val);
		}
		else
		{
			parent->right_ = new Node(val);
		}
	}
	//�ݹ�������
	void insert(const T& val)
	{
		root_ = insert(root_, val);
	}
	//�ǵݹ�ɾ������
	void n_remove(const T& val)
	{
		if (root_ == nullptr)
		{
			return;
		}
		//������ɾ���ڵ�
		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				break;//�ҵ���ɾ���ڵ�
			}
			else if (comp_(cur->data_, val))
			{
				parent = cur;
				cur = cur->right_;
			}
			else  // >= false
			{
				parent = cur;
				cur = cur->left_;
			}
		}
		//û�ҵ���ɾ���ڵ�
		if (cur == nullptr)
		{
			return;
		}
		//��ɾ���ڵ��������ӽڵ�(�����)
		if (cur->left_ != nullptr && cur->right_ != nullptr)
		{
			parent = cur;
			Node* pre = cur->left_;
			while (pre->right_ != nullptr)
			{
				parent = pre;
				pre = pre->right_;
			}
			cur->data_ = pre->data_;
			cur = pre;	//��curָ��ǰ���ڵ�,ת����1,2
		}

		//curָ��ɾ���ڵ�,parentָ���丸�ڵ�
		//ͳһ�����ɾ���ڵ�ֻ��һ���ӽڵ�(�����)����û���ӽڵ�(���һ)
		Node* child = cur->left_;
		if (child == nullptr)
		{
			child = cur->right_;
		}

		if (parent == nullptr)	//������� ��ʾɾ�����Ǹ��ڵ�
		{
			root_ = child;
		}
		else
		{
			//�Ѵ�ɾ���ڵ�ĺ���(nullptr���߲���)д���丸�ڵ���Ӧ�ĵ�ַ����
			if (parent->left_ == cur)
			{
				parent->left_ = child;
			}
			else
			{
				parent->right_ = child;
			}
		}
		
		delete cur;	//ɾ����ǰ�ڵ�
	}
	//�ݹ�ɾ������
	void remove(const T& val)
	{
		root_ = remove(root_);
	}
	//�ǵݹ��ѯ����
	bool non_query(const T& val)
	{
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				return true;
			}
			else if (comp_(cur->data, val))
			{
				cur = cur->right_;
			}
			else
			{
				cur = cur->left_;
			}
		}
		return false;
	}
	//�ݹ��ѯ����
	bool query(const T& val)
	{
		return nullptr != query(root_, val);
	}
	//�ݹ�ǰ���������
	void preOrder()
	{
		cout << "�ݹ�:ǰ�����:";
		preOrder(root_);
		cout << endl;
	}
	//�ǵݹ�ǰ���������
	void n_preOrder()
	{
		cout << "�ǵݹ�:ǰ�����:";
		if (root_ == nullptr)
		{
			return;
		}
		stack<Node*>s;
		s.push(root_);
		while (!s.empty())
		{
			Node* top = s.top();
			s.pop();

			cout << top->data_ << " ";	//V

			if (top->right != nullptr)
			{
				s.push(top->right_);	//R
			}

			if (top->left_ != nullptr)
			{
				s.push(top->left_);		//L
			}
		}
		cout << endl;
	}
	//�ݹ������������
	void inOrder()
	{
		cout << "�ݹ�:�������:";
		inOrder(root_);
		cout << endl;
	}
	//�ǵݹ������������
	void n_inOrder()
	{
		cout << "�ǵݹ�:�������:";
		if (root_ == nullptr)
		{
			return;
		}
		stack<Node*> s;
		Node* cur = root_;
		while (cur != nullptr)
		{
			s.push(cur);
			cur = cur->left_;
		}
		while (!s.empty())
		{
			Node* top = s.top();
			s.pop();

			cout << top->data_ << " ";	

			cur = top->right_;
			if (cur != nullptr)
			{
				s.push(cur);
				cur = cur->left_;
			}
		}
		
		cout << endl;
	}
	//�ݹ�����������
	void postOrder()
	{
		cout << "�ݹ�:�������:";
		postOrder(root_);
		cout << endl;
	}
	//�ǵݹ��������
	void n_postOrder()
	{
		cout << "�ǵݹ�:�������:";
		if (root_ == nullptr)
		{
			return;
		}
		stack<Node*>s1;
		stack<Node*>s2;
		s1.push(root_);
		while (!s1.empty())
		{
			Node* top = s1.top();
			s1.pop();

			s2.push(top);
			if (top->left_ != nullptr)
			{
				s1.push(top->left_);
			}
			if (top->right_ != nullptr)
			{
				s1.push(top->right_);
			}
		}
		while (!s2.empty())
		{
			cout << s2.top()->data << " ";	
			s2.pop();
		}
		cout << endl;
	}
	//�ݹ�ʵ�ֲ������
	void levelOrder()
	{
		cout << "�ݹ�:�������:";
		int h = high();
		for (int i = 0; i < h; ++i)
		{
			levelOrder(root_, i);	//�ݹ�������Ĳ��
		}
		cout << endl;
	}
	//�ǵݹ�ʵ�ֲ������
	void n_levelOrder()
	{
		cout << "�ǵݹ�:�������:";
		if (root_ == nullptr)
		{
			return;
		}
		queue<Node*> que;
		que.push(root_);
		while (!que.empty())
		{
			Node* front = que.front();
			que.pop();

			cout << front->data_ << " ";
			if (front->left_ != nullptr)
			{
				que.push(front->left_);
			}
			if (front->right_ != nullptr)
			{
				que.push(front->right_);
			}
		}
		cout << endl;
	}
	//�ݹ������������
	int high()
	{
		return high(root_);
	}
	//�ݹ���������ڵ����
	int number()
	{
		return number(root_);
	}
	//�����������Ԫ��ֵ[i ,j]
	void findValues(vector<T>& vec, int i, int j)
	{
		findValues(root_, vec, i, j);
	}
	//�ж϶������Ƿ�ΪBST��
	bool isBSTree()
	{
		Node* pre = nullptr;
		return isBSTree(root_, pre);
	}
	//�ж���������
	bool isChildTree(BSTree<T, Comp>& child)
	{
		//�ڵ�ǰ����������child�ĸ��ڵ�
		if (root_ == nullptr)
		{
			return true;
		}

		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == child.root_->data_)
			{
				break;
			}
			else if (comp_(cur->data_, child.root_->data_))
			{
				cur = cur->right_;
			}
			else
			{
				cur = cur->left_;
			}
		}
		if (cur == nullptr)
		{
			return false;
		}
		return isChildTree(cur, child.root_);
	}
	//����������Ƚڵ�
	int getLCA(int vak1, int val2)
	{
		Node *node = getLCA(root_, val1, val2);
		if (node == nullptr)
		{
			throw "no LCA!"
		}
		else
		{
			return node->data_;
		}
	}
	//����ת
	void mirror01()
	{
		mirror01(root_);
	}
	//����Գ�
	bool mirroe02()
	{
		if (root_ == nullptr)
		{
			return true;
		}
		return mirror02(root_->left_, root_->right_);
	}
	//�ؽ�������
	void rebuild(int pre[], int i, int j, int in[], int m, int n)
	{
		root_ = _rebuild(pre, i, j, in, m, n);
	}
	//�Ӹ��ڵ���� ���ݵ�ʱ�����ʱ��ȽϺ�
	//�ж�ƽ����
	bool isBalance()
	{
		int l = 0;
		bool flag = true;
		isBalance02(root_, l);
		return flag;

	}
	//���������������k���ڵ�
	int getVal(int k)
	{
		Node* node = getVal(root_, k);
		if (node == nullptr)
		{
			string err = "no No.";
			err += k;
			throw err;
		}
		else
		{
			return node->data_;
		}
	}
private:
	//�ڵ㶨��
	struct Node
	{
		Node(T data = T())
			:data_(data)
			,left_(nullptr)
			,right_(nullptr)
		{ }
		T data_;	//������
		Node* left_;	//������
		Node* right_;	//�Һ�����
	};

	//�ݹ�ǰ�����	VLR 
	void preOrder(Node* node)
	{
		if (node != nullptr)
		{
			cout << node->data_ << " ";	//����V
			preOrder(node->left_);	//L
			preOrder(node->right_);	//R
		}
	}
	//�ݹ��������	LVR
	void inOrder(Node* node)
	{
		if (node != nullptr)
		{
			inOrder(node->left_);	//L
			cout << node->data_ << " ";	//����V
			inOrder(node->right_);	//R
		}
	}
	//�ݹ��������	LRV
	void postOrder(Node* node)
	{
		if (node != nullptr)
		{
			postOrder(node->left_);	//L
			postOrder(node->right_);	//R
			cout << node->data_ << " ";	//����V
		}
	}
	//�ݹ���������ʵ��
	void levelOrder(Node* node,int i)
	{
		if (node == nullptr)
		{
			return;
		}
		if (i == 0)
		{
			cout << node->data_ << " ";
			return;
		}
		levelOrder(node->left_, i - 1);
		levelOrder(node->right_, i - 1);
	}
	//�ݹ�ʵ������������� ����nodeΪ���ڵ�������ĸ߶Ȳ����ظ߶�ֵ
	int high(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		int left = high(node->left_);
		int right = high(node->right_);
		return left > right ? left + 1 : right + 1;
	}
	//�ݹ���������ڵ����	����nodeΪ���ڵ�����Ľڵ�����,������
	int number(Node *node) 
	{
		if (node == nullptr)
		{
			return 0;
		}
		int left = number(node->left_);
		int right = number(node->right_);
		return left + right + 1;
	}
	//�ݹ�������
	Node* insert(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			//�ݹ�������ҵ�����val��λ��,�����½ڵ㲢������ڵ�
			return new Node(val);
		}

		if (node->data_ == val)
		{
			return node;
		}
		else if (comp_(node->data_, val))
		{
			node->right_ = insert(node->right_, val);
		}
		else
		{
			node->left_ = insert(node->left_, val);
		}
		return node;
	}
	//�ݹ��ѯ����ʵ��
	Node* query(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (node->data_ == val)
		{
			return node;
		}
		else if (comp_(node->data_, val))
		{
			return query(node->right_, val);
		}
		else
		{
			return query(node->left_, val);
		}
	}
	//�ݹ�ɾ������ʵ��
	Node* remove(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (node->data_ == val)	//�ҵ���ɾ���ڵ�
		{
			//���3
			if (node->left_ != nullptr && node->right_ != nullptr)
			{
				//��ǰ���ڵ�
				Node* pre = node->left_;
				while (pre->right != nullptr)
				{
					pre = pre->right_;
				}
				node->data_ = pre->data_;
				//ͨ���ݹ�ֱ��ɾ��ǰ���ڵ�
				node->left_ = remove(node->left_, pre->data_);
			}
			else
			{
				//���1�����2
				if (node->left_ != nullptr)
				{
					Node* left = node->left_;
					delete node;
					return left;
				}
				else if (node->right_ != nullptr)
				{
					Node* right = node->right_;
					delete node;
					return right;
				}
				else //ɾ������û�к��ӵĽڵ�  Ҷ�ӽڵ�
				{
					delete node;
					return nullptr;
				}
			}
		}
		else if (comp_(node->data_, val))
		{
			node->right_ = remove(node->right_, val);
		}
		else
		{
			node->left_ = remove(node->left_, val);
		}
		return node;	//�ѵ�ǰ�ڵ㷵�ظ����ڵ�,���¸��ڵ���Ӧ�ĵ�ַ��
	}
	//�����������Ԫ��ֵ[i ,j]
	void findValues(Node *node, vector<T>& vec, int i, int j)	//�������
	{
		if (node != nullptr)
		{
			//�ڵ�ǰ�ڵ��������������
			if (node->data_ > i)
			{
				findValues(node->left_, vec, i, j);	//���ȷ������� 
			}
			
			//���ڵ�
			if (node->data_ >= i && node->data_ <= j)
			{
				vec.push_back(node->data_);
			}
			//�ڵ�ǰ�ڵ��������������
			if (node->data_ < j)
			{
				findValues(node->right_, vec, i, j);	//�Һ���
			}
		}
	}
	//�ж϶������Ƿ�ΪBST����ʵ�� �������������һ��������ص�
	bool isBSTree(Node* node, Node *&pre)//������,���Žڵ�ı���,preҪ��¼��ǰ�ڵ��ǰһ���ڵ�
	{
		if (node == nullptr)
		{
			return ture;
		}
		if (!isBSTree(node->left_, pre))	//L
		{
			return false;	//�жϵݹ����������
		}
		//V
		if (pre != nullptr)
		{
			if (comp_(node->data_, pre->data_))	//�жϵݹ����������
			{
				return false;
			}
		}
		pre = node;	//�������������ǰ���ڵ�

		return isBSTree(node->right_, pre); //R

		/*if (node->left_ != nullptr && comp_(node->data_, node->left_->data_))
		{
			return false;
		}
		if (node->right_ != nullptr && comp_(node->right_->data_, node->data_))
		{
			return false;
		}
		if (!isBSTree(node->left_))
		{
			return false;
		}

		return isBSTree(node->right_);*/
	}
	//�ж���������Ĵ���ʵ��
	bool isChildTree(Node* father, Node* child)
	{
		if (father == nullptr && child == nullptr)
		{
			return true;
		}
		if (father == nullptr)
		{
			return false;	//���������нڵ�,��ǰ������û��
		}
		if (child == nullptr)
		{
			return true;
		}

		//�ж�ֵ����ͬ
		if (father->data_ != child->data_)
		{
			return false;
		}
		return isChildTree(father->left_, child->left_)
			&& isChildTree(father->right_, child->right_);

	}
	//����������Ƚڵ�
	Node* getLCA(Node *node, int vak1, int val2)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		if (comp_(node->data_, val1) && comp_(node->data_, val2))
		{
			return getLCA(node->right_, val1, val2);
		}
		else if (comp_(val1, node->data_) && comp_(val2, node->data_))
		{
			return getLCA(node->left_, val1, val2);
		}
		else
		{
			return node;
		}
	}
	//����ת
	void mirror01(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}
		//V
		Node* tmp = node->left_;	//L
		node->left_ = node->right_;		//R
		node->right_ = tmp;

		mirror01(node->left);
		mirror01(node->right_);
	}
	//����Գ�
	bool mirroe02(Node *node1,Node *node2)
	{
		if (node1 == nullptr && node2 == nullptr)
		{
			return true;
		}
		if (node1 == nullptr || node2 == nullptr)
		{
			return false;
		}

		if (node1->data_ != node2->data_)
		{
			return false;
		}
		return mirror02(node1->left_, node2->right_)
			&& mirror02(node1->right_, node2->left_);
	}
	//�ؽ�������
	Node* _rebuild(int pre[], int i, int j, int in[], int m, int n)
	{
		if (i > j || m > n)
		{
			return nullptr;
		}

		//������ǰ�����ĸ��ڵ�
		Node* node = new Node(pre[i]);	//��ǰ��ĵ�һ�����ִ����������ڵ�
		for (int k = m; k <= n; ++k)
		{
			if (pre[i] == in[k])	//��������������������ڵ���±�k
			{
				node->left_ = _rebuild(pre��i + 1��i + (k - m), in, m, k - 1);
				node->right_ = _rebuild(pre, i + (k - m) + 1, j, in, k + 1, n);
				return node;
			}
		}
		return node;
	}
	//�ж�ƽ����
	bool isBalance(Node *node)	//Ч�ʵ�
	{
		if (node == nullptr)
			return true;
		if (!isBalance(node->left_))
			return false;
		if (!isBalance(node->right_))
			return false;

		int left = high(node->left_);
		int right = high(node->right_);
		return abs(left - right) <= 1;
	}
	//�ж�ƽ����  Ч�ʸ� �ݹ�����У���¼�˽ڵ�ĸ߶�ֵ ���ؽڵ�߶�ֵ
	bool isBalance02(Node* node, int l, bool& flag)
	{
		if (node == nullptr)
			return true;
		int left = isBalance02(node->left_, l + 1, flag);		//	L
		if (!flag)
			return left;
		int right = isBalance02(node->right_, l + 1, flag);		//	R
		if (!flag)
			return right;

		if (abs(left - right) > 1)	//�ڵ�ʧ����
		{
			flag = false;
		}
		return max(left, right);
	}
	//���������������k���ڵ�
	int i = 1;
	Node *getVal(Node *node, int k)
	{
		if (node == nullptr)
			return nullptr;
		Node *left = getVal(node->right_, k);	//R
		if (left != nullptr)
			return left;
		//V
		if (i++ == k)		//��VRL��˳���£��ҵ�������k��Ԫ��
		{
			return node;
		}
		return getVal(node->left_, k);	//L
	}

	Node* root_;	//ָ��BST���ĸ��ڵ�
	Comp comp_;	//����һ����������
};


#if 0
int main()
{
	int ar[] = { 58,24,67,0,34,62,69,5,41,64,78 };
	BSTree<int> bst;
	for (int v : ar)
	{
		bst.n_insert(v);
	}

	bst.inOrder();
	bst.postOrder();
	bst.preOrder();
	bst.levelOrder();
	cout<<bst.high()<<endl;

	cout<<bst.number()<<endl;

	vector<int> vec;
	bst.findValues(vec, 10, 60);
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;
	//bst.n_insert(12);
	//bst.n_remove(12);
	return 0;
}
#endif