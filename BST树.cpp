#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include<cmath>
using namespace std;

//BST树代码实现
template<typename T,typename Comp=less<T>>
class BSTree
{
public:
	//初始化根节点和函数对象
	BSTree(Comp comp = Comp())
		:root_(nullptr)
		,comp_(comp)
	{ }
	//层序遍历思想释放BST树所有节点资源
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
	//非递归插入操作
	void n_insert(const T& val)
	{
		//树为空,生成根节点
		if (root_ == nullptr)
		{
			root_ = new Node(val);
			return;
		}
		//搜索合适的插入位置,记录父节点的位置
		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				//不插入元素相同的值
				return;
			}
			else if (comp_(cur->data_, val))	//小于关系
			{
				parent = cur;
				cur = cur->right_;
			}
			else	//大于关系
			{
				parent = cur;
				cur = cur->left_;
			}
		}
		//把新节点插入到parent节点的孩子上
		if (comp_(val, parent->data_))
		{
			parent->left_ = new Node(val);
		}
		else
		{
			parent->right_ = new Node(val);
		}
	}
	//递归插入操作
	void insert(const T& val)
	{
		root_ = insert(root_, val);
	}
	//非递归删除操作
	void n_remove(const T& val)
	{
		if (root_ == nullptr)
		{
			return;
		}
		//搜索待删除节点
		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				break;//找到待删除节点
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
		//没找到待删除节点
		if (cur == nullptr)
		{
			return;
		}
		//待删除节点有两个子节点(情况三)
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
			cur = pre;	//让cur指向前驱节点,转化成1,2
		}

		//cur指向删除节点,parent指向其父节点
		//统一处理待删除节点只有一个子节点(情况二)或者没有子节点(情况一)
		Node* child = cur->left_;
		if (child == nullptr)
		{
			child = cur->right_;
		}

		if (parent == nullptr)	//特殊情况 表示删除的是根节点
		{
			root_ = child;
		}
		else
		{
			//把待删除节点的孩子(nullptr或者不空)写入其父节点相应的地址域中
			if (parent->left_ == cur)
			{
				parent->left_ = child;
			}
			else
			{
				parent->right_ = child;
			}
		}
		
		delete cur;	//删除当前节点
	}
	//递归删除操作
	void remove(const T& val)
	{
		root_ = remove(root_);
	}
	//非递归查询操作
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
	//递归查询操作
	bool query(const T& val)
	{
		return nullptr != query(root_, val);
	}
	//递归前序遍历操作
	void preOrder()
	{
		cout << "递归:前序遍历:";
		preOrder(root_);
		cout << endl;
	}
	//非递归前序遍历操作
	void n_preOrder()
	{
		cout << "非递归:前序遍历:";
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
	//递归中序遍历操作
	void inOrder()
	{
		cout << "递归:中序遍历:";
		inOrder(root_);
		cout << endl;
	}
	//非递归中序遍历操作
	void n_inOrder()
	{
		cout << "非递归:中序遍历:";
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
	//递归后序遍历操作
	void postOrder()
	{
		cout << "递归:后序遍历:";
		postOrder(root_);
		cout << endl;
	}
	//非递归后续遍历
	void n_postOrder()
	{
		cout << "非递归:后序遍历:";
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
	//递归实现层序遍历
	void levelOrder()
	{
		cout << "递归:层序遍历:";
		int h = high();
		for (int i = 0; i < h; ++i)
		{
			levelOrder(root_, i);	//递归调用树的层次
		}
		cout << endl;
	}
	//非递归实现层序遍历
	void n_levelOrder()
	{
		cout << "非递归:层序遍历:";
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
	//递归求二叉树层数
	int high()
	{
		return high(root_);
	}
	//递归求二叉树节点个数
	int number()
	{
		return number(root_);
	}
	//求满足区间的元素值[i ,j]
	void findValues(vector<T>& vec, int i, int j)
	{
		findValues(root_, vec, i, j);
	}
	//判断二叉树是否为BST树
	bool isBSTree()
	{
		Node* pre = nullptr;
		return isBSTree(root_, pre);
	}
	//判断子树问题
	bool isChildTree(BSTree<T, Comp>& child)
	{
		//在当前二叉树上找child的根节点
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
	//最近公共祖先节点
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
	//镜像翻转
	void mirror01()
	{
		mirror01(root_);
	}
	//镜像对称
	bool mirroe02()
	{
		if (root_ == nullptr)
		{
			return true;
		}
		return mirror02(root_->left_, root_->right_);
	}
	//重建二叉树
	void rebuild(int pre[], int i, int j, int in[], int m, int n)
	{
		root_ = _rebuild(pre, i, j, in, m, n);
	}
	//从根节点遍历 回溯的时候检测的时候比较好
	//判断平衡树
	bool isBalance()
	{
		int l = 0;
		bool flag = true;
		isBalance02(root_, l);
		return flag;

	}
	//求中序遍历倒数第k个节点
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
	//节点定义
	struct Node
	{
		Node(T data = T())
			:data_(data)
			,left_(nullptr)
			,right_(nullptr)
		{ }
		T data_;	//数据域
		Node* left_;	//左孩子域
		Node* right_;	//右孩子域
	};

	//递归前序遍历	VLR 
	void preOrder(Node* node)
	{
		if (node != nullptr)
		{
			cout << node->data_ << " ";	//操作V
			preOrder(node->left_);	//L
			preOrder(node->right_);	//R
		}
	}
	//递归中序遍历	LVR
	void inOrder(Node* node)
	{
		if (node != nullptr)
		{
			inOrder(node->left_);	//L
			cout << node->data_ << " ";	//操作V
			inOrder(node->right_);	//R
		}
	}
	//递归中序遍历	LRV
	void postOrder(Node* node)
	{
		if (node != nullptr)
		{
			postOrder(node->left_);	//L
			postOrder(node->right_);	//R
			cout << node->data_ << " ";	//操作V
		}
	}
	//递归层序遍历的实现
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
	//递归实现求二叉树层数 求以node为根节点的子树的高度并返回高度值
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
	//递归求二叉树节点个数	求以node为根节点的树的节点总数,并返回
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
	//递归插入操作
	Node* insert(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			//递归结束，找到插入val的位置,生成新节点并返回其节点
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
	//递归查询操作实现
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
	//递归删除操作实现
	Node* remove(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (node->data_ == val)	//找到待删除节点
		{
			//情况3
			if (node->left_ != nullptr && node->right_ != nullptr)
			{
				//找前驱节点
				Node* pre = node->left_;
				while (pre->right != nullptr)
				{
					pre = pre->right_;
				}
				node->data_ = pre->data_;
				//通过递归直接删除前驱节点
				node->left_ = remove(node->left_, pre->data_);
			}
			else
			{
				//情况1和情况2
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
				else //删除的是没有孩子的节点  叶子节点
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
		return node;	//把当前节点返回给父节点,更新父节点相应的地址域
	}
	//求满足区间的元素值[i ,j]
	void findValues(Node *node, vector<T>& vec, int i, int j)	//中序遍历
	{
		if (node != nullptr)
		{
			//在当前节点的左子树中搜索
			if (node->data_ > i)
			{
				findValues(node->left_, vec, i, j);	//优先访问左孩子 
			}
			
			//根节点
			if (node->data_ >= i && node->data_ <= j)
			{
				vec.push_back(node->data_);
			}
			//在当前节点的右子树中搜索
			if (node->data_ < j)
			{
				findValues(node->right_, vec, i, j);	//右孩子
			}
		}
	}
	//判断二叉树是否为BST树的实现 利用中序遍历是一个升序的特点
	bool isBSTree(Node* node, Node *&pre)//传引用,随着节点的遍历,pre要记录当前节点的前一个节点
	{
		if (node == nullptr)
		{
			return ture;
		}
		if (!isBSTree(node->left_, pre))	//L
		{
			return false;	//判断递归结束的条件
		}
		//V
		if (pre != nullptr)
		{
			if (comp_(node->data_, pre->data_))	//判断递归结束的条件
			{
				return false;
			}
		}
		pre = node;	//更新中序遍历的前驱节点

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
	//判断子树问题的代码实现
	bool isChildTree(Node* father, Node* child)
	{
		if (father == nullptr && child == nullptr)
		{
			return true;
		}
		if (father == nullptr)
		{
			return false;	//子树里面有节点,当前二叉树没有
		}
		if (child == nullptr)
		{
			return true;
		}

		//判断值不相同
		if (father->data_ != child->data_)
		{
			return false;
		}
		return isChildTree(father->left_, child->left_)
			&& isChildTree(father->right_, child->right_);

	}
	//最近公共祖先节点
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
	//镜像翻转
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
	//镜像对称
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
	//重建二叉树
	Node* _rebuild(int pre[], int i, int j, int in[], int m, int n)
	{
		if (i > j || m > n)
		{
			return nullptr;
		}

		//创建当前子树的根节点
		Node* node = new Node(pre[i]);	//拿前序的第一个数字创建子树根节点
		for (int k = m; k <= n; ++k)
		{
			if (pre[i] == in[k])	//在中序遍历中找子树根节点的下标k
			{
				node->left_ = _rebuild(pre，i + 1，i + (k - m), in, m, k - 1);
				node->right_ = _rebuild(pre, i + (k - m) + 1, j, in, k + 1, n);
				return node;
			}
		}
		return node;
	}
	//判断平衡树
	bool isBalance(Node *node)	//效率低
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
	//判断平衡树  效率高 递归过程中，记录了节点的高度值 返回节点高度值
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

		if (abs(left - right) > 1)	//节点失衡了
		{
			flag = false;
		}
		return max(left, right);
	}
	//求中序遍历倒数第k个节点
	int i = 1;
	Node *getVal(Node *node, int k)
	{
		if (node == nullptr)
			return nullptr;
		Node *left = getVal(node->right_, k);	//R
		if (left != nullptr)
			return left;
		//V
		if (i++ == k)		//在VRL的顺序下，找到正数第k个元素
		{
			return node;
		}
		return getVal(node->left_, k);	//L
	}

	Node* root_;	//指向BST树的根节点
	Comp comp_;	//定义一个函数对象
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