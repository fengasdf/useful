#include "hashmap.h"

void test()
{
	HashTable<int, int> A;
	A.insert(1);
	A.insert(2);
	A.insert(3);
	A.insert(54);
	A.remove(1);
	A.remove(54);
	
}

int main()
{

	test();

	return 0;
}