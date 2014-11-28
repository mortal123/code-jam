#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 2100, MAXM = MAXN * MAXN;

int A[MAXN], B[MAXN], n, last[MAXN], dgr[MAXN];

struct eglist
{
	int other[MAXM], succ[MAXM], last[MAXN], sum;
	void clear()
	{
		memset(last, 0, sizeof(last));
		sum = 0;
	}
	void AddEdge(int a, int b)
	{
		swap(a, b);
		dgr[b]++;
		//printf("%d %d\n", a, b);
		other[++sum] = b, succ[sum] = last[a], last[a] = sum;
	}
}e;

int ans[MAXN], q[MAXN];
priority_queue <int> Q;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int T;
	scanf("%d", &T);
	for(int t = 1; t <= T; t++) {
		scanf("%d", &n);
		e.clear();
		for(int i = 0; i <= n; i++)
			last[i] = -1, dgr[i] = 0;
		for(int i = 0; i < n; i++)
		{
			scanf("%d", &A[i]);
			if (last[A[i]] != -1)
			{
				int tmp = last[A[i]];
				e.AddEdge(i, last[A[i]]);
			}
			if (A[i] != 1)
			{
				int tmp = last[A[i] - 1];
				e.AddEdge(last[A[i] - 1], i);
			}
			last[A[i]] = i;
		}
		for(int i = 0; i <= n; i++)
			last[i] = n;
		for(int i = 0; i < n; i++)
			scanf("%d", &B[i]);
		for(int i = n - 1; i >= 0; i--)
		{
			if (last[B[i]] != n)
			{
				int tmp = last[B[i]];
				e.AddEdge(i, last[B[i]]);
			}
			if (B[i] != 1)
			{
				int tmp = last[B[i] - 1];
				e.AddEdge(last[B[i] - 1], i);
			}
			last[B[i]] = i;
		}
		while(Q.size())
			Q.pop();
		int head = 0, tail = 0, oper = 1;
		for(int i = 0; i < n; i++)
			if (dgr[i] == 0)
				Q.push(i);
		for(int i = 0; i <= n; i++)
				ans[i] = 0;
		int use = n;
		while(!Q.empty()) {
			int x = Q.top();
			Q.pop();
			ans[x] = use;
			use--;
			for(int i = e.last[x]; i; i = e.succ[i]) {
				int y = e.other[i];
				dgr[y]--;
				if (!dgr[y])
					Q.push(y);
			}
		}
		printf("Case #%d:", t);
		for(int i = 0; i < n; i++)
			printf(" %d", ans[i]);
		printf("\n");
	}
	return 0;
}
