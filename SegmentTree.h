#pragma once

#include <iostream>
#include <cstdio>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;
using std::vector;

template<class T>
class SegmentTree
{
private:
	vector<T> sum;
	vector<T> add;
public:
	void build(int left, int right, int array_num, T value,int tree_num=1);
	T intervalSum(int left, int right, int x, int y,int tree_num=1);
	T query(int left, int right, int x, int y,int tree_num=1);                   //query() returns the value in Σ[x,y]
	void modify(int left, int right, int x, int y, T value,int tree_num=1);      //modify() changes the value in [x,y]

	void flagModify(int left, int right, T value,int tree_num=1);                
	void pushdown(int left, int right, int mid, int tree_num=1);                 
	void modifyInPd(int left, int right, int x, int y, T value, int tree_num=1);
	T queryInPd(int left, int right, int x, int y,int tree_num=1);
	SegmentTree() {};
	SegmentTree(int n);
	//~SegmentTree() {};
};

template<class T>
SegmentTree<T>::SegmentTree(int n): sum(4 * T(n), 0),add(4 * T(n), 0)
{
	cout << "Please enter " << n << " numbers to build Segment Tree." << endl;
	for (int i = 1; i <= n; i++)
	{
		T v = 0;
		cin >> v;
		build(1, n, i, v);
	}
	cout << "The initialization of Segment Tree is successful!" << endl;
}

template<class T>
void SegmentTree<T>::build(int left, int right, int array_num, T value, int tree_num)
{
	if (array_num < left || array_num > right) return;
	if (left == right && left == array_num)
	{
		sum[tree_num] = value;
		return;
	}
	int mid = (left + right) >> 1;
	build(left, mid, array_num, value, 2 * tree_num);
	build(mid + 1, right, array_num, value, 2 * tree_num + 1);
	sum[tree_num] = sum[T(tree_num) * 2] + sum[T(tree_num) * 2 + 1];
}
//This function adds a node to the tree. And it's number in the array is array_num,
//value is value, number in the tree is tree_num.


template<class T>
T SegmentTree<T>::intervalSum(int left, int right, int x, int y, int tree_num)
{
	int mid = 0;
	T res = 0;
	if (x > right || y < left) return 0;
	if (x <= left && y >= right) return sum[tree_num];
	mid = (left + right) >> 1;
	res = query(left, mid, x, y, 2 * tree_num);
	res += query(mid + 1, right, x, y, 2 * tree_num + 1);
	return res;
}
//This function is used for interval sum.

template<class T>
void SegmentTree<T>::modify(int left, int right, int x, int y, T value, int tree_num)
{
	if (x > right || y < left) return;
	if (left >= x && right <= y)
	{
		add[tree_num] += value;
		return;
	}
	sum[tree_num] += (min(right, y) - max(left, x) + 1) * value; //[left,right]∩[x,y]+1
	int mid = (left + right) >> 1;
	if (x <= mid) modify(left, mid, x, y, value, 2 * tree_num);
	if (mid < y) modify(mid + 1, right, x, y, value, 2 * tree_num + 1);
}
//This function adds the value to a interval [x,y]. 

template<class T>
T SegmentTree<T>::query(int left, int right, int x, int y, int tree_num)
{
	if (x > right || y < left) return 0;  //This sentence is VERY IMPROTANT!!!DON'T FORGET TO WRITE IT!!!
	if (left >= x && right <= y) return  sum[tree_num] + (T(right) - T(left) + 1) * add[tree_num];
	int mid = (left + right) >> 1;
	T res = 0;
	res = (T(min(right, y)) - T(max(left, x)) + 1) * add[tree_num];
	if (x <= mid) res += query(left, mid, x, y, 2 * tree_num);
	if (mid < y) res += query(mid + 1, right, x, y, 2 * tree_num + 1);
	return res;
}
//This function has the same function as intervalSum() while it's used for interval change.

//These two functions above are "永久标记法".This kind of means is eazy to write, however, if we want
//to use plus in the Segment Tree, they are invalid. So you are reommended to use "标记下传法".


template<class T>
void SegmentTree<T>::flagModify(int left, int right, T value, int tree_num)
{
	add[tree_num] += value;
	sum[tree_num] += (T(right) - T(left) + 1) * value;
	return;
}
//This function signs an add flag(array add) instead of really add value to the node.

template<class T>
void SegmentTree<T>::pushdown(int left, int right, int mid, int tree_num)
{
	if (add[tree_num] == 0) return;
	flagModify(left, mid, add[tree_num], 2 * tree_num);
	flagModify(mid + 1, right, add[tree_num], 2 * tree_num + 1);
	add[tree_num] = 0;
}
//This function push down a node's flag.It's left child and right child will get this flag if their flag is 0.

template<class T>
void SegmentTree<T>::modifyInPd(int left, int right, int x, int y, T value, int tree_num)
{
	if (y < left || x > right) return;
	if (left >= x && right <= y) return flagModify(left, right, value, tree_num);
	int mid = (left + right) >> 1;
	pushdown(left, right, mid, tree_num);
	if (x <= mid) modifyInPd(left, mid, x, y, value, 2 * tree_num);
	if (mid < y) modifyInPd(mid + 1, right, x, y, value, 2 * tree_num + 1);
	sum[tree_num] = sum[2 * T(tree_num)] + sum[2 * T(tree_num) + 1];
}

template<class T>
T SegmentTree<T>::queryInPd(int left, int right, int x, int y, int tree_num)
{
	if (y < left || x > right) return 0;
	if (left >= x && right <= y) return sum[tree_num];
	int mid = (left + right) >> 1;
	T res = 0;
	pushdown(left, right, mid, tree_num);
	if (x <= mid) res += queryInPd(left, mid, x, y, 2 * tree_num);
	if (mid < y) res += queryInPd(mid + 1, right, x, y, 2 * tree_num + 1);
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
