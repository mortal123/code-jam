#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 222222;
const long long INF = (1LL << 60);

long long h[N];
int p[N], e[N];
long long sum[N];
int n, rank, killed, total = 0;
vector<int> ids[N];
vector<int> tmp;

int cmp(int a, int b) {
	return e[a] < e[b];
}

void ins(long long s[], int pos, long long v) {
	for(int i = pos; i < N; i += (i & (-i))) {
		s[i] += v;
	}
}

void insert(int id, int opt) {
	total += opt;
	ins(h, e[id], opt);
	ins(sum, e[id], opt * e[id]);
}

long long askMinKth(int number) {
	int pos = 0, now = 0;
	long long res = 0;
	for(int i = 17; i >= 0; i--) {
		if (pos + (1 << i) < N && now + (h[pos + (1 << i)]) <= number) {
			pos += (1 << i);
			now += h[pos];
			res += sum[pos];
		}
	}
	
	return res + 1LL * (number - now) * (pos + 1) - 1LL * number;
}

int main() {
	freopen("input.txt", "r", stdin);
	
	scanf("%d %d", &n, &rank);
	killed = n - (rank - 1);
	
	for(int i = 1; i <= n; i++) {
		scanf("%d %d", &p[i], &e[i]);
		e[i]++;
		ids[p[i]].push_back(i);
		insert(i, 1);
	}
	
	int upper = 0, lower = n;
	long long needed = 0, ans = INF;
	
	for(int i = 200002; i >= 0; i--) {
		tmp.clear();
		for(int j = max(0, i - 1); j <= i; j++)
			for(int k = 0; k < (int)ids[j].size(); k++) {
				tmp.push_back(ids[j][k]);
			}
		sort(tmp.begin(), tmp.end(), cmp);
		if ((int)tmp.size() + lower < killed)
			break;
			
		int defeat = max(0, killed - lower);
		long long cur = 0;
		for(int j = 0; j < defeat; j++) {
			cur += e[tmp[j]] - 1;
		}
		
		for(int j = defeat; j < (int)tmp.size(); j++) {
			insert(tmp[j], 1);
		}
		
		if (i - defeat <= total) {
			cur += askMinKth(i - defeat);
			ans = min(ans, cur);
		}
		
		for(int j = defeat; j < (int)tmp.size(); j++) {
			insert(tmp[j], -1);
		}
		
		for(int j = 0; j < ids[i].size(); j++) {
			insert(ids[i][j], 1);
			upper++;
		}
		
		if (i - 2 >= 0) {
			for(int j = 0; j < ids[i - 2].size(); j++) {
				insert(ids[i - 2][j], -1);
				lower--;
			}
		}
	}
	if (ans == INF)
		printf("-1\n");
	else
		printf("%I64d\n", ans);
	return 0;
} 
