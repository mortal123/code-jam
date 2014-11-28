#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

const int N = 111111;

int n, a[N];
vector<int> ans;

void solve(int delta) {
	int flag = 0, can;
	for(int i = 2; i <= n; i++) {
		if (a[i] - a[i - 1] == delta)
			continue;
		flag++;
		if (a[i] - a[i - 1] == 2 * delta) {
			can = (a[i] + a[i - 1]) / 2;
		} else {
			flag++;
		}
	}
	
	if (!flag) {
		ans.push_back(a[1] - delta);
		ans.push_back(a[n] + delta);
	} else if (flag == 1) {
		ans.push_back(can);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	
	if (n == 1) {
		printf("-1\n");
		return 0;
	}
	
	sort(a + 1, a + n + 1);
	solve(a[2] - a[1]);
	solve((a[2] - a[1]) / 2);
	
	sort(ans.begin(), ans.end());
	ans.erase(unique(ans.begin(), ans.end()), ans.end());
	
	printf("%d\n", (int)ans.size());
	if (!(int)ans.size())
		return 0;
	for(int i = 0; i < (int)ans.size(); i++) {
		printf("%d ", ans[i]);
	}
	printf("\n");
	
	return 0;
} 
