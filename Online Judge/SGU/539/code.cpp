#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

const int MAXN = 1100;

int n, a[MAXN], b[MAXN], visit[MAXN];
vector<pair<int, int> > ans, anss[2];

int checkZeroStep(int a[], int n) {
	for(int i = 2; i <= n; i++)
		if (a[i] < a[i - 1])
			return false;
	return true;
}

int checkOneStep(int a[], int n) {
	for(int i = 1; i <= n; i++)
		b[i] = a[i], visit[i] = 0;
	sort(b + 1, b + n + 1);
	ans.clear();
	for(int i = 1; i <= n; i++) {
		if (a[i] == b[i] || visit[i])
			continue;
		bool found = false;
		for(int j = i + 1; j <= n; j++)
			if (!visit[j] && a[j] == b[i] && a[i] == b[j]) {
				ans.push_back(make_pair(i, j));
				visit[j] = 1;
				found = true;
				break;
			}
		if (!found)
			return false;
	}
	return true;
}

int cmp(int i, int j) {
	return a[i] < a[j];
}

int checkTwoStep(int a[], int n) {
	anss[0].clear();
	anss[1].clear();
	for(int i = 1; i <= n; i++)
		b[i] = i, visit[i] = 0;
	sort(b + 1, b + n + 1, cmp);
	for(int i = 1; i <= n; i++)
		if (!visit[i]) {
			vector<int> vec;
			int x = i;
			while(!visit[x]) {
				visit[x] = 1;
				vec.push_back(x);
				x = b[x];
			}
			if (vec.size() == 1)
				continue;
			for(int j = 0, k = vec.size() - 2; j < k; j++, k--) {
				anss[0].push_back(make_pair(vec[j], vec[k]));
				swap(vec[j], vec[k]);
			}
			for(int j = 0, k = vec.size() - 1; j < k; j++, k--) {
				anss[1].push_back(make_pair(vec[j], vec[k]));
				swap(vec[j], vec[k]);
			}
		}
	return 1;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	if (checkZeroStep(a, n)) {
		printf("0\n");
	} else if (checkOneStep(a, n)) {
		printf("1\n");
		printf("%d", ans.size());
		if (ans.size() == 0)
			while(1);
		for(int i = 0; i < ans.size(); i++) {
			printf(" %d %d", ans[i].first, ans[i].second);
		}
		printf("\n");
	} else if (checkTwoStep(a, n)){
		printf("2\n");
		for(int i = 0; i < 2; i++) {
			printf("%d", anss[i].size());
			if (anss[i].size() == 0)
				while(1);
			for(int j = 0; j < anss[i].size(); j++)
				printf(" %d %d", anss[i][j].first, anss[i][j].second);
			printf("\n");
		}
	} else 
		while(1);
	return 0;
}
