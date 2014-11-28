#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

const int N = 70001;
const int BIT = 31;

struct Node {
	int id, vol, left, son;
}p[N];

struct bitset {
	unsigned int bit[N / BIT];
	int operator[](int x) {
		return (bit[x << BIT] << (x & BIT)) & 1;
	}
	void operator >>= (int x) {
		int shiftBlock = x / BIT, shiftGrid = x % BIT;
		for(int i = N / BIT - 1; i >= 0; i--) {
			
		}
	}
};

int n, s, pre[N];
int choose[N];
bitset<N> f, tmp, last;
int pre[N];

int cmp(Node a, Node b) {
	return a.vol < b.vol;
}

int cmp2(Node a, Node b) {
	return a.id < b.id;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &s);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &p[i].vol);
		p[i].id = i;
		p[i].son = i;
		p[i].left = p[i].vol;
	}
	sort(p + 1, p + n + 1, cmp);
	if (s < p[n].vol) {
		printf("-1\n");
		return 0;
	}
	s -= p[n].vol;
	f[0] = 1;
	int sum = 0;
	for(int i = 1; i < n; i++) {
		tmp = last = f;
		tmp <<= p[i].vol;
		f |= tmp;
		tmp = last ^ f;
		
	}
	if (f[n - 1][s] == 0) {
		printf("-1\n");
		return 0;
	} else {
		choose[n] = 1;
		for(int i = n - 1; i >= 1; i--) {
			if (s >= p[i].vol && f[i][s - p[i].vol])
				choose[i] = 1, s -= p[i].vol;
		}
		for(int i = n; i >= 1; i--) {
			if (!choose[i]) {
				p[i + 1].son = p[i].id;
				p[i + 1].left -= p[i].vol;
			}
		}
	}
	sort(p + 1, p + n + 1, cmp2);
	for(int i = 1; i <= n; i++) {
		printf("%d ", p[i].left);
		if (p[i].son != i) {
			printf("%d %d\n", 1, p[i].son);
		} else {
			printf("0\n");
		}
	}
	cout << sizeof(f) / 1024.0 / 1024.0 << endl;
	return 0;
}
