#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXN = 2000;

int n, a[MAXN], b[MAXN], ans[MAXN], m;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int T;
	cin >> T;
	while(T--) {
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		printf("%.6lf\n", (double)a / (a + b));
	}
	return 0; 
} 
