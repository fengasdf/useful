#pragma once

#include <iostream>
#include <stack>

using namespace std;

template<typename K, typename T = int>
struct AVLNode
{
	typedef AVLNode<K, T> Node;

	AVLNode(const K& key, const T value = T())
		:_key(key)
		,_value(value)
		,_br(0)
		,_left(NULL)
		,_right(NULL)
		,_father(NULL)
	{

	}

	const K _key;
	T _value;
	int _br;
	Node *_left;
	Node *_right;
	Node *_father;
};



template<class K, class T = int>
class AVLtree
{
public:


	typedef AVLtree<K, T> tree;
	typedef AVLNode<K, T> Node;

	AVLtree()
		:_root(NULL)
	{};

	bool insert(const K& key, const T& value = T())
	{
		Node *p = new Node(key, value);
		if (NULL == _root)
		{
			_root = p;
			return true;
		}
		Node *cur    = _root;
		Node *father = cur;

		while (cur)
		{
			father = cur;
			if (key == cur->_key)
				return false;
			else if (key > cur->_key)
				cur = cur->_right;
			else cur = cur->_left;

		}
		if (father->_key > key)
			father->_left = p;
		else father->_right = p;
		p->_father = father;

		adjust(p);
		return true;

		

	}

	bool erase(const K key)
	{
		Node *cur = _root;

		while (cur && cur->_key != key)
		{
			if (cur->_key > key)
				cur = cur->_left;
			else cur = cur->_right;
		}

		if (NULL == cur)
			return false;
		Node *father = cur->_father;
		Node *tmp = NULL;
		if (NULL == cur->_left || NULL == cur->_right)
		{
			if (NULL == cur->_left)
				tmp = cur->_right;
			else tmp = cur->_left;
		}
		else
		{
			tmp = cur->_right;
			while (tmp->_left != NULL)
			{
				tmp = tmp->_left;
			}

			if (tmp->_father->_left == tmp)
				tmp->_father->_left = tmp->_right;
			else tmp->_father->_left = tmp->_left;
		}

		if (NULL == father)
		{
			_root = tmp;
		}
		else
		{
			if (father->_left == cur)
				father->_left = tmp;
			else father->_right = tmp;

		}
		delete cur;
	}

	void middle_display()
	{
		middle_display(_root);

	}

protected:
	void rotate_left(Node *father)
	{
		Node *grandfather = father->_father;
		Node *great_father = grandfather->_father;

		grandfather->_right = father->_left;
		if (father->_left != NULL)
			father->_left->_father = grandfather;

		father->_left = grandfather;
		grandfather->_father = father;

		if (NULL == great_father)
		{
			_root = father;
			
		}
		else 
		{
			if (great_father->_left == grandfather)
				great_father->_left = father;
			else great_father->_right = father;

		}
		father->_father = great_father;

	}

	void rotate_right(Node *father)
	{
		Node *grandfather = father->_father;
		Node *great_father = grandfather->_father;

		grandfather->_left = father->_right;
		if (father->_right != NULL)
			father->_right->_father = grandfather;

		father->_right = grandfather;
		grandfather->_father = father;

		if (NULL == great_father)
		{
			_root = father;
			_root->_father = NULL;
		}
		else
		{
			if (great_father->_left == grandfather)
				great_father->_left = father;
			else great_father->_right = father;
		}
		father->_father = great_father;
	}

	void adjust(Node *father, Node *grandfather)
	{

		if (2 == grandfather->_br)//进行左旋转
		{
			if (-1 == father->_br)//须先进行右旋转
			{
				father = father->_left;
				rotate_right(father);
				
			}

			rotate_left(father);

		}
		else if (-2 == grandfather->_br)//进行右旋转
		{
			if (1 == father->_br)//须先进行左旋转
			{
				father = father->_right;
				rotate_left(father);
				
			}

			rotate_right(father);
		   
		}

	}
	void adjust(Node *child)
	{
		Node *father = child->_father;

		while (child != _root)
		{
			if (father->_left == child)
				father->_br -= 1;
			else father->_br += 1;

			if (0 == father->_br)
				break;
			else if (1 == father->_br || -1 == father->_br)
			{
				child = father;
				father = father->_father;
				
			}
			else
			{
				adjust(child, father);
				child->_br = father->_br = 0;
				break;
			}
		}
	}

	void middle_display(Node *root)
	{
		if (NULL == root)
			return;
		middle_display(root->_left);
		cout << root->_key << endl;

		middle_display(root->_right);
	}

	void height()
	{
		stack<int> A;

	}

	int height(Node *root, stack<int> & A)
	{
		if (NULL == root)
			return 0;

		int max = height(root->left);
		max = std::max(max, height(root->_right));
	}
private:
	
	Node *_root;
};