#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 40;

int N, C;
char str[MAXN];
double f[1 << 21], dp[1 << 21];
struct node
{
	int sta, cnt;
	friend int operator<(node a, node b)
	{
		return a.cnt < b.cnt;
	}
}p[1 << 21];

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int T;
	scanf("%d\n", &T);
	for(int t = 1; t <= T; t++) {
		gets(str);
		N = strlen(str);
		int s = 0;
		/*
		for(int i = 0; i < (1 << N); i++) {
			int cnt = 0;
			for(int j = 0; j < N; j++)
				if (i & (1 << j))
					cnt++;
			p[i].cnt = cnt; p[i].sta = i;
			f[i] = 0;
		}
		sort(p, p + (1 << N));
		*/
		for(int i = N - 1; i >= 0; i--)
			s = s * 2 + (str[i] == 'X');
		for(int i = 0; i < (1 << N); i++)
			f[i] = 0, dp[i] = 0;
		f[s] = 1;
		for(int i = 0; i < (1 << N) - 1; i++) {
			for(int j = 0; j < N; j++) {
				int k = j, dollar = N;
				while((1 << k) & i)
					k = (k + 1) % N, dollar--;
				f[i + (1 << k)] += f[i] / N;
				dp[i + (1 << k)] += (f[i] * dollar + dp[i]) / N;	
			}
		}
		printf("Case #%d: %.14lf\n", t, dp[(1 << N) - 1]);
	}
	return 0;
}
