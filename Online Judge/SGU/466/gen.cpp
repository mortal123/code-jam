#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;

int main()
{
	srand(time(0));
	freopen("input.txt", "w", stdout); 
	int n = 20, m = 20;
	printf("%d %d\n", n, m);
	for(int i = 1; i <= n; i++)
		printf(".");
	printf("\n");
	for(int i = 1; i <= m; i++)
	{
		if (i > 10 && rand() % 64 < 12)
		{
			printf("LEAVE %d\n", rand() % (i - 1) + 1);
		} else
		{
			printf("PARK %d\n", rand() % (n / 2) + 1);
		}
	}
	return 0;
}
