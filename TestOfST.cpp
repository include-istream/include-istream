#include <iostream>
#include "SegmentTree.h"
using namespace std;
int main()
{
	SegmentTree<int> a(5);
	cout << a.intervalSum(1, 5, 2, 4)<<endl;
	a.modifyInPd(1, 5, 2, 4, 10);    
	cout << a.queryInPd(1, 5, 2, 4)<<endl;
	a.modifyInPd(1, 5, 2, 4, 10);
	cout << a.queryInPd(1, 5, 2, 4)<<endl; 
	
	return 0;
}
