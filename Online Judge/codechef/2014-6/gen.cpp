#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <time.h>
#define PQ priority_queue
#define OO 2147483647

using namespace std;

int n = 100000, m1 = 700, m2 = 700, i;

int main()
{
	freopen("input.txt", "w", stdout);
	srand(time(NULL));
	printf("%d %d %d\n", n, m1, m2);
	for (i = 2; i <= n; i++)
		printf("%d %d\n", i, rand() % (i - 1) + 1);
	for (i = 1; i <= m1; i++)
		printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand());
	for (i = 1; i <= m2; i++)
		printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand());
	
	return 0;
}
