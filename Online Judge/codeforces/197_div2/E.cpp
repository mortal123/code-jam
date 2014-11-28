#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

const int MAXN = 1100;

int n, a[MAXN], m;
vector<pair<int, int> > pairs;
int L[MAXN], R[MAXN];

int check(vector<pair<int, int> > &pairs) {
	int start = 1;
	for(int i = 0; i < pairs.size(); i++) {
		if (start != pairs[i].first)
			return 0;
		start = pairs[i].second + 1;
	}
	return 1;
}

void dfs(int dep, vector<pair<int, int> > pairs) {
	if (check(pairs)) {
		printf("%d\n", dep - 1);
		for(int i = dep - 1; i >= 1; i--) {
			printf("%d %d\n", L[i], R[i]);
			//for(int j = L[i], k = R[i]; j < k; j++, k--)
			//	swap(a[j], a[k]);
		}
		//for(int i = 1; i <= n; i++)
		//	printf("%d ", a[i]);
		exit(0);
	}
	if (dep > 3) {
		return ;
	}
	vector<pair<int, int> > tmp;
	for(int i = 0; i < pairs.size(); i++)
		for(int j = i; j < pairs.size(); j++) {
			tmp = pairs;
			for(int k = i; k <= j; k++)
				swap(tmp[k].first, tmp[k].second);
			for(int k = i, l = j; k < l; k++, l--)
				swap(tmp[k], tmp[l]);
			int cnt = 0;
			for(int k = 0; k < pairs.size() ; k++) {
				if (k == i)
					L[dep] = cnt + 1;
				cnt += abs(pairs[k].second - pairs[k].first) + 1;
				if (k == j)
					R[dep] = cnt;
			}
			if (L[dep] == R[dep])
				continue;
			dfs(dep + 1, tmp);
		}
}		

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1, j; i <= n; i = j + 1) {
		j = i;
		if (i < n && abs(a[i + 1] - a[i]) == 1) {
			j = i + 1;
			while(j < n && a[j + 1] - a[j] == a[i + 1] - a[i])
				j++;
		}
		pairs.push_back(make_pair(a[i], a[j]));
	}
	//for(int i = 0; i < pairs.size(); i++)
	//	cerr << pairs[i].first << " " << pairs[i].second << endl;
	dfs(1, pairs);
	int l = 1, r = n, cnt = 0;
	while(l < r) {
		while(l < r && a[l + 1] - a[l] == 1)
			l++;
		while(l < r && a[r] - a[r - 1] == 1)
			r--;
		if (l == r)
			break;
		L[++cnt] = l, R[cnt] = r;
		for(int i = l, j = r; i < j; i++, j--)
			swap(a[i], a[j]);
	}
	printf("%d\n", cnt);
	for(int i = cnt; i >= 1; i--)
		printf("%d %d\n", L[i], R[i]);
	return 0;
}
