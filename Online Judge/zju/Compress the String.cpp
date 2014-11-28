#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <ctime>
#include <cmath>
#include <set>
#include <map>

#define foreach(it,e) for (__typeof(e.begin()) it = e.begin(); it != e.end(); ++it)

#define sqr(x) ((x) * (x))
#define abs(x) (((x) > 0) ? (x) : (-(x))) 
#define lowbit(x) ((x) & (-(x)))

using namespace std;

int n, length;
int a[6], buffer[6][6], sum[6], LEN[6];
char str[1000];
char visit[6][6];

inline bool check(int i, int &pos) {
	if (pos == length) {
		return true;
	}
	for(int j = 0; j < LEN[i]; j++) {
		if (buffer[i][j] == 0) {
			if (visit[i][j]) {
				if (visit[i][j] != str[pos]) {
					return false;
				}
			} else {
				visit[i][j] = str[pos];
			}
			pos++;
		} else {
			if (!check(buffer[i][j], pos)) {
				return false;
			}
		}
	}
	return true;
}

vector<int> ways, ways2;

inline bool dfs(int idx, int len, int tot) {
	if (idx == 1 && len == 0) {
		bool flag = false;
		ways.clear();
		ways.push_back(0);
		for(int i = 1; i <= a[1] && !flag; i++) {
			ways2.clear();
			for(int j = 0; j < (int)ways.size(); j++) {
				for(int k = 2; k <= n; k++) {
					if (ways[j] + sum[k] <= length) {
						ways2.push_back(ways[j] + sum[k]);
					}
				}
			}
			swap(ways, ways2);
			sort(ways.begin(), ways.end());
			ways.erase(unique(ways.begin(), ways.end()), ways.end());
			
			if (ways.size() == 0) {
				break;
			}
			if (ways.back() <= length && ways.back() + (a[1] - i) >= length) {
				flag = true;
			}
		}
		if (!flag) {
			return false;
		}
	}
	
	if (idx == 0) {
		if (sum[1] != length) {
			return false;
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < LEN[i]; ++j) {
				visit[i][j] = 0;
			}
		}
		int pos = 0;
		return check(1, pos);
	}
	
	bool ret = false;
	if (idx != 1 && len == 0) {
		sum[idx] = LEN[idx] = 0;
		if (dfs(idx - 1, 0, 0)) {
			return true;
		}
	}
	
	if (idx == 1 && len >= 1 || len > 1) {
		sum[idx] = tot;
		LEN[idx] = len;
		int app = 1;
		for(int i = idx; i <= n; i++) {
			app = max(app, sum[i]);
		}
		for(int i = 1; i < idx; i++) {
			app *= a[i];
		}
		if (app >= length && tot <= length) {
			ret |= dfs(idx - 1, 0, 0);
		}
		
		app = 1;
		for(int i = idx + 1; i <= n; i++) {
			app = max(app, sum[i]);
		}
		for(int i = 1; i <= idx; i++) {
			app *= a[i];
		}
		if (app < length) {
			return false;
		}
	}
	if (len < a[idx]) {
		for (int i = idx; i <= n && !ret; ++i) {
			if (i == idx) {
				buffer[idx][len] = 0;
				ret |= dfs(idx, len + 1, tot + 1);
			} else if (sum[i]) {
				buffer[idx][len] = i;
				ret |= dfs(idx, len + 1, tot + sum[i]);
			}
		}
	}
	return ret;
}

inline void solve() {
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		if (a[i] == 1) {
			i--;
			n--;
		}
	}
	scanf("%s", str);
	length = (int)strlen(str);
	
	if (n == 0) {
		printf("%s\n", length == 1 ? "Yes" : "No");
		return ;
	}
	int tot = a[1];
	for(int i = 2; i <= n; i++) {
		tot += a[i] - 1;
	}
	if (tot >= length) {
		printf("Yes\n");
		return;
	}
	if (n == 1) {
		printf("No\n");
		return ;
	}
	
	for(int i = 0; i < a[n]; i++) {
		buffer[n][i] = 0;
	}
	for(int len = a[n]; len >= 2; len--) {
		LEN[n] = sum[n] = len;
		if (dfs(n - 1, 0, 0)) {
			puts("Yes");
			return ;
		}
	}
	puts("No");
}

int main() {
	freopen("input.txt", "r", stdin);
	while (scanf("%d", &n) != EOF) {
		solve();
	}
	return 0;
}
