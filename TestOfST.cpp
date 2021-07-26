#include <iostream>
#include "SegmentTree.h"
#pragma comment(linker,"/STACK:2147483648")
using namespace std;
int main()
{
	int n;
	cin >> n;
	SegmentTree<int> a(n);
	cout << a.intervalSum(1, 1, n, 1, n) << endl;
	int k;
	cin >> k;
	a.modifyInPd(1, 1, n, 2, n - 1, k);
	cout << a.queryInPd(1, 1, n, 1, n);
	return 0;
}
