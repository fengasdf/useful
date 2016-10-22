#pragma once
#include <map>
#include <queue>
#include <set>
#include <string>
#include "pile.h"



#define MaxTran 2097152


struct HuffNode
{
	typedef HuffNode Node;
	HuffNode()
		:_c(0)
		, _left(NULL)
		, _right(NULL)
		, _time(0)
		, _parent(NULL)
	{};

	HuffNode(const char c, const size_t time)
		:_c(c)
		, _left(NULL)
		, _right(NULL)
		, _time(time)
		, _parent(NULL)

	{


	}


	Node *_left;
	Node *_right;
	unsigned long   _time;
	unsigned char _c;
	Node *_parent;


};

template<typename T>
struct compare
{

	bool operator()(const T&a, const T&b)
	{
		return a->_time < b->_time;
	}

};


struct hufffz
{
	typedef HuffNode Node;
	typedef unsigned char uchar;
	FILE *trans(const string str)
	{
		errno_t error;
		FILE* file;
		error = fopen_s(&file, str.c_str(), "r");
		if (error)
		{
			throw 1;
		}
		Node *root = NULL;

		Plie<Node*, compare<Node *>> d;
		vector<unsigned long > count(256, 0);
		map<int, string> contrast;
		//统计字符次数
		int va;
		while ((va = fgetc(file)) != EOF)
		{
			count[va]++;
		}

		//将出现过的字符转化为Node
		for (int i = 0; i < 256; i++)
		{
			if (count[i] != 0)
			{
				Node *p = new Node(i, count[i]);
				d.push(p);
			}
		}
		//构建哈夫曼树
		root = construct(d);
		//记录字符所对应的新编码
		Tran(root, contrast);
		//将原文件字符每个对应的新编码打入到A中， 当A的size到达一定大小时进行转换，把转换后的数写入到新文件中，
		//新文件名为原文件名+code;
		size_t pos = str.rfind('.');
		string s = str.substr(0, pos);
		string s1 = s + "configer.txt";


		FILE *fff = NULL;
		error = fopen_s(&fff, s1.c_str(), "a+");
		if (error)
		{
			cout << s1.c_str() << ends;
			throw 1;
		}

		//写入文件
		fprintf(fff, "%d", contrast.size());
		fputc(' ', fff);

		for (auto p : contrast)
		{
			char hp[20] = { 0 };
			_ultoa_s(count[p.first], hp, 20, 10);
			fprintf(fff, "%c%s ", p.first, (char*)hp);

		}

		//
		FILE* f = NULL;
		s1 = s + "code.txt";
		error = fopen_s(&f, s1.c_str(), "a+");
		if (error)
		{
			cout << s1.c_str() << ends;
			throw 1;
		}
		//写入数据信息
		string A;
		fseek(file, 0, SEEK_SET);//将原文件指针重新定位到文件开头

		while ((va = fgetc(file)) != EOF)
		{

			for (auto p : contrast[va])
			{
				A.push_back(p);
			}
		}


		int cas = 0;
		//看A中是否有剩余字节，有的话补至8的整数倍

		while (A.size() % 8 != 0)
		{
			A.push_back('0');
		}
		//写入信息
		//FILE *f5 = NULL;
		//fopen_s(&f5, "E:\\test5code.txt", "w");

		int size = A.size();
		int sum = 0;
		int i = 0;
		auto end = A.end();
		int countsum = 0;
		int pre = 0;
		for (auto pi = A.begin(); pi != A.end(); pi++)
		{
			sum = 2 * sum + (*pi - '0');
			i++;
			if (i % 8 == 0)
			{
				if (sum == 26)
				{

					fputc(' ', fff);
					fprintf(fff, "%d", (countsum - pre));
					pre = countsum;

				}
				else
				{
					fputc(sum, f);
					//fprintf(f5, "%d ", sum);
				}
				i = 0;
				sum = 0;
				countsum++;

			}
		}

		fclose(file);
		fclose(f);
		fclose(fff);

	}

	void restore(const string str)
	{



		//将文件的数据读取,分别为新编码个数(即出现字符的数量)，并且再读取字符和所对应的次数，同时也放入最小堆中
		Plie<Node *, compare<Node *>> A;
		int i = 0;
		size_t pos = str.rfind('c');
		string s = str.substr(0, pos);
		string s1 = s + "configer.txt";

		FILE *fff = NULL;
		errno_t error = fopen_s(&fff, s1.c_str(), "r");
		if (error)
		{
			cout << s1.c_str() << ends;
			throw 1;
		}

		fscanf_s(fff, "%d", &i, 3);
		fgetc(fff);
		for (int j = 0; j < i; j++)
		{
			Node *tmp = new Node();
			int va3 = fgetc(fff);
			tmp->_c = va3;
			fscanf_s(fff, "%d", &va3, 3);
			tmp->_time = va3;
			fgetc(fff);
			A.push(tmp);
		}

		fgetc(fff);

		//打开压缩文件
		FILE* file = NULL;
		error = fopen_s(&file, str.c_str(), "r");
		if (error)
		{
			cout << str.c_str() << ends;
			throw 1;
		}
		//创立哈夫曼树
		Node *root = construct(A);
		unsigned long  long count = root->_time;

		//建立一个新文件开始转换
		pos = str.rfind('c');
		s = str.substr(0, pos);
		s = s + "1.txt";
		FILE *f = NULL;
		error = fopen_s(&f, s.c_str(), "w+");
		if (error)
		{
			cout << s.c_str() << ends;
			throw 1;
		}

		/*fgetc(file);*/
		//开始转换
		/*FILE *f3 = NULL;
		fopen_s(&f3, "E:\\test3code.txt", "w");*/

		Node *head = root;
		int  va = 0;
		int countsum = 0;
		int flag = 0;
		fscanf_s(fff, "%d", &flag, 10);
		if (feof(fff))
			flag = -1;
		int inter = 0;
		while (count > 0)
		{
			if (countsum == flag)
			{
				va = 26;
				if (inter != -1)
				{
					fscanf_s(fff, "%d", &inter, 10);
					fgetc(fff);
					flag += inter;
				}


				if (feof(fff))
					inter = -1;


			}
			else
			{
				va = fgetc(file);
				/*fputc(va, fff);*/
			}
			countsum++;
			int pos = 0x80;
			while (0 != pos && count > 0)
			{

				int turn = (pos & va) ? 1 : 0;
				if (0 == turn)
					head = head->_left;
				if (0 != turn)
					head = head->_right;
				if (NULL == head->_left && NULL == head->_right)
				{
					fputc(head->_c, f);
					count--;
					head = root;
				}
				pos >>= 1;
			}


		}
		/*fclose(f3);*/
		fclose(file);
		fclose(f);
		fclose(fff);


	}


protected:

	void Tran(Node *root, map<int, string>& contrast)
	{
		string s;
		traning(root, s, contrast);
	}

	Node *construct(Plie<Node*, compare<Node*>>& d)
	{
		Node *root = NULL;
		while (d.size() > 1)
		{
			//将节点连接起来
			root = new Node();
			Node *left = root->_left = d.top();
			d.pop();
			Node *right = root->_right = d.top();
			d.pop();
			root->_time = left->_time + right->_time;
			left->_parent = root;
			right->_parent = root;

			d.push(root);
		}
		return root;
	}

	void traning(Node *root, string s, map<int, string>& contrast)
	{
		if (NULL == root->_left && NULL == root->_right)
		{
			contrast[root->_c] = s;
			return;
		}

		traning(root->_left, s + '0', contrast);

		traning(root->_right, s + '1', contrast);

	}





};