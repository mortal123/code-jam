#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int N = 55, M = 111;

struct Node {
	int maxLength;
	vector<int> ways;
	bool operator <(const Node &o) const {
		return maxLength < o.maxLength;
	}
};

vector<int> ans;
Node f[N][N * M * 4];
vector<int> vec;
int n, h[N], total = 0, maxV = -1, sum[N];

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &h[i]);
		total += abs(h[i] - h[i - 1]);
		total += 2;
		sum[i] = sum[i - 1] + h[i];
	}
	total += h[n];
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= total; j++) {
			f[i][j].maxLength = -1;
		}
	f[0][0].maxLength = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j <= total; j++)
			if (f[i][j].maxLength != -1) {
				for(int k = i + 1; k <= n; k++) {
					int cost = j + abs(h[k] - h[i]) + 2;
					if (f[i][j].maxLength + sum[k - 1] - sum[i] > f[k][cost].maxLength) {
						f[k][cost] = f[i][j];
						f[k][cost].maxLength += sum[k - 1] - sum[i];
						f[k][cost].ways.push_back(k);
					}
					if ((cost + h[k]) * 2 >= total) {
						if (f[k][cost].maxLength + sum[n] - sum[k] > maxV) {
							maxV = f[k][cost].maxLength + sum[n] - sum[k];
							ans = f[k][cost].ways;
						}
					}
				}
			}
	printf("%d\n", maxV);
	
	printf("%d\n", n - (int)ans.size());
	static int hash[N];
	for(int i = 1; i <= n; i++)
		hash[i] = 0;
	for(int i = 0; i < (int)ans.size(); i++)
		hash[ans[i]] = 1;
	for(int i = 1, cnt = 0; i <= n; i++) {
		if (hash[i])
			continue;
		printf("%d%c", i, ++cnt == n - (int)ans.size() ? '\n' : ' ');
	}
	return 0;
} 
