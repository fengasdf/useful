#pragma once
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

template<typename T>
struct compare
{
	int operator()(const T&a, const T& b)
	{
		return a - b;
	}
};






template<typename K, typename T = int>
struct BStreeNode
{
	typedef BStreeNode Node;
	Node(const K key, const T value = T())
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
	{

	}

	const Node& operator=(const Node &a)
	{
		_value = a._value;
		return *this;
	}

	Node *_left;
	Node *_right;

	const K _key;
	T _value;
};


template<class K, class T = int, typename compare = compare<T>>
class BStree
{
public:
	typedef BStreeNode<K, T> Node;
	typedef BStree<K, T, compare> tree;


	tree()
		:_root(NULL)
	{}

	bool insert(const K key,const T value = T())
	{
		
		if (NULL == _root)
		{
			Node *p = new Node(key, value);
			_root = p;
		}
		else
		{
		
			pair<Node*, Node*> A = find(key,0);
			Node *father = A.second;
			if (NULL == father)
				return false;
			Node *p = new Node(key, value);
			if (compare()(key, father->_key) > 0)
				father->_right = p;
			else father->_left = p;
		}
		return true;

	}

	bool erase(const K key)
	{
		pair<Node *, Node *> A = find(key, 0);
		Node *cur = A.first;
		Node *ancestor = A.second;
		if (NULL == cur)
			return false;

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
			Node *father = cur;
			while (tmp->_left != NULL)
			{
				father = tmp;
				tmp = tmp->_left;
			}

			if (father->_left == tmp)
				father->_left = tmp->_right;
			else father->_right = tmp->_right;

			tmp->_left = cur->_left;
			tmp->_right = cur->_right;

		}
		if (NULL != ancestor)
		{
			if (cur == ancestor->_left)
				ancestor->_left = tmp;
			else ancestor->_right = tmp;
		}
		else _root = tmp;
	

		delete cur;
		
	}

	Node *find(const K key)
	{
		Node *tmp = (find(key, 0)).first;
		return tmp;
	}

	void middle_display()
	{
		middle_display(_root);
	}


	bool insertn(const K key, const T value = T())
	{
		return insertn(_root, key, value);
	}

	bool erasen(const K key)
	{
		return erasen(_root, key);
	}

	T& findn(const K key)
	{
		Node *p = findn(_root, key);
		return p->_value;
	}
protected:

	pair<Node*, Node*> find(const K key, int)
	{
		Node *cur = _root;
		Node *father = NULL;

		while (NULL != cur)
		{
			
			if (compare()(key, cur->_key) > 0)
			{
				father = cur;
				cur = cur->_right;
			}
			else if (compare()(key, cur->_key) < 0)
			{
				father = cur;
				cur = cur->_left;
			}
			else
			{
				return make_pair(cur, father);
			}
			
		}

		return make_pair(cur, father);

	}

	void middle_display( Node *root)
	{
		if (NULL == root)
		{
			return;
		}

		middle_display(root->_left);
		cout << root->_key << ends;
		middle_display(root->_right);

	}


	bool insertn(Node *&root, const K& key, const T& value)
	{
		if (NULL == root)
		{
			Node *p = new Node(key, value);
			root = p;
			return true;
		}

		if (root->_key == key)
		{
			return false;
		}

		else if (com(key, root->_key) < 0)
			insertn(root->_left, key, value);
		else insertn(root->_right, key, value);
	}

	bool erasen(Node *&root, const K& key)
	{
		if (NULL == root)
			return false;
		int flag = com(root->_key, key);
		if (flag > 0)
			erasen(root->_left, key);
		else if (flag < 0)
			erasen(root->_right, key);
		else
		{
			Node *del = root;
			if (NULL == del->_left || NULL == del->_right)
			{
				if (NULL == del->_left)
					root = del->_right;
				else root = del->_left;
			}
			else
			{
				Node *tmp = root->_right;
				Node *father = root;
				while (tmp->_left != NULL)
				{
					father = tmp;
					tmp = tmp->_right;
				}

				if (tmp == father->_left)
					father->_left = tmp->_right;
				else father->_right = tmp->_right;

				tmp->_left = del->_left;
				tmp->_right = del->_right;
				root = tmp;
			}

			
			delete del;

		}

	}

	Node* findn(Node *root, const K& key)
	{
		if (NULL == root)
			return NULL;

		int flag = com(root->_key, key);

		if (flag > 0)
			findn(root->_left, key);
		else if (flag < 0)
			finn(root->_right, key);
		else return root;
	}


private:
	Node *_root;
	compare com;
};