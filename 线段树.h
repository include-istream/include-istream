#pragma once

#include <iostream>
#include <cstdio>
constexpr auto MAXN = 500010;
//#pragma comment(linker, "/STACK:2147483648")
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;

template<class T>
class SegmentTree
{
private:
	T sum[MAXN];
	T add[MAXN];
public:
	void build(int tree_num, int left, int right, int array_num, T value);
	T intervalSum(int tree_num, int left, int right, int x, int y);
	T query(int tree_num, int left, int right, int x, int y);                   //query() returns the value in Σ[x,y]
	void modify(int tree_num, int left, int right, int x, int y, T value);      //modify() changes the value in [x,y]

	void flagModify(int tree_num, int left, int right, T value);
	void pushdown(int tree_num, int left, int right, int mid);
	void modifyInPd(int tree_num, int left, int right, int x, int y, T value);
	T queryInPd(int tree_num, int left, int right, int x, int y);
	SegmentTree() {};
	SegmentTree(int n);
	//~SegmentTree();
};

template<class T>
SegmentTree<T>::SegmentTree(int n)
{
	for (int i = 1; i <= n; i++)
	{
		T v = 0;
		cin >> v;
		build(1, 1, n, i, v);
	}
}

template<class T>
void SegmentTree<T>::build(int tree_num, int left, int right, int array_num, T value)
{
	if (array_num < left || array_num > right) return;
	if (left == right && left == array_num)
	{
		sum[tree_num] = value;
		return;
	}
	int mid = (left + right) >> 1;
	build(2 * tree_num, left, mid, array_num, value);
	build(2 * tree_num + 1, mid + 1, right, array_num, value);
	sum[tree_num] = sum[tree_num * 2] + sum[tree_num * 2 + 1];
}
//This function adds a node to the tree. And it's number in the array is array_num,
//value is value, number in the tree is tree_num.


template<class T>
T SegmentTree<T>::intervalSum(int tree_num, int left, int right, int x, int y)
{
	int mid = 0;
	T res = 0;
	if (x > right || y < left) return 0;
	if (x <= left && y >= right) return sum[tree_num];
	mid = (left + right) >> 1;
	res = query(2 * tree_num, left, mid, x, y);
	res += query(2 * tree_num + 1, mid + 1, right, x, y);
	return res;
}
//This function is used for interval sum.

template<class T>
void SegmentTree<T>::modify(int tree_num, int left, int right, int x, int y, T value)
{
	if (x > right || y < left) return;
	if (left >= x && right <= y)
	{
		add[tree_num] += value;
		return;
	}
	sum[tree_num] += (min(right, y) - max(left, x) + 1) * value; //[left,right]∩[x,y]+1
	int mid = (left + right) >> 1;
	if (x <= mid) modify(2 * tree_num, left, mid, x, y, value);
	if (mid < y) modify(2 * tree_num + 1, mid + 1, right, x, y, value);
}
//This function adds the value to a interval [x,y]. 

template<class T>
T SegmentTree<T>::query(int tree_num, int left, int right, int x, int y)
{
	if (x > right || y < left) return 0;  //This sentence is VERY IMPROTANT!!!DON'T FORGET TO WRITE IT!!!
	if (left >= x && right <= y) return  sum[tree_num] + (T(right) - T(left) + 1) * add[tree_num];
	int mid = (left + right) >> 1;
	T res = 0;
	res = (T(min(right, y)) - T(max(left, x)) + 1) * add[tree_num];
	if (x <= mid) res += query(2 * tree_num, left, mid, x, y);
	if (mid < y) res += query(2 * tree_num + 1, mid + 1, right, x, y);
	return res;
}
//This function has the same function as intervalSum() while it's used for interval change.

//These two functions above are "永久标记法".This kind of means is eazy to write, however, if we want
//to use plus in the Segment Tree, they are invalid. So you are reommended to use "标记下传法".


template<class T>
void SegmentTree<T>::flagModify(int tree_num, int left, int right, T value)
{
	add[tree_num] += value;
	sum[tree_num] += (T(right) - T(left) + 1) * value;
	return;
}
//This function signs an add flag(array add) instead of really add value to the node.

template<class T>
void SegmentTree<T>::pushdown(int tree_num, int left, int right, int mid)
{
	if (add[tree_num] == 0) return;
	flagModify(2 * tree_num, left, mid, add[tree_num]);
	flagModify(2 * tree_num + 1, mid + 1, right, add[tree_num]);
	add[tree_num] = 0;
}
//This function push down a node's flag.It's left child and right child will get this flag if their flag is 0.

template<class T>
void SegmentTree<T>::modifyInPd(int tree_num, int left, int right, int x, int y, T value)
{
	if (y < left || x > right) return;
	if (left >= x && right <= y) return flagModify(tree_num, left, right, value);
	int mid = (left + right) >> 1;
	pushdown(tree_num, left, right, mid);
	if (x <= mid) modifyInPd(2 * tree_num, left, mid, x, y, value);
	if (mid < y) modifyInPd(2 * tree_num + 1, mid + 1, right, x, y, value);
	sum[tree_num] = sum[2 * tree_num] + sum[2 * tree_num + 1];
}

template<class T>
T SegmentTree<T>::queryInPd(int tree_num, int left, int right, int x, int y)
{
	if (y < left || x > right) return 0;
	if (left >= x && right <= y) return sum[tree_num];
	int mid = (left + right) >> 1;
	T res = 0;
	pushdown(tree_num, left, right, mid);
	if (x <= mid) res += queryInPd(2 * tree_num, left, mid, x, y);
	if (mid < y) res += queryInPd(2 * tree_num + 1, mid + 1, right, x, y);
	return res;
}

/*USED FOR TEST
int main()
{
	int n;
	cin >> n;
	SegmentTree<double> a(n);
	cout << a.intervalSum(1, 1, n, 2, 4)<<endl;
	int i=0;
	cin >> i;
	a.modifyInPd(1, 1, n, 2, 4, i);
	cout << a.queryInPd(1, 1, n, 2, 4)<<endl;
	return 0;
}
*/
