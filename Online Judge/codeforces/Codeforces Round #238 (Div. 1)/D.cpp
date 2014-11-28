#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef pair<long long, long long> Point;

const int N = 111111;
const int M = 18;

Point p[N];
int father[N][20], n;
vector<Point> s;
int dep[N], number[N];

int calc(int a, int b) {
	if (dep[a] < dep[b])
		swap(a, b);
	for(int i = M; i >= 0; i--) {
		if (dep[a] - (1 << i) >= dep[b])
			a = father[a][i];
	}
	
	if (a == b)
		return a;
	for(int i = M; i >= 0; i--) {
		if (father[a][i] != father[b][i])
			a = father[a][i], b = father[b][i];
	}
	return father[a][0];
}

bool turn_right(Point a, Point b, Point c) {
	Point t1 = make_pair(b.first - a.first, b.second - a.second);
	Point t2 = make_pair(c.first - a.first, c.second - a.second);
	return t1.first * t2.second - t1.second * t2.first > 0;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%I64d %I64d", &p[i].first, &p[i].second);
	}
	
	for(int i = n; i >= 1; i--) {
		while((int)s.size() > 1 && turn_right(s[(int)s.size() - 1], s[(int)s.size() - 2], p[i])) {
			s.pop_back();
		}
		number[(int)s.size()] = i;
		s.push_back(p[i]);
		if (i == n)
			father[i][0] = 0, dep[i] = 0;
		else 
			father[i][0] = number[(int)s.size() - 2], dep[i] = dep[father[i][0]] + 1;
	}
	
	//for(int i = 1; i <= n; i++)
	//	printf("%d = %d\n", i, father[i][0]);
	
	for(int i = 1; i <= M; i++)
		for(int j = 1; j <= n; j++)
			father[j][i] = father[father[j][i - 1]][i - 1];
	int q;
	scanf("%d", &q);
	for(int i = 1; i <= q; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		printf("%d\n", calc(a, b));
	}
	return 0;
}
