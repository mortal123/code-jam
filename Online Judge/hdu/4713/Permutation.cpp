#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN = 11005;
const double eps = 1e-8;

int n;
int check[MAXN], primes[MAXN], top;
double f[10001][1234], g[MAXN];

double dfs(int a, int b) {
	if (f[a][b] >= -eps)
		return f[a][b];
	if (a == 0) 
		return f[a][b] = 0;
	if (primes[b] > a)
		return f[a][b] = 0;
		
	double res = dfs(a, b + 1), tmp = g[b];
	for(int j = primes[b]; j <= a; j *= primes[b], tmp += g[b]) {
		res = max(res, tmp + dfs(a - j, b + 1));
		if (primes[b] == 1)
			break;
	}
	
	return f[a][b] = res;
}

int main() {
	//cout << log(5.0) << " " << log(2.0) + log(3.0) << endl;
	freopen("input.txt", "r", stdin);
	memset(f, -1, sizeof(f));
	primes[++top] = 1;
	for(int i = 2; i <= 10010; i++) {
		if (check[i] == 0) {
			primes[++top] = i;
			g[top] = log((double)i);
			for(int j = i + i; j <= 10010; j += i) 
				check[j] = 1;
		}
	}
	//printf("%d\n", top);
	int Test;
	scanf("%d", &Test);
	for(int test = 1; test <= Test; test++) {
		scanf("%d", &n);
		if (n == 1) {
			printf("1\n");
			continue;
		}
		double ans = dfs(n, 1), have = 0;
		//printf("%I64d\n", ans);
		vector<int> vec, print;
		for(int i = 2; i <= top && n; i++) {
		//	printf("%d %d\n", i, n);
			double tmp = g[i];
			for(int j = primes[i]; j <= n; j *= primes[i], tmp += g[i]) {
				if (fabs(have + tmp + f[n - j][i + 1] - ans) < 1e-6) {
					vec.push_back(j);
					n -= j;
					have += tmp;
					break;
				}
				if (primes[i] == 1)
					break;
			}
		}
		while(n--)
			vec.push_back(1);
		int first = 1, begin = 1;
		sort(vec.begin(), vec.end());
		for(int i = 0; i < vec.size(); i++) {
			for(int j = 1; j < vec[i]; j++)
				print.push_back(begin + j);
			print.push_back(begin);
			begin += vec[i];
		}
		for(int i = 0; i < print.size(); i++)
			printf("%d%c", print[i], i == print.size() - 1 ? '\n' : ' ');
	}
//	cout << sizeof(f) / 1024.0 / 1024.0 << endl; 
	return 0;
} 
