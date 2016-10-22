#pragma once
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct TreeNode
{
	typedef TreeNode<T> Node;

	TreeNode() {};
	TreeNode(const T &value)
		:_value(value)
		,_left(NULL)
		,_right(NULL)
	{
		
	}
	
	T _value;

	Node *_left;
	Node *_right;

	int _lefttype;
	int _righttype;
};

template<typename T>
struct TreeIterator
{
	enum
	{
		CONNECTION,
		LINK
	};

	typedef TreeNode<T> Node;
	typedef TreeIterator<T> iterator;
	typedef T value;

	iterator()
		:node(NULL)
	{
		;
	}
	iterator(Node * p)
		:node(p)
	{
		;
	}
	iterator operator++(int)
	{
		Node *cur = node;
		if (node->_righttype == CONNECTION)
		{
			node = node->_right;
		}

		else
		{
			node = node->_right;
			while (node && node->_lefttype == LINK)
			{
				node = node->_left;
			}

		}

		return cur;

	}
	iterator operator--()
	{
		Node *cur = node;
		if (node->_lefttype == CONNECTION)
			node = node->_left;
		else
		{
			node = node->_left;
			while (node && node->_right == LINK)
			{
				node = node->_right;
			}
		}
		return cur;
	}

	value& operator*()
	{
		return node->_value;
	}

	int operator!=(iterator& i)
	{
		return node != i.node;
	}


	Node *node;
};








template<class T>
class BinarryTree
{
	typedef TreeNode<T> Node;
	typedef BinarryTree<T> Tree;
	typedef TreeIterator<T> iterator;
	enum
	{
		CONNECTION,
		LINK
	};
public:
	BinarryTree(const vector<T> &a, const int size, const T& invalue)
	{
		int pos = 0;
		_root = construct(a, size, pos, invalue);
		cueing();
	}

	BinarryTree(const Tree& a)
	{
		_root = Copy(a._root);
		cueing();
	}

	void Print()
	{
		print();
		cout << endl;
	}

	iterator begin()
	{
		Node *cur = _root;
		while (cur->_lefttype == LINK)
		{
			cur = cur->_left;
		}

		return cur;
	}

	iterator end()
	{
		return NULL;
	}

	~BinarryTree()
	{
		destory(_root);
	}
protected:
	void cueing()
	{
		Node *prev = NULL;
		cueing(_root, prev);
	}
	Node* construct(const vector<T>& a, const int size, int& pos, const T& invalue)
	{
		if (pos >= size || a[pos] == invalue)
		{
			return NULL;
		}
	
		Node *root = GetNode(a[pos]);
		root->_left = construct(a, size, ++pos, invalue);
		root->_right = construct(a, size, ++pos, invalue);
		
		if (NULL == root->_left)
			root->_lefttype = CONNECTION;
		else root->_lefttype = LINK;
		if (NULL == root->_right)
			root->_righttype = CONNECTION;
		else root->_righttype = LINK;

		return root;


	}

	Node* Copy(Node *head)
	{
		Node *new_root = GetNode(head->_value);
		if (head->_lefttype == LINK)
		new_root->_left  = Copy(head->_left);
		else new_root->_left = NULL;
		if (head->_righttype == LINK)
		new_root->_right = Copy(head->_right);
		else new_root->_right == NULL:

		new_root->_lefttype  = head->_lefttype;
		new_root->_righttype = head->_righttype;

		return new_root;
	}



	void cueing(Node* root, Node *& prev)
	{
		if (NULL == root)
			return;
		cueing(root->_left, prev);
		if (root->_lefttype == CONNECTION)
			root->_left = prev;

		if (NULL != prev && prev->_righttype == CONNECTION)
		{
			prev->_right = root;

		}

		prev = root;
		cueing(root->_right, prev);

	}
	//void cueing(Node *root, Node *&prev)
	//{
	//	if (NULL == root)
	//		return;

	//	if (root->_lefttype == CONNECTION)
	//		root->_left = prev;

	//	if (prev && prev->_righttype == CONNECTION && prev->_left != root)
	//		prev->_right = root;
	//	prev = root;

	//	if (root->_lefttype == LINK)
	//	cueing(root->_left, prev);
	//	cueing(root->_right, prev);

	//}
	Node *GetNode(const T value)
	{
		Node *p = new Node(value);
		return p;
	}

	void print()
	{
		if (NULL == _root)
			return;
		Node *cur = _root;

		while (cur)
		{
			while (cur->_lefttype == LINK)
			{
				cur = cur->_left;
			}
			
			cout << cur->_value << ends;

			while (cur && cur->_righttype == CONNECTION)
			{
				cur = cur->_right;
				if (cur)
				cout << cur->_value << ends;
				
				

			}
			if (cur)
			{
				cur = cur->_right;
			}
				


		}

	}
	//void print()
	//{
	//	if (NULL == _root)
	//		return;
	//	Node *cur = _root;
	//	while (cur)  
	//	{
	//		
	//		while (cur->_lefttype == LINK)
	//		{
	//			cout << cur->_value << ends;
	//			cur = cur->_left;
	//			
	//		}
	//		cout << cur->_value << ends;
	//		cur = cur->_right;
	//	}

	//}

	void destory(Node *root)
	{
		if (root->_lefttype == LINK)
			destory(root->_left);
		if (root->_righttype == LINK)
			destory(root->_right);
		//cout << root->_value << ends;
		delete root;
	}
private:
	Node *_root;
};