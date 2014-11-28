#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;


const int MAX_N = 1000000 + 10;

int rank[MAX_N], height[MAX_N], a[MAX_N], sa[MAX_N];

int cmp(int *x, int a, int b, int d)
{
	return x[a] == x[b] && x[a + d] == x[b + d];
}

void doubling(int *a, int N, int M)
{
	a[N] = 299; N++;
	static int sRank[MAX_N], tmpA[MAX_N], tmpB[MAX_N];
	int *x = tmpA, *y = tmpB;
	for(int i = 0; i < M; ++ i) sRank[i] = 0;
	for(int i = 0; i < N; ++ i) ++ sRank[x[i] = a[i]];
	for(int i = 1; i < M; ++ i) sRank[i] += sRank[i - 1];
	for(int i = N - 1; i >= 0; -- i) sa[-- sRank[x[i]]] = i;
	
	for(int d = 1, p = 0; p < N; M = p, d <<= 1) {
		p = 0; 
		//for(int i = 0; i < N; ++ i) printf("%d ", x[i]);
		//printf("\n");
		for(int i = N - d; i < N; ++ i) y[p ++] = i;
		for(int i = 0; i < N; ++ i)
			if (sa[i] >= d) y[p ++] = sa[i] - d;
		for(int i = 0; i < M; ++ i) sRank[i] = 0;
		for(int i = 0; i < N; ++ i) ++ sRank[x[i]];
		for(int i = 1; i < M; ++ i) sRank[i] += sRank[i - 1];
		for(int i = N - 1; i >= 0; -- i) sa[-- sRank[x[y[i]]]] = y[i];
		swap(x, y); x[sa[0]] = 0; p = 1;
		for(int i = 1; i < N; ++ i)
			x[sa[i]] = cmp(y, sa[i], sa[i - 1], d) ? p - 1 : p ++;
	}
	//for(int i = 0; i < N; ++ i) printf("%d ", x[i]);
	//	printf("\n");
	//for(int i = 0; i < 1000 || i < 3 * N; i++)
	//	sRank[i] = tmpA[i] = tmpB[i] = 0;
}

void calcHeight(int *a, int N)
{
	for(int i = 0; i < N; ++ i) rank[sa[i]] = i;
	int cur = 0;
	for(int i = 0; i < N; ++ i)
		if (rank[i]) {
			if (cur) cur --;
			for( ; a[i + cur] == a[sa[rank[i] - 1] + cur]; ++ cur);
			height[rank[i]] = cur;
		}
} // h[1 ~ N - 1]

int n;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int T;
	cin >> T;
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		if (n == 1) {
			printf("0\n");
			continue;
		}
		for(int i = 0; i < n - 1; i++)
			a[i] = a[i + 1] - a[i] + 101;
		n--;
		doubling(a, n, 300);
		calcHeight(a, n);
		long long ans = (long long)(n + 1) * n / 2;
		for(int i = 1; i < n; i++)
			ans -= height[i];
		cout << ans % 1000000009 << endl;
	}
	return 0;
} 
