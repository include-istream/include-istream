#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	freopen("read.txt","w",stdout);
int a[1000];
int i;srand(time(0)); /*��ʼbai��du��zhi��dao*/for( i = 0; i < 1000; i++ ) a[i]=rand();
for( i = 0; i < 1000; i++ ) printf("%d ", a[i]);
fclose(stdout);
}
