#include "bitmap.h"

void test()
{
	bitmap A;
	A.insert(3);
	A.insert(10);
	A.insert(32);
	int i = A.find(3);
	i = A.find(10);
	i = A.find(67);
	i = A.find(15);
	A.resert(32);
	A.resert(3);
}

int main()
{
	test();
	getchar();
	return 0;
}