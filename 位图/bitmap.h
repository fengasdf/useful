#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class bitmap
{
public:
	bitmap()
	{}

	void insert(unsigned long value)
	{
		adjust(value);
		unsigned long pos = value / 32;
		unsigned long index = value % 32;
		_hp[pos] |= (1 << index);
	}

	bool find(unsigned long value)
	{
		unsigned long pos = value / 32;
		if (pos + 1 > _hp.size())
			return false;
		unsigned long index = value % 32;
		if (_hp[pos] & (1 << index))
			return true;
		else return false;
	}

	void resert(unsigned long value)
	{
		
		unsigned long pos = value / 32;
		if (pos + 1 > _hp.size())
			return;
		unsigned long index = value % 32;
		_hp[pos] &= (~(1 << index));
	}

protected:
	void adjust(unsigned long  value)
	{
		unsigned long size = value / 32 + 1;
		if (size > _hp.size())
			_hp.resize(size);

	}
private:
	vector<int> _hp;
};