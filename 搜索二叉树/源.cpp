
#include "SearchBearrytree.h"




void test()
{
	//²âÊÔÓÃÀı
	BStree<int> a;
	a.insert(5);
	a.insertn(3);
	a.insertn(6);
	a.insertn(7);
	a.insertn(9);
	a.erase(5);
	a.insertn(1);
	a.insertn(2);
	a.erase(7);
	a.insertn(4);

	
	a.erase(3);
	a.insert(8);

	a.erasen(1);
	a.erasen(2);
	a.erasen(3);
	a.erasen(4);
	a.erasen(5);
	a.erasen(6);
	a.erasen(7);
	a.erasen(8);
	a.erasen(9);
	//BStreeNode<int>* b = a.find(2);
	//b->_value = 2;


	a.middle_display();
	



}




int main()
{
	test();
	getchar();
	return 0;

}


