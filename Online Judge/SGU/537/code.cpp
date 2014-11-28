#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <ctime>
using namespace std;

const int MAXN = 10000000;

int Test;
long long Ans = 0;
int map[300], hash[300];
char str[300];
int n, cnt, m, random[200];
bool check[MAXN + 5];
vector<int> primes;
vector<long long> ans;

struct Node {
	long long a;
	int b;
	Node(long long a, int b) : a(a), b(b) {}
	Node() {}
}p[500];

long long gcd(long long a, long long b) {
	return b ? gcd(b, a % b) : a;
}

void dfsAns(int dep, long long now) {
	if (dep > m) {
		ans.push_back(now);
		return;
	}
	for(int i = 0; i <= p[dep].b; i++) {
		dfsAns(dep + 1, now);
		now *= p[dep].a;
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	srand(time(0));
	for(int i = 2; i <= MAXN; i++) {
		if (check[i])
			continue;
		primes.push_back(i);
		if ((long long)i * i > MAXN)
			continue;
		for(int j = i * i; j <= MAXN; j += i)
			check[j] = 1;
	}
	scanf("%d", &Test);
	memset(map, -1, sizeof(map));
	for(int test = 1; test <= Test; test++) {
		scanf("%s", str);
		n = strlen(str);
		cnt = 2000; Ans = 0;
		for(int i = 0; i < 10; i++)
			random[i] = i;
		while(cnt--) {
			do {
				random_shuffle(random, random + 10);
			} while(random[0] == 0);
			int j = 0;
			long long now = 0;
			for(int i = 0; str[i]; i++)
				map[str[i]] = -1;
			for(int i = 0; str[i]; i++) {
				if (map[str[i]] == -1) {
					map[str[i]] = random[j++];
				}
				now = now * 10 + map[str[i]];
			}
			Ans = gcd(Ans, now);
		}
		m = 0;
		for(int i = 0; (long long)primes[i] * primes[i] <= Ans; i++) {
			if (Ans % primes[i] != 0)
				continue;
			int a = primes[i], b = 0;
			while(Ans % a == 0)
				Ans /= a, b++;
			p[++m] = Node(a, b);
		}
		if (Ans > 1)
			p[++m] = Node(Ans, 1);
		ans.clear();
		dfsAns(1, 1);
		sort(ans.begin(), ans.end());
		printf("Case %d:", test);
		for(int i = 0; i < ans.size(); i++)
			printf(" %I64d", ans[i]);
		printf("\n");
	}
	return 0;
}
