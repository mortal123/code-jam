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
		scanf("%d", &n);
		for(int i = 0; i < n; i++)
			scanf("%d", &a[i]), b[i] = a[i];
		sort(b, b + n);
		m = 0;
		for(int i = 0; i < n; i++) {
			if ()
		}
	}
	return 0;
} 
