#ifndef SORTS_H_
#define SORTS_H_

#include <cmath>
#include <iostream>

template <typename T>
void Bubble_sort(T *array,T array_num)
{
	for (int i = array_num - 1; i >= 1; i--)
		for (int j = 1; j <= i; j++)
			if (array[j] < array[j + 1])
			{
				swap(array[j],array[j+1]);
			}
}
int r[1000000];
template <typename T1>
void Merge_sort(T1 *array,T1 left,T1 right)
{
	if (left == right) return;
	int mid = (left + right) / 2;
	Merge_sort(array,left, mid);
	Merge_sort(array,mid + 1, right);
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

template <typename T2>
void Quick_sort(T2 *array,T2 left,T2 right)
{
	if (right<=left) return;
    int i = left;
    int j = right + 1;
    int key = array[left];
    while (true)
    {
        while (array[++i] < key)
        {
            if (i == right){
                break;
            }
        }
        while (array[--j] > key)
        {
            if (j == left){
                break;
            }
        }
        if (i >= j) break;
        swap(array[i],array[j]);
    }
    swap(array[left],array[j]);
    Qsort(array, left, j - 1);
    Qsort(array, j + 1, right);
}
/*
struct BiTree
{
	int l_child,r_child;
	int Data;
}bt[100000];
int tot=0;
template <typename T>
void insert(T *array,T array_num)
{
	for (int i=1;i<=array_num;i++)
	{
		if (array[i]<bt[i])	
		{
			if (bt.l_child==0) tot++; insert(bt[tot].l_child)
			
		}
	}

}


template <typename T3>
void BT_sort(T3 *array,T3 )*/
#endif
