#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 210;

bool f[MAXN][MAXN];
vector<int> ans;
int length[MAXN][MAXN];

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			scanf("%d", &length[i][j]);
	memset(f, 0, sizeof(f));
	f[1][1] = true;
	int K;
	scanf("%d", &K);
	for(int i = 1; i <= K; i++) {
		int len;
		scanf("%d", &len);
		for(int j = 1; j <= n; j++)
			if (f[i][j])
				for(int k = 1; k <= n; k++)
					if (length[j][k] == len)
						f[i + 1][k] = true;
	}
	int cnt = 0;
	for(int i = 1; i <= n; i++)
		cnt += f[K + 1][i];
	printf("%d\n", cnt);
	for(int i = 1; i <= n; i++)
		if (f[K + 1][i])
			printf("%d ", i);
	return 0;
}
