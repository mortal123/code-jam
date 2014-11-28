#include <cstdio>
#include <cstdlib>
#include <iostream> 
#include <algorithm>
#include <cstring>
using namespace std;

int k, n, maxb, t, ans;
int b[200000], h[200000];

int main()
{
	freopen("input.txt", "w", stdout);
	printf("%d %d %d %d\n", 10, 200, 100000, 78501);
	k = 10;
	while(k--)
	{
		for(int i = 1; i <= 200; i++)
			printf("%d ", rand()); 
		printf("\n");
	}
	return 0;
}
