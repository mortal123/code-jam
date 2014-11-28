#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> Gray;
int n, k;


int digit(int x)
{
	int cnt = 0;
	for(; x; x -= ((-x) & x), cnt++);
	return cnt;
}

int main()
{
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	Gray.push_back(0);
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++)
		for(int j = Gray.size() - 1; j >= 0; j--)
			Gray.push_back((1 << (i - 1)) + Gray[j]);
	Gray.push_back(0);
	/*
	for(int i = 0; i < Gray.size(); i++)
		printf("Gray %d\n", Gray[i]);
	*/
	int last = 0;
	for(int i = 1; i < Gray.size(); i++)
	{
		int x = Gray[i];
		if (digit(x) > k)
			continue;
		int vary = (last ^ x);
		for(int j = 0; j < n; j++)
		if (vary & (1 << j))
		{
			if (j < n - 1 && vary & (1 << (j + 1)))
			{
				if (last & (1 << j))
					printf("++%d", j + 1);
				else
					printf("--%d", j + 1 + 1);
			} else
			{
				if (last & (1 << j))
					printf("-%d", j + 1);
				else
					printf("+%d", j + 1);
			}
			break;
		}
		last = x;
	}
	return 0;
}
