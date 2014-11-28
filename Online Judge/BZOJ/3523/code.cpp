#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int N = 1111111;

int n, start, endd;
int a[N], b[N];
int m;
priority_queue<pair<int, int> > q;

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &n, &start, &endd);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &b[i]);
		m += b[i];
	}
	if (b[start] <= 0 || b[endd] <= 0) {
		printf("0\n");
		return 0;
	}
	if (m == 1) {
		if (start == endd) {
			printf("%d\n", start);
			return 0;
		} else {
			printf("0\n");
			return 0;
		}
	}
	b[start]--;
	b[endd]--;
	m -= 2;
	if (b[start] < 0 || b[endd] < 0) {
		printf("0\n");
		return 0;
	} else if (m == 0) {
		printf("%d %d\n", start, endd);
		return 0;
	}
	for(int i = 1; i <= n; i++) {
		if (b[i]) {
			q.push(make_pair(b[i], i));
		}
	}
	int cur = 0;
	pair<int, int> last = make_pair(0, -1);
	while(!q.empty()) {
		pair<int, int> tmp = q.top();
		q.pop();
		a[++cur] = tmp.second;
		tmp.first--;
		if (last.first) {
			q.push(last);
		}
		last = tmp;
	}
	if (last.first) {
		printf("0\n");
		return 0;
	}
	/*
	for(int i = 1; i <= m; i++) {
		printf("%d ", a[i]);
	}
	puts("");	
	*/
	if (a[1] == start) {
		int r;
		for(r = 1; r <= m && a[r] == start; r += 2);
		if (r == m + 2) {
			printf("0\n");
			return 0;
		}
		for(int i = 1, j = r - 1; i < j; i++, j--)
			swap(a[i], a[j]);
	}
	if (a[m] == endd) {
		int l;
		for(l = m; l >= 1 && a[l] == endd; l -= 2);
		if (l == -1) {
			printf("0\n");
			return 0;
		}
		for(int i = m, j = l + 1; i > j; i--, j++)
			swap(a[i], a[j]);
	}
	a[0] = start, a[++m] = endd;
	for(int i = 0; i <= m; i++) {
		if (i + 1 <= m && a[i] == a[i + 1]) {
			printf("0\n");
			return 0;
		} else if (i > 0 && a[i] == a[i - 1]) {
			printf("0\n");
			return 0;
		}
	}
	for(int i = 0; i <= m; i++) {
		printf("%d%c", a[i], i == m ? '\n' : ' ');
	}
	return 0;
}
