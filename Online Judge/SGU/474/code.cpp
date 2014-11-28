#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 222222;

struct Triple {
	int x, y, sign;
	Triple(int x, int y, int sign) : x(x), y(y), sign(sign) {}
	
	Triple() {}
	
	friend inline int operator < (const Triple &a, const Triple &o) {
		return a.x < o.x || a.x == o.x && a.y < o.y || 
			a.x == o.x && a.y == o.y && a.sign < o.sign;
	}
	
	void show() {
		printf("x = %d y = %d sign = %d\n", x, y, sign);
	}
};

struct Point {
	int x, y;
	
	Point(int x, int y) : x(x), y(y) {}
	
	Point() {}
	
	inline int operator < (const Point &o) {
		return x < o.x || x == o.x && y < o.y;
	}
	
	inline int operator == (const Point &o) {
		return x == o.x && y == o.y;
	}
	
	inline Point operator - (const Point &o) {
		return Point(x - o.x, y - o.y);
	}
};

long long det(const Point &a, const Point &b) {
	return 1LL * a.x * b.y - 1LL * a.y * b.x;
}

long long dot(const Point &a, const Point &b) {
	return 1LL * a.x * b.x + 1LL * a.y * b.y;
}

long long abss(long long x) {
	if (x < 0)
		return -x;
	return x;
}

vector<Triple> compare;
vector<Triple> tmp;

Point tri[N][3];
int n, m;

int check(vector<Triple> &s) {
	sort(s.begin(), s.end());
	//for(int i = 0; i < (int)s.size(); i++)
	//	s[i].show();
	//printf("\n");
	for(int i = 0, j = 0, k = 0; i < (int)s.size(); i = j) {
		int cnt = 0;
		for(j = i; j < (int)s.size() && s[j].x == s[i].x; j = k) {
			for(k = j; k < (int)s.size() && s[k].x == s[j].x && s[k].y == s[j].y; k++) {
				cnt -= s[k].sign;
			}
			
			if (cnt != 0 && cnt != 2)
				return 0;
		}
	}
	
	return 1;
}

void add(vector<Triple> &s, int a, int b, int c) {
	if (b > c)
		swap(b, c);
	s.push_back(Triple(a, b, -1));
	s.push_back(Triple(a, c, 1));
}

int solve() {
	scanf("%d %d", &m, &n);
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < 3; j++) {
			scanf("%d %d", &tri[i][j].x, &tri[i][j].y);
		}
	}	
	
	long long totalArea = 0;	
	
	for(int i = 1; i <= n; i++) {
		//printf("process at %d\n", i);
		totalArea += abss(det(tri[i][1] - tri[i][0], tri[i][2] - tri[i][0]));
		bool flag = false;
		for(int j = 0; j < 3; j++) {
			swap(tri[i][j], tri[i][0]);
			if (dot(tri[i][1] - tri[i][0], tri[i][2] - tri[i][0]) == 0) {
				flag = true;
				break;
			}
		}
		
		if (!flag)
			return 0;
		
		if ((tri[i][1] - tri[i][0]).x == 0)
			swap(tri[i][1], tri[i][2]);
		
		if ((tri[i][1] - tri[i][0]).y != 0 || (tri[i][2] - tri[i][0]).x != 0)
			return 0;
		
		if (abss((tri[i][1] - tri[i][0]).x) != abss((tri[i][2] - tri[i][0]).y))
			return 0;
			
		for(int j = 0; j < 3; j++) {
			if (tri[i][j].x >= 0 && tri[i][j].y >= 0 && tri[i][j].x + tri[i][j].y <= m)
				continue;
			else {
				return 0;
			}	
		}
	}
	
	if (totalArea != 1LL * m * m)
		return 0;
	
	tri[n + 1][0] = Point(0, 0);
	tri[n + 1][1] = Point(m, 0);
	tri[n + 1][2] = Point(0, m);
	
	compare.clear();
	for(int i = 1; i <= n + 1; i++) {
		add(compare, tri[i][0].x, tri[i][0].y, tri[i][2].y);
		//compare.push_back(Triple(tri[i][0].x, tri[i][0].y, -1));
		//compare.push_back(Triple(tri[i][2].x, tri[i][2].y, 1));
	}
	
	if (!check(compare))
		return 0;
	
	compare.clear();
	for(int i = 1; i <= n + 1; i++) {
		add(compare, tri[i][0].y, tri[i][0].x, tri[i][1].x);
		//compare.push_back(Triple(tri[i][0].y, tri[i][0].x, -1));
		//compare.push_back(Triple(tri[i][1].y, tri[i][1].x, 1));
	}
	
	if (!check(compare))
		return 0;
	
	for(int i = 1; i <= n; i++) {
		if (tri[i][1].y > tri[i][2].y)
			swap(tri[i][1], tri[i][2]);
	}
	
	compare.clear();
	for(int i = 1; i <= n + 1; i++) {
		if (tri[i][1].x < tri[i][2].x) {
			add(compare, tri[i][1].x - tri[i][1].y, tri[i][1].x + tri[i][1].y, tri[i][2].x + tri[i][2].y);
			//compare.push_back(Triple(tri[i][1].x - tri[i][1].y, tri[i][1].x + tri[i][1].y, -1));
			//compare.push_back(Triple(tri[i][2].x - tri[i][2].y, tri[i][2].x + tri[i][2].y, 1));
		}
	}
	
	if (!check(compare))
		return 0;
	
	compare.clear();
	for(int i = 1; i <= n + 1; i++) {
		if (tri[i][1].x > tri[i][2].x) {
			add(compare, tri[i][2].x + tri[i][2].y, tri[i][2].x - tri[i][2].y, tri[i][1].x - tri[i][1].y);
			//compare.push_back(Triple(tri[i][2].x + tri[i][2].y, tri[i][2].x - tri[i][2].y, -1));
			//compare.push_back(Triple(tri[i][1].x + tri[i][1].y, tri[i][1].x - tri[i][1].y, 1));
		}
	}
	
	if (!check(compare))
		return 0;
	
	return 1;
}

int main() {
	freopen("input.txt", "r", stdin);
	int test;
	scanf("%d", &test);
	while(test--) {
		printf("%s\n", solve() ? "YES" : "NO");		
	}
	
	return 0;
} 
