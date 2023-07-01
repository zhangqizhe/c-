#include<iostream>
#include<cmath>
using namespace std;

//AVL
template<typename T> 
class AVLTree
{
public:
	AVLTree():root_(nullptr) {}
	
	//AVL���Ĳ������
	void insert(const T& val)
	{
		root_ = insert(root_, val);
	}
	//ɾ������
	void remove(const T& val)
	{
		root_ = remove(root_, val);
	}
private:
	struct Node
	{
		Node(T data=T())
			:left_(nullptr)
			,right_(nullptr)
			,height(1)
		{ }
	
		T data_;
		Node* left_;
		Node* right_;
		int height_;	//��¼�ڵ�ĸ߶�ֵ
	};

	//���ؽڵ�ĸ߶�ֵ
	int height(Node* node)
	{
		return node == nullptr ? 0 : node->height_;
	}

	//����ת����	�Բ���nodeΪ��������ת�����������µĸ��ڵ㷵��
	Node* rightRotate(Node* node)
	{
		//�ڵ���ת
		Node* child = node->left_;
		node->left_ = child->right_;
		child->right_ = node;
		//�߶ȸ���		��node ��child
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;
		//������ת��������µĸ��ڵ�
		return child;
	}

	//����ת����	�Բ���nodeΪ��������ת�����������µĸ��ڵ㷵��
	Node* leftRotate(Node* node)
	{
		//�ڵ���ת
		Node* child = node->right_;
		node->right_ = child->left_;
		child->left_ = node;
		//�߶ȸ���		��node ��child
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;
		//������ת��������µĸ��ڵ�
		return child;
	}

	//��ƽ����� �Բ���nodeΪ������-����ת�����������µĸ��ڵ㷵��
	Node* leftBalance(Node* node)
	{
		node->left_ = leftRotate(node->left_);
		return rightRotate(node);
	}

	//��ƽ����� �Բ���nodeΪ������-����ת�����������µĸ��ڵ㷵��
	Node* rightBalance(Node* node)
	{
		node->right_ = rightRotate(node->right_);
		return leftRotate(node);
	}

	//AVL���Ĳ������
	Node* insert(Node* node, const T& val)
	{
		if (node == nullptr)	//�ݹ�������ҵ�����λ��
		{
			new Node(val);
		}
		if (node->data_ > val)
		{
			node->left_ = insert(node->left_, val);
			//���1 �ڵݹ���ݵ�ʱ���жϽڵ��Ƿ�ʧ��	node��������̫���� nodeʧ����
			if (height(node->left_) - height(node->right_) > 1)
			{
				if (height(node->left_->left_) >= height(node->left_->right_))
				{
					//�ڵ�ʧ�⣬�������ӵ�������̫����
					node = rightRotate(node);
				}
				else
				{
					//�ڵ�ʧ�⣬�������ӵ�������̫����
					node = leftBalance(node);
				}
			}
		}
		else if (node->data_ < val)
		{
			node->right_ = insert(node->right_, val);
			//���2 �ڵݹ���ݵ�ʱ���жϽڵ��Ƿ�ʧ��	node��������̫���� nodeʧ����
			if (height(node->right_) - height(node->left_) > 1)
			{
				if (height(node->right_->right_) >= height(node->right_->left_))
				{
					//�ڵ�ʧ�⣬�����Һ��ӵ�������̫����
					node = leftRotate(node);
				}
				else
				{
					//�ڵ�ʧ�⣬�����Һ��ӵ�������̫����
					node = rightBalance(node);
				}
			}
			else
			{
				;	//��ʾ�ҵ���ͬ�ڵ㣬���������µݹ��ˣ�ֱ�����ϻ���
			}
			//���3 ��Ϊ�������������µĽڵ�  �ڵݹ����ʱ�����½ڵ�߶�
			node->height_ = max(height(node->left_), height(node->right_)) + 1;
			return node;
		}	
	}
	
	//ɾ������ʵ��
	Node* remove(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (node->data_ > val)
		{
			node->left_ = remove(node->left_, val);
			//������ɾ���ڵ㣬�������������̫��
			if (heigh(node->right_) - height(node->left_) > 1)
			{
				if (height(node->right_->right_) >= height(node->right_->left_))
				{
					//�Һ��ӵ�������̫��
					node = leftRotate(node);
				}
				else
				{
					//�Һ��ӵ�������̫��
					node = rightBalance(node);
				}
			}
		}
		else if (node->data_ < val)
		{
			node->right_ = remove(node->right_, val);
			//������ɾ���ڵ㣬���ܵ���������̫��
			if (height(node->left_) - height(node->right_) > 1)
			{
				if (height(node->left_->left_) >= height(node->left_->right_))
				{
					//���ӵ�������̫��
					node = rightRotate(node);
				}
				else
				{
					//���ӵ�������̫��
					node = leftBalance(node); 
				}
			}
		}
		else
		{
			//�ҵ��ˣ��ȴ������������ӵĽڵ�ɾ�����
			if (node->left_ != nullptr && node->right_ != nullptr)
			{
				//Ϊ�˱���ɾ��ǰ�����ߺ�̽ڵ���ɽڵ�ʧ�⣬˭��ɾ��˭
				if (height(node->left_) >= height(node->right_))
				{
					//ɾǰ��
					Node* pre = node->left_;
					while (pre->right_ != nullptr)
						pre = pre->right_;
					node->data_ = pre->data_;
					node->left_ = remove(node->left_, pre->data_);//ɾǰ���ڵ�
				}
				else
				{
					Node* post = node->right_;
					while (post->left_ != nullptr)
						post = post->left_;
					node->data_ = post->data_;
					node->right_ = remove(node->right_, post->data_);//ɾ����̽ڵ�
				}
			}
			else  //ɾ���ڵ㣬�����һ������
			{
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
				else
				{
					return nullptr;
				}
			}
		}
		//���½ڵ�߶�
		node->height_ = max(height(node->left_), height(node->right_)) + 1;

		return node;	//�ݹ���ݹ����У��ѵ�ǰ�ڵ�����ڵ㷵��
	}
	
	
	Node* root_;	//ָ����ڵ�
};

//����AVL���ڵ�����


#if 0
int main()
{

	return 0;
}
#endif