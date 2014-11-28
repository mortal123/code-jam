#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

const long long INF = (1LL << 60);

struct Node {
	int d[3];
	Node (int x = 0, int y = 0, int z = 0) {
		d[0] = x;
		d[1] = y;
		d[2] = z;
	}
	void print() {
		for(int i = 0; i < 3; i++) {
			printf("%d%c", d[i], i == 2 ? '\n' : ' ');
		}
	}
};

vector<Node> points;
Node s[8];
int total = 0, bit[1 << 20];
long long ds[8][8];

__inline long long sqr(long long x) {
	return x * x;
}

__inline long long calc(const Node &a, const Node &b) {
	return sqr(a.d[0] - b.d[0]) + sqr(a.d[1] - b.d[1]) + sqr(a.d[2] - b.d[2]);
}

int count(int x) {
	int result = 0;
	while(x) {
		result += (x & 1);
		x >>= 1;
	}
	return result;
}



int ok[1 << 8];
vector<Node> ways[1 << 8];

int dfs(int dep, const vector<int> &pos, vector<Node> &way) {
	if (dep == 4) {
		vector<Node> w = way;
		long long dist = min(calc(w[0], w[1]), calc(w[0], w[2]));
		for(int i = 1; i < 4; i++) {
			if (calc(w[i], w[0]) > dist) {
				swap(w[i], w[2]);
				break;
			}
		}
		/*if (pos[0] == 0 && pos[1] == 1 && pos[2] == 2 && pos[3] == 4) {
			int a, b;
			a += b;
			puts("!!");
			w[0].print();
			w[1].print();
			w[2].print();
			w[3].print();
		}*/
		return calc(w[0], w[1]) == dist && calc(w[1], w[2]) == dist && 
			calc(w[2], w[3]) == dist && calc(w[3], w[0]) == dist && calc(w[0], w[2]) == 2 * dist && calc(w[1], w[3]) == 2 * dist;
	}
	
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if (i != j) {
				for(int k = 0; k < 3; k++) {
					if (k != i && k != j) {
						way.push_back(Node(points[pos[dep]].d[i], 
							points[pos[dep]].d[j], points[pos[dep]].d[k]));
						if (dfs(dep + 1, pos, way)) {
							return 1;
						}
						way.pop_back();
					}
				}
			}
	return 0;
}

bool solve(int mask, const vector<int> &pos) {
	ways[mask].clear();
	if (dfs(0, pos, ways[mask])) {
		return true;
	} else {
		return false;
	}
}

bool check(int mask1, int mask2) {
	vector<Node> a = ways[mask1], b = ways[mask2];
	if (min(calc(a[0], a[1]), calc(a[0], a[2])) != min(calc(b[0], b[1]), calc(b[0], b[2]))) {
		return false;
	}
	long long dist = min(calc(a[0], a[1]), calc(a[0], a[2]));
	for(int i = 0; i < 4; i++) {
		bool flag = false;
		for(int j = i; j < 4; j++) {
			if (calc(a[i], b[j]) == dist) {
				swap(b[i], b[j]);
				flag = true;
				break;
			}
		}
		if (!flag) {
			return false;
		}
	}
	return true;
}

int main() {
	for(int i = 0; i < 8; i++) {
		bit[i] = count(i);
	}
	for(int i = 0; i < 8; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		points.push_back(Node(x, y, z));
	}
	for(int i = 0; i < (1 << 8); i++) {
		vector<int> pos;
		for(int j = 0; j < 8; j++) {
			if (i >> j & 1) {
				pos.push_back(j);
			}
		}
		if (pos.size() == 4) {
			ok[i] = solve(i, pos);
			if (i == 23) {
				ways[i][2].print();
				points[pos[2]].print();
			}
		} else {
			ok[i] = 0;
		}
	}
	int full = (1 << 8) - 1;
	
	printf("%d %d\n", ok[23], ok[full ^ 23]);
	
	for(int i = 0; i < (1 << 8); i++) {
		if (ok[i] && ok[full ^ i]) {
			if (check(i, full ^ i) || i == 23) {
				puts("YES");
				int cnt0 = 0, cnt1 = 0;
				for(int j = 0; j < 8; j++) {
					if (i >> j & 1) {
						ways[i][cnt0].print();
						cnt0++;
					} else {
						ways[full ^ i][cnt1].print();
						cnt1++;
					}
				}
				return 0;
			}
		}
	}
	puts("NO");
	return 0;
}

