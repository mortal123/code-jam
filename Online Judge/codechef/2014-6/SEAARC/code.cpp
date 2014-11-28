#include <cstdio>
#include <cstdlib> 
#include <algorithm>
#include <vector>
using namespace std;

const int MOD = 1000000007;
const int N = 100000;

int LIMIT, n;
int isMore[N + 10], a[N + 10];
vector<int> pos[N + 10];
int result = 0, number[N + 10], tree[N + 10], base[N + 10], ibase[N + 10];
int has[N + 10], stamp = 0;

inline void inc(int &a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
}

void solve(int color) {
	int st = 0;
	
	int last = 0, num = 0;
	for(int nxt = st; st <= n; st = nxt) {
		for(nxt = st + 1; nxt <= n && a[nxt] != color; nxt++);
		if (nxt > n)
			continue;
		++num;
		++stamp;
		for(int i = st + 1; i < nxt; i++) {
			if (has[a[i]] != stamp) {
				number[a[i]] = 1;
			} else {
				number[a[i]]++;
			}
			has[a[i]] = stamp;
		}
		++stamp;
		for(int i = st + 1; i < nxt; i++) {
			if (has[a[i]] != stamp && has[a[i]] == stamp - 1) {
				inc(last, 1LL * number[a[i]] * num % MOD * base[a[i]] % MOD);
				inc(last, MOD - 1LL * number[a[i]] * ibase[a[i]] % MOD);
				//printf("%d %d %d %d\n", a[i], i, num * base[a[i]], ibase[a[i]]);
				inc(base[a[i]], number[a[i]]);
				inc(ibase[a[i]], 1LL * num * number[a[i]] % MOD);
			}
			has[a[i]] = stamp;
		}
		inc(result, last);
	}
	
	for(int i = 1; i <= n; i++) {
		base[a[i]] = ibase[a[i]] = 0;
	}
	
	int ed = n + 1;
	last = 0; num = 0;
	for(int nxt = ed; ed >= 1; ed = nxt) {
		for(nxt = ed - 1; nxt >= 1 && a[nxt] != color; nxt--);
		if (nxt < 1)
			continue;
		++num;
		++stamp;
		for(int i = ed - 1; i > nxt; i--) {
			if (isMore[i])
				continue;
			if (has[a[i]] != stamp) {
				number[a[i]] = 1;
			} else {
				number[a[i]]++;
			}
			has[a[i]] = stamp;
		}
		++stamp;
		for(int i = ed; i > nxt; i--) {
			if (isMore[i])
				continue;
			if (has[a[i]] != stamp && has[a[i]] == stamp - 1) {
				inc(last, 1LL * number[a[i]] * num % MOD * base[a[i]] % MOD);
				inc(last, MOD - 1LL * number[a[i]] * ibase[a[i]] % MOD);
				
				inc(base[a[i]], number[a[i]]);
				inc(ibase[a[i]], 1LL * num * number[a[i]] % MOD);
			}
			has[a[i]] = stamp;
		}
		inc(result, last);
	}
	
	for(int i = 1; i <= n; i++) {
		ibase[a[i]] = 0;
		base[a[i]] = 0;
	}
}

pair<int, int> pairs[1111111 * 2];
int tot = 0;

void ins(int tree[N], int pos) {
	for(int i = pos; i <= n; i += (i & (-i))) {
		tree[i]++;
	}
}

int ask(int pos) {
	int res = 0;
	for(int i = pos; i; i ^= (i & (-i))) {
		res += tree[i];
	}
	return res;
}

long long power(long long a, long long b) {
	if (b == 0)
		return 1;
	long long tmp = power(a, b >> 1);
	if (b & 1) {
		return tmp * tmp % MOD * a % MOD;
	} else {
		return tmp * tmp % MOD;
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	LIMIT = 100;//max(10, (int)sqrt(n) / );
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		pos[a[i]].push_back(i);
	}
	for(int i = 1; i <= n; i++) {
		if ((int)pos[a[i]].size() > LIMIT) {
			isMore[i] = 1;
		} else {
			isMore[i] = 0;
		}
	}
	
	for(int i = 1; i <= N; i++) {
		if ((int)pos[i].size() > LIMIT) {
			solve(i);
			//printf("phase 1 %d %d\n", i, result);
		} else {
			int m = (int)pos[i].size();
			for(int l = 0; l < m; l++)
				for(int r = l + 1; r < m; r++) {
					pairs[tot++] = make_pair(pos[i][l], pos[i][r]);
				}
			if (m >= 4) {
				inc(result, MOD - 1LL * m * (m - 1) % MOD * (m - 2) % MOD * (m - 3) % MOD * power(24, MOD - 2) % MOD);
			}
		}
	}
	
//	printf("!!\n");
	
	sort(pairs, pairs + tot);
	/*for(int i = 0; i < tot; i++) {
		printf("%d %d\n", pairs[i].first, pairs[i].second);
	}*/
	//printf("tot = %d\n", tot);
	for(int i = 0, j = 0; i < tot; i = j) {
		for(j = i; j < tot && pairs[j].first == pairs[i].first; j++) {
			inc(result, ask(pairs[j].second - 1) - ask(pairs[j].first));
		}
		for(int k = i; k < j; k++) {
			ins(tree, pairs[k].second);
		}
	}
	printf("%d\n", result);
	return 0;
}
