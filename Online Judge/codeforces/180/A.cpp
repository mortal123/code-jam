#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 2000;

char A[MAXN], B[MAXN];
int cnt;
int n, m;

int main()
{
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	gets(A + 1); n = strlen(A + 1);
	gets(B + 1); m = strlen(B + 1);
	int cntot = 0, bakcnt = 0;
	for(int i = 1; i <= n; i++)
		cntot += (A[i] == '1');
	if (cntot % 2 == 1)
		A[++n] = '1', cntot++;
	bakcnt = cntot;
	for(int s = 1; s <= n + 1; s++)
	{
		cntot = bakcnt;
		if (n - s + 1 > m)
			continue;
		int cnts = 0;
		for(int i = 1; i <= s - 1; i++)
			cnts += (A[i] == '1');
		int flag = 1;
		for(int i = s; i <= n; i++)
			if (A[i] != B[i - s + 1])
				flag = 0;
		if (!flag)
			continue;
		int t = n - s + 2;
		for(int i = t; i <= m; i++)
		{
			if (B[i] == '0')
			{
				if (cntot % 2 == 0)
					continue;
				else
				if (cnts)
				{
					cnts--;
					cntot--;
				} else
					flag = 0;
			} else
			{
				if (cntot % 2 == 1)
					continue;
				else
				if (cnts)
				{
					cnts--;
					//cntot--;
				} else
					flag = 0;
			}
		}
		if (flag)
		{
			printf("YES\n");
			return 0;
		}
	}
	printf("NO\n");
	return 0;	
} 
