#include <iostream>
#include <algorithm>
#include <cstdio>
#include "Sorts.h"

using namespace std;
int a[10001];
 
 int main()
 {
 	freopen("read.txt","r",stdin);
 	freopen("write.txt","w",stdout);
 	int n;
 	cin>>n;
 	for (int i=1;i<=n;i++) cin>>a[i];   
 	//Bubble_sort(a,n);      //0.07s 1000Êý¾Ý 
 	//Merge_sort(a,1,n);       //0.09s 
	//Quick_sort(a,1,n);       //0.06s
 	for (int i=1;i<=n;i++) cout<<a[i]<<" ";
 	fclose(stdin);
 	fclose(stdout);
 }
