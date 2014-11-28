#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

const int MAXN = 110000, MAXM = 1100000;

int n, m, type[MAXN], dgr[MAXN];

struct eglist {
	int other[MAXM], succ[MAXM], last[MAXM], sum;
	void AddEdge(int a, int b) {
		other[++sum] = b, succ[sum] = last[a], last[a] = sum;
	}
	void clear(int n) {
		for(int i = 0; i <= n; i++)
			last[i] = 0; 
		sum = 0;
	}
}e;

int q[3][MAXN], head[3], tail[3];

int insert(int x) {
	q[type[x]][++tail[type[x]]] = x;
}

int Solve(int first) {
	for (int i = 1; i <= n; i++)
		dgr[i] = 0;
	for(int x = 1; x <= n; x++)
		for(int i = e.last[x]; i; i = e.succ[i])
			dgr[e.other[i]]++;

	for(int i = 1; i <= 2; i++)
		head[i] = 0, tail[i] = 0;
	for(int i = 1; i <= n; i++)
		if (dgr[i] == 0) {
			insert(i);
		}	
	//cout << tail[1] + tail[2] << endl;
	int res = 0;
	while(head[1] < tail[1] || head[2] < tail[2]) {
		int x;
		if (head[first] < tail[first]) {
			x = q[first][++head[first]];
			for(int i = e.last[x]; i; i = e.succ[i]) {
				int y = e.other[i];
				dgr[y]--;
				if (dgr[y] == 0)
					insert(y);
			}
		} else {
			first = 3 - first;
			res++;
		}
	}
	//cout << tail[1] + tail[2] << endl;
	if (tail[1] + tail[2] != n)
		return int(1e9);
	return res;
}

int main() {
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	scanf("%d %d", &n, &m);
	e.clear(n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &type[i]);
	}
	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		e.AddEdge(a, b);
	}
	int ans = Solve(1);
	ans = min(ans, Solve(2));
	assert(ans != int(1e9));
	cout << ans << endl;
	return 0;
} 
