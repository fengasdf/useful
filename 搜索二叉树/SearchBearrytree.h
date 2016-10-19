#pragma once
#include <iostream>
#include <utility>
using namespace std;

template<typename T>
struct compare
{
	int operator(const T&a, const T& b)
	{
		return a - b;
	}
};






template<typename K, typename T>
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

	Node *_left;
	Node *_right;

	K _key;
	T _value;
};


template<class K, class T, typename compare = compare<T>>
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
		
			pair<Node*, Node*> A = find(key);
			Node *father = A.second;
			if (NULL == father)
				return false;
			Node *p = new Node(key, value);
			if (_com(key, father->_key))
				father->_right = p;
			else father->_left = p;
		}
		return true;

	}

	bool erase(const K key)
	{
		pair<Node *, Node *> A = find(key);

		Node *cur = A.first;
		if (NULL == cur)
			return false;

		cur = cur->_right;
		Node *father = A.second;
		if (cur)
		{
			if (father->_left == cur)
			{
				father->_left = cur->_left;
			}
			else father->_right = cur->_right;
		}

		else
		{
			Node *pather = NULL;
			while (NULL != cur->left)
			{
				pather = cur;
				cur = cur->_left;
			}
			(A.first)->_value = cur->_value;
			erase(pather, cur);
		}
		return true;
	}


protected:
	void erase(Node *father, Node *child)
	{
		if (father->_right == child)
		{
			father->_right = child->_right;
		}

		if (father->_left == child)
		{
			fater->left = child->_right;
		}

		delete child;
	}

	pair<Node*, Node*> find(const K key)
	{
		Node *cur = _root;
		Node *father = NULL;

		while (NULL != cur)
		{
			father = cur;
			if (compare()(key, cur->_key) > 0)
			{
				cur = cur->_right;
			}
			else if (compare()(key, cur->_key) < 0)
			{
				cur = cur->_left;
			}
			else return make_pair(NULL, NULL);
		}

		return make_pair(cur, father);

	}

private:
	Node *_root;
};