#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename K, typename T = int>
struct HashListNode
{
	typedef HashListNode<T,K> Node;
	HashListNode(const K& key, const T& value = T())
		:_key(key)
		,_value(value)
		,_next(NULL)
	{

	}
	const K _key;
	T _value;
	Node *_next;
};

template<typename K>
struct Tranfroming
{
	unsigned long operator()(const K& key) const
	{
		return key;
	}
};


template<>
struct Tranfroming<string>
{
	unsigned long operator()(const string& key)
	{
		unsigned long seed = 131;
		unsigned long hash = 0;
		auto str = key.begin();
		while (*str)
		{
			hash = hash * seed + (*str++);
		}
		return (hash & 0x7fffffff);
	}
};

template<class K, class T = int, typename Tranfrom = Tranfroming<K>>
class HashTable
{
public:
	typedef HashListNode<K, T> Node;
	typedef Tranfrom Transfrom;

	HashTable()
		:_size(0)
	{
		adjust();
	}

	bool find(const K& key) const
	{
		return find(key, GetPos(key));
	}

	bool insert(const K& key, const T& value = int())
	{
		int pos = GetPos(key);
		if (find(key, pos))
			return false;
		//调整大小
		_size++;

		//插入
		Node *p = new Node(key, value);

		p->_next = _hp[pos];
		_hp[pos] = p;
		return true;
	}

	bool remove(const K& key)
	{
		unsigned long pos = GetPos(key);
		Node *pre = NULL;
		Node *p = _hp[pos];

		while (NULL != p && p->_key != key)
		{
			pre = p;
			p = p->_next;
			
		}
		if (NULL == p)
			return false;

		if (NULL == pre)
		{
			_hp[pos] = p->_next;
		}
		else
		{
			pre->_next = p->_next;
		}

		delete p;
		_size--;
		return true;
	}


protected:
	int GetPos(const K& key) const
	{
		return  ( Transfrom()(key) % (_hp.size()) );
	}

	bool find(const K& key, unsigned long pos) const
	{
		Node *p = _hp[pos];
		while (p)
		{
			p = p->_next;
			if (p && p->_key == key)
				return true;
		}
		return false;
	}

	void adjust()
	{
		if (_size == _hp.size())
		{
			_hp.resize(GetPrime(_size));
		}
	}

	unsigned long GetPrime(unsigned long size)
	{
		const int _PrimeSize = 28;    
		static const unsigned long _PrimeList[_PrimeSize] =
		{
		53ul,         97ul,         193ul,       389ul,
		769ul,        1543ul,       3079ul,       6151ul,
		12289ul,     24593ul,        49157ul,      98317ul,
		196613ul,    393241ul,    786433ul,        1572869ul,
		3145739ul,    6291469ul,   12582917ul,  25165843ul,
		50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
		1610612741ul, 3221225473ul, 4294967291ul
		};

		for (int i = 0; i < _PrimeSize; i++)
		{
			if (size < _PrimeList[i])
				return _PrimeList[i];
		}
		return _PrimeList[27];

	}

private:
	vector<Node *> _hp;
	unsigned long _size;

};