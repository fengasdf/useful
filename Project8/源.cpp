
#include "AVLtree.h"



void test()
{

	AVLtree<int, int> a;
	a.insert(4);
	a.insert(2);
	a.insert(6); 
	a.insert(1); 
	a.insert(3);
	a.insert(5);
	a.insert(15);
	a.insert(7);
	a.insert(16);
	a.insert(14);



	a.middle_display();
}

int main()
{
	test();
	getchar();
	return 0;
}