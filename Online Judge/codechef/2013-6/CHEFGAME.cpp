#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXN = 70000;
const long long mod = 747474747, inf = 2000000000000000000ll;

int T, N, D;

long long dis[MAXN];
int dix[MAXN][7], set[MAXN];
long long ans = 0;

inline long long calc(int a, int b)
{
	long long res = 0;
	for(int i = 1; i <= D; i++)
		res += (long long)(dix[a][i] - dix[b][i]) * (dix[a][i] - dix[b][i]);
	return res;
}

int main()
{
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d %d", &N, &D);
		for(int i = 1; i <= N; i++)
			for(int j = 1; j <= D; j++)
				scanf("%d", &dix[i][j]);
		ans = 1;
		int top = 0;
		for(int i = 2; i <= N; i++)
			dis[i] = calc(1, i), set[++top] = i;
		while(top)
		{
			int pos;
			long long Max = -inf;
			for(int j = 1; j <= top; j++)
			{
				if (Max < dis[set[j]])
					Max = dis[set[j]], pos = j;
			}
			if (Max > 0)
				ans = ans * (Max % mod) % mod;
			int s = set[pos];
			for(int i = pos; i < top; i++)
				set[i] = set[i + 1];
			top--;
			for(int j = 1; j <= top; j++)
				dis[set[j]] = max(dis[set[j]], calc(s, set[j]));
		}
		cout << ans << endl;
	}
	return 0;
}
