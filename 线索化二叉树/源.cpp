#include "tree.h"

#define err 11

void test()
{
	vector<int> a  = { 4, 3, 7, 2, 'x', 'x', 8, 'x', 'x', 'x', 5, 6, 8, 9, 10, 'x', 'x', 'x', 'x', 'x', 7 , 7,'x','x',4};
	vector<int> aa = { 1, 4, 3, err, err, err, 2, 7 };
	BinarryTree<int> b(a, a.size(), 'x');
	b.Print();
	auto p = b.begin();
	auto End = b.end();
	while (p != End)
	{
		cout << *p << ends;
		p++;

	}
}


int main()
{
	test();
	getchar();
	return 0;


}