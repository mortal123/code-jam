#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 100000;
const int PRIMENUM = 1000000;
const int MAXM = 10000000;

int f[MAXN + 10], prim[PRIMENUM + 10], pnum, MaxP[MAXM + 10], p[MAXN + 10];
bool sieve[MAXM + 10], app[PRIMENUM + 10];
long long MaxV;
int n, m, ans[MAXN + 10], farest;

vector<pair<int, int> > qut;

void work1()
{
	int pt;
	for(int i = 2; i <= farest; i++) {
		if (!sieve[i]) {
			prim[++pnum] = i;
			while(pt <= n && p[pt] < i)
				pt++;
			app[pnum] = (pt <= n && p[pt] == i);
			MaxP[i] = app[pnum] * prim[pnum];
		}
		for(int j = 1; j <= pnum; j++) {
			if (prim[j] > farest / i)
				break;
			MaxP[i * prim[j]] = max(app[j] * prim[j], MaxP[i]);
			sieve[i * prim[j]] = true;
			if (i % prim[j] == 0)
				break;
		}
	}
	
	for(int i = 1; i <= m; i++) {
		ans[i] = -1;
	}
}

void work2()
{
	f[0] = 0;
	f[1] = p[n] - 1;
	int i, k = 0;
	while(k < m && qut[k].first < p[n])
		ans[qut[k].second] = 1, k++;
	for(i = 1; f[i] < farest; i++) {
		int far = f[i];
		if (n < f[i] - f[i - 1]) {
			for(int j = 1; j <= n; j++) {
				int x = f[i] / p[j] * p[j];
				x += p[j];
				far = max(far, x - 1);
			}
		} else {
			for(int j = f[i - 1] + 1; j <= f[i]; j++) {
				far = max(far, j + MaxP[j] - 1);
			}
		}
		f[i + 1] = far;
		while(k < m && qut[k].first <= far)
			ans[qut[k].second] = i + 1, k++;
		if (f[i + 1] == f[i])
			break;
	}
}

int main()
{
	freopen("brunhilda.in", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &p[i]);
	sort(p + 1, p + n + 1);
	qut.clear();
	MaxV = 1;	
	farest = 0;
	for(int i = 1; i <= m; i++) {
		int a;
		scanf("%d", &a);
		farest = max(farest, a);
		qut.push_back(make_pair(a, i));
		if (MaxV <= MAXM)
			MaxV *= a;
	}
	sort(qut.begin(), qut.end());
	memset(sieve, 0, sizeof(sieve));
	int pt = 1; pnum = 0;
	MaxP[1] = 1; 
	work1();
	/*
	for(int i = 2; i <= farest; i++) {
		if (!sieve[i]) {
			prim[++pnum] = i;
			while(pt <= n && p[pt] < i)
				pt++;
			app[pnum] = (pt <= n && p[pt] == i);
			MaxP[i] = app[pnum] * prim[pnum];
		}
		for(int j = 1; j <= pnum; j++) {
			if (prim[j] > farest / i)
				break;
			MaxP[i * prim[j]] = max(app[j] * prim[j], MaxP[i]);
			sieve[i * prim[j]] = true;
			if (i % prim[j] == 0)
				break;
		}
	}
	
	for(int i = 1; i <= m; i++) {
		ans[i] = -1;
	}*/
	
	work2();
	/*
	f[0] = 0;
	f[1] = p[n] - 1;
	int i, k = 0;
	while(k < m && qut[k].first < p[n])
		ans[qut[k].second] = 1, k++;
	for(i = 1; f[i] < farest; i++) {
		int far = f[i];
		if (n < f[i] - f[i - 1]) {
			for(int j = 1; j <= n; j++) {
				int x = f[i] / p[j] * p[j];
				x += p[j];
				far = max(far, x - 1);
			}
		} else {
			for(int j = f[i - 1] + 1; j <= f[i]; j++) {
				far = max(far, j + MaxP[j] - 1);
			}
		}
		f[i + 1] = far;
		while(k < m && qut[k].first <= far)
			ans[qut[k].second] = i + 1, k++;
		if (f[i + 1] == f[i])
			break;
	}
	*/
	//printf("i = %d\n", i);
	for(int i = 1; i <= m; i++) {
		if (ans[i] == -1) {
			printf("oo\n");
		} else {
			printf("%d\n", ans[i]);
		}
	}
	return 0;
} 
