#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 200;

int N, T, K;
int a[MAXN], now, sum, ans;

int main()
{
	scanf("%d", &T);
	while(T--)
	{
		sum = 0, ans = 0;
		scanf("%d %d", &N, &K);
		for(int i = 1; i <= N; i++)
			scanf("%d", &a[i]);
		sort(a + 1, a + N + 1);
		for(int i = 1; i <= N; i++)
			sum += a[i];
		now = 0;
		for(int i = 1; i <= K; i++)
			now += a[i];
		ans = max(ans, abs(now - (sum - now)));
		now = 0;
		for(int i = N - K + 1; i <= N; i++)
			now += a[i];
		ans = max(ans, abs(now - (sum - now)));
		printf("%d\n", ans);
	}
	return 0;
} 
