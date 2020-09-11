/*这是一个集成了c++十大排序算法的头文件，现在仍未完工
主要用于竞赛或平时方便用。
以后或许会将更多的东西，比如数据结构给加进来。

9.8更新
目前本头文件已经有七种排序算法了。
其中，特别感谢许誉潇同学贡献的选择排序与插入排序算法。
此外，不久后将更新搜索算法。 
Billy Du*/
#ifndef SORTS_H_
#define SORTS_H_

#include <cmath>
#include <iostream>
#include <cstring>

const long long int LONG=10000000;

int r[LONG],flag_=1;

struct BiTree
{
	int l_child,r_child;
	int Data;
}bt[LONG];
namespace sort
{
	template <typename val>
	void swap(val& value1, val& value2)
	{
		val temp;
		temp = value1;
		value1 = value2;
		value2 = temp;
	}
	namespace BubbleSort
	{
		template <typename T>
		void Bubble_sort(T* array, T array_num, bool flag)   //flag==true, 从小到大，否则从大到小 
		{
			for (int i = array_num - 1; i >= 1; i--)
				for (int j = 1; j <= i; j++)
				{
					if (flag)
					{
						if (array[j] > array[j + 1])  swap(array[j], array[j + 1]);
					}


					else
					{
						if (array[j] < array[j + 1])  swap(array[j], array[j + 1]);
					}

				}
		}
	}
	namespace MergeSort
	{
		template <typename T1>
		void Merge_sort(T1* array, T1 left, T1 right)
		{
			if (left == right) return;
			int mid = (left + right) / 2;
			Merge_sort(array, left, mid);
			Merge_sort(array, mid + 1, right);
			int i = left, j = mid + 1, k = left;

			while (i <= mid && j <= right)
			{
				if (array[i] <= array[j])
				{
					r[k] = array[i]; k++; i++;
				}
				else
				{
					r[k] = array[j]; k++; j++;
				}
			}
			while (i <= mid)
			{
				r[k] = array[i]; k++; i++;
			}
			while (j <= right)
			{
				r[k] = array[j]; k++; j++;
			}
			for (int i = left; i <= right; i++) array[i] = r[i];
		}
	}

	namespace QuickSort
	{
		template <typename T2>
		void Quick_sort(T2* array, T2 left, T2 right)
		{
			if (right <= left) return;
			int i = left;
			int j = right + 1;
			int key = array[left];
			while (true)
			{
				while (array[++i] < key)
				{
					if (i == right) {
						break;
					}
				}
				while (array[--j] > key)
				{
					if (j == left) {
						break;
					}
				}
				if (i >= j) break;
				swap(array[i], array[j]);
			}
			swap(array[left], array[j]);
			Quick_sort(array, left, j - 1);
			Quick_sort(array, j + 1, right);
		}
	}

	namespace HeapSort
	{
		template <typename b>
		void max_heapify(b* array, b start, b end)
		{
			int dad = start;
			int son = dad * 2 + 1;
			while (son <= end)
			{
				if (son + 1 <= end && array[son] < array[son + 1])  son++;
				if (array[dad] > array[son])  return;
				else
				{
					swap(array[dad], array[son]);
					dad = son;
					son = dad * 2 + 1;
				}
			}
		}

		template <typename b>
		void min_heapify(b* array, b start, b end)
		{
			int dad = start;
			int son = dad * 2 + 1;
			while (son <= end)
			{
				if (son + 1 <= end && array[son] > array[son + 1])  son++;
				if (array[dad] < array[son])  return;
				else
				{
					swap(array[dad], array[son]);
					dad = son;
					son = dad * 2 + 1;
				}
			}
		}
		//remember
		template <typename T3>
		void Heap_sort(T3* array, T3 array_num, bool flag)                          //if flag==true 建大顶堆，升序排序，否则降序。       
		{
			if (flag)                                                                       //大顶堆排序
			{
				for (int i = array_num / 2 - 1; i >= 0; i--)  max_heapify(array, i, array_num - 1);
				for (int i = array_num - 1; i > 0; i--)
				{
					swap(array[0], array[i]);
					max_heapify(array, 0, i - 1);
				}
			}
			/*else
			{
				for (int i=0;i<=array_num/2-1;i++)  min_heapify(array,i,array_num);
				for (int i=1;i<=array_num-1; i++)
				{
					swap(array[0],array[i]);
					min_heapify(array,0,i);
				}
			}*/
		}
	}
	namespace BTSort
	{
		template <typename abab>
		void insert(abab p, abab va)
		{
			if (!r[p])
			{
				r[p] = va;
				return;
			}
			if (va < r[p]) insert(2 * p, va);
			else insert(2 * p + 1, va);
		}

		template <typename baba>
		void mid_print(baba* array, baba p)
		{
			if (r[p] == 0) return;
			mid_print(array, 2 * p);
			array[flag_] = r[p]; flag_++;
			mid_print(array, 2 * p + 1);

		}

		template <typename T4>
		void BT_sort(T4* array, T4 array_num)
		{
			for (int i = 1; i <= array_num; i++)
			{
				insert(1, array[i]);
			}
			mid_print(array, 1);
		}
	}
}
#endif


#ifndef Algorithm_H_
#define Algorithm_H_

#endif
