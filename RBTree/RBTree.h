#include"iostream"
using namespace std;
enum Color
{
	RED,
	BLACK
};
template<class K, class V>struct RBTreeNode
{
	K _key;
	V _value;
	RBTreeNode<K, V>*_left;
	RBTreeNode<K, V>*_right;
	RBTreeNode<K, V>*_parent;
	Color _color;
	RBTreeNode(const K&key, const V&value) :_key(key), _value(value), _left(NULL), _right(NULL), _parent(NULL), _color(RED)
	{}
};
template<class K, class V>class RBTree
{
	typedef RBTreeNode<K, V> Node;
protected:
	Node* _root;
public:
	RBTree() :_root(NULL)
	{}
	bool Insert(const K&key, const V&value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_color = BLACK;
			return true;
		}
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(key, value);
		cur->_parent = parent;
		if (parent->_key < key)
			parent->_right = cur;
		else
			parent->_left = cur;
		while (cur != _root && parent->_color == RED)
		{
			//保证有父亲和祖父
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				if (uncle&&uncle->_color == RED)
				{
					//情况一
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					//继续向上调整
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					//uncle 不在或者uncle为黑
					if (parent->_right == cur)
					{
						//情况3
						_RotateL(parent);
						//第一次旋转完成后更新parent和cur
						swap(parent, cur);
					}
					_RotateR(grandfather);
					grandfather->_color = RED;
					parent->_color = BLACK;
					break;
				}
			}
			else
			{
				//grandfather ->right==parent
				Node*uncle = grandfather->_left;
				if (uncle && uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					//uncle 不存在或者uncle为黑色
					if (parent->_left == cur)
					{
						_RotateR(parent);
						swap(parent, cur);
					}
					_RotateL(grandfather);
					grandfather->_color = RED;
					parent->_color = BLACK;
					break;
				}
			}
		}
		_root->_color = BLACK;
		return true;
	}
	bool Find(const K&key)
	{
		if (_root == NULL)
			return false;
		Node*cur = _root;
		while (cur)
		{
			if (cur->_key < key)
				cur = cur->_right;
			else if (cur->_key>key)
				cur = cur->_left;
			else
				return true;
		}
		return false;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	bool IsRBTree()
	{
		if (_root == NULL)
			return true;
		if (_root->_color == RED)
			return false; //根颜色须为黑色
		int count = 0;
		Node*cur = _root;
		while (cur)
		{
			if (cur->_color == BLACK)
				count++;
			cur = cur->_left;
		}
		int k = 0;
		return _IsRBTree(_root, count, k);
	}
	~RBTree()
	{
		_Destroy(_root);
	}
 protected:
	 bool _IsRBTree(Node*root, const int count, int k)
	 {
		 if (root == NULL)
			 return true;
		 if (root->_color == RED&&root->_color == RED)
		 {
			 cout << "存在连续的红节点：" << root->_parent->_color << endl;
			 return false;
		 }
		 if (root->_color == BLACK)
			 ++k;
		 if (root->_left == NULL && root->_right == NULL)
		 {
			 if (count != k)
			 {
				 cout << "黑色节点数量不等！" << root->_key << endl;
				 return false;
			 }
		 }
		 return _IsRBTree(root->_left, count, k) && _IsRBTree(root->_right, count, k);
	 }
	 void _RotateL(Node*parent)
	 {
		 Node*subR = parent->_right;
		 Node*subRL = subR->_left;
		 parent->_right = subRL;
		 if (subRL)
			 subRL->_parent = parent;
		 subR->_left = parent;
		 Node*ppNode = parent->_parent;
		 parent->_parent = subR;
		 if (ppNode == NULL)
		 {
			 _root = subR;
			 subR->_parent = NULL;
		 }
		 else
		 {
			 if (ppNode->_left == parent)
				 ppNode->_left = subR;
			 else
				 ppNode->_right = subR;
			 subR->_parent = ppNode;
		 }
	 }
	 void _RotateR(Node*parent)
	 {
		 Node*subL = parent->_left;
		 Node*subLR = subL->_right;
		 parent->_left = subLR;
		 if (subLR)
			 subLR->_parent = parent;
		 subL->_right = parent;
		 Node*ppNode = parent->_parent;
		 parent->_parent = subL;
		 if (ppNode == NULL)
		 {
			 _root = subL;
			 subL->_parent = NULL;
		 }
		 else
		 {
			 if (ppNode->_left == parent)
				 ppNode->_left = subL;
			 else
				 ppNode->_right = subL;
			 subL->_parent = ppNode;
		 }
	 }
	 void _InOrder(Node*root)
	 {
		 if (root == NULL)
			 return;
		 _InOrder(root->_left);
		 cout << root->_key << " ";
		 _InOrder(root->_right);
	 }
	 void _Destroy(Node*&root)
	 {
		 if (root == NULL)
			 return;
		 Node*cur = root;
		 if (cur)
		 {
			 _Destroy(cur->_left);
			 _Destroy(cur->_right);
			 delete cur;
			 cur = NULL;
		 }
	 }
};