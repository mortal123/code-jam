#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1111111;
const int INF = 111111111;

int sum[N];
int n, a[N], b[N], lst[N];
char s[N];
vector<int> vec[N];

void solve(char s[], int n, int a[]) {
	for(int i = 1; i <= n; i++) {
		sum[i] = sum[i - 1] + (s[i] == 'p' ? 1 : -1);
	}
	vector<int> q;
	q.push_back(0);
	for(int i = 1; i <= n; i++) {
		while((int)q.size() && sum[i] >= sum[q.back()])
			q.pop_back();
		if ((int)q.size() == 0) {
			a[i] = 1;
		} else {
			a[i] = q.back() + 2;
		}
		q.push_back(i);
	}
}

int find(int x) {
	int p = x, t;
	while(lst[p] != p) {
		p = lst[p];
	}
	while(lst[x] != p) {
		t = lst[x];
		lst[x] = p;
		x = t;
	}
	return p;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);	
	scanf("%s", s + 1);
	for(int i = 1, j = n; i < j; i++, j--)
		swap(s[i], s[j]);
	solve(s, n, a);
	for(int i = 1, j = n; i < j; i++, j--)
		swap(s[i], s[j]);
	for(int i = 1; i <= n; i++) {
		b[n - i + 1] = n - a[i] + 1;
	}
	
	for(int i = 1; i <= n; i++) {
		vec[b[i]].push_back(i);
	}
	solve(s, n, a);
	for(int i = 1; i <= n + 1; i++) {
		lst[i] = i;
	}
	for(int i = 0; i < (int)vec[0].size(); i++)
		lst[vec[0][i]] = vec[0][i] + 1;
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		ans = max(ans, 1 + i - find(a[i]));
		for(int j = 0; j < (int)vec[i].size(); j++) {
			lst[vec[i][j]] = vec[i][j] + 1;
		}
	}
	printf("%d\n", ans);
}
