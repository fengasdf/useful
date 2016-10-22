#pragma once
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;



template<class T, class Compare>
class Plie
{

public:
	Plie() {};
	Plie(const vector<T>& A)
		:_dp(A)
	{
		SetUp();
	}


	void push( const T& a)
	{
		_dp.push_back(a);
		adjust();

	}

	void Sort()
	{
		int size = _dp.size();
		while (size > 0)
		{
			std::swap(_dp[0], _dp[size-1]);
			size--;
			UpDown(0, size);
		}

	}

	const T& top()
	{
		return _dp[0];
	}

	void pop()
	{
		int size = _dp.size();
		assert(size);
		std::swap(_dp[0], _dp[size - 1]);
		_dp.pop_back();
		UpDown(0, size-1);

	}
	size_t size()
	{
		return _dp.size();
	}


	bool empty()
	{
		return _dp.empty();
	}

	void clear()
	{
		_dp.clear();
	}

protected:
	void SetUp()
	{
		int size = _dp.size();
			
		for (int i = (size) / 2 - 1; i >= 0; i--)
		{
			UpDown(i, size);
		}


	}

	void adjust()
	{
		int pos = _dp.size() - 1;
		int i = 0;

		while (pos > 0)
		{
			i = (pos - 1) / 2;
			if (Compare()(_dp[pos], _dp[i]))
			{
				std::swap(_dp[pos], _dp[i]);
				pos = i;
				
			}
			else break;
		}
		
	}

	void UpDown(int pos, int size)
	{
		while ((2 * pos)+1 < size)
		{
			int tmp = 2 * pos + 1;
			if (tmp + 1 < size && Compare()(_dp[tmp+1], _dp[tmp]))
				tmp++;
			if (Compare()(_dp[tmp], _dp[pos]))
			{
				std::swap(_dp[tmp], _dp[pos]);
				pos = tmp;
			}
			else break;
		}

	}
private:
	vector<T> _dp;
};


