#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 100000;

int f[MAXN + 10], p[MAXN + 10];
int n, m, ans[MAXN + 10];

vector<pair<int, int> > qut;

int main()
{
	freopen("brunhilda.in", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &p[i]);
	sort(p + 1, p + n + 1);
	qut.clear();
	int farest = 0;
	for(int i = 1; i <= m; i++) {
		int a;
		scanf("%d", &a);
		farest = max(farest, a);
		qut.push_back(make_pair(a, i));
	}
	sort(qut.begin(), qut.end());
	for(int i = 1; i <= m; i++) {
		ans[i] = -1;
	}
	if (n > 10000) {
		for(int i = 1; i <= 5000; i++) {
			p[100 + i] = p[n - 5000 + i];
		}
		n = 10000;
	}
	f[0] = 0;
	int i, k = 0;
	for(i = 1; f[i - 1] < farest; i++) {
		int far = f[i];
		for(int j = 1; j <= n; j++) {
			int x = f[i - 1] / p[j] * p[j];
			x += p[j];
			far = max(far, x);
		}
		f[i] = far - 1;
		while(k < m && qut[k].first < far)
			ans[qut[k].second] = i, k++;
		if (f[i - 1] == f[i])
			break;
	}
	//printf("i = %d %d %d\n", i, f[]);
	for(int i = 1; i <= m; i++) {
		if (ans[i] == -1) {
			printf("oo\n");
		} else {
			printf("%d\n", ans[i]);
		}
	}
	return 0;
} 
