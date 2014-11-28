#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

const int N = 1111;
const double eps = 1e-8;
const int INF = 1000000000;

struct Point {
	double x, y;
	Point(double x, double y) : x(x), y(y) {}
	Point() {}
	
	friend int operator <(const Point &a, const Point &b) {
		if (fabs(a.x - b.x) < eps)
			return a.y < b.y;
		return a.x < b.x;
	}
	
	inline friend Point operator +(const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y);
	}
	
	inline friend Point operator -(const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	} 
	
	inline friend Point operator *(const Point &a, double b) {
		return Point(a.x * b, a.y * b);
	}
	
	inline friend Point operator /(const Point &a, double k) {
		return Point(a.x / k, a.y / k);
	}
}ss[N], tt[N];

double times[2][N];

double det(Point a, Point b) {
	return a.x * b.y - b.x * a.y;
}

Point intersect(Point a, Point b, Point c, Point d) {
	double s1 = det(b - a, c - a);
	double s2 = det(b - a, d - a);
	
	if (fabs(s1 - s2) < eps) {
		return Point(INF, INF);
	}
	
	return (d * s1 - c * s2) / (s1 - s2);
}

struct Node {
	double t;
	Point p;
	Node(double t, Point p) : t(t), p(p) {}
	Node() {}
	
	friend int operator <(const Node &a, const Node &b) {
		if (fabs(a.t - b.t) < eps)
			return a.p < b.p;
		return a.t < b.t;
	}
};

vector<Node> events;

int n;

double calc(int i, Point s) {
	Point v = tt[i] - ss[i];
	v = v / (times[1][i] - times[0][i]);
	
	if (fabs(v.x) > eps) {
		return (s.x - ss[i].x) / v.x + times[0][i];
	} else {
		return (s.y - ss[i].y) / v.y + times[0][i];
	}
}

int eq(const Point &a, const Point &b) {
	return fabs(a.x - b.x) < eps && fabs(a.y - b.y) < eps;
}

int father[N], cnt[N];

int find(int x) {
	if (father[x] == x)
		return x;
	return father[x] = find(father[x]);
}

int main() {
	
	for(int i = 0; i < N; i++) {
		father[i] = i;
	}
	
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		double t1, x, y, t2, xx, yy;
		scanf("%lf %lf %lf %lf %lf %lf", &t1, &x, &y, &t2, &xx, &yy);
		ss[i] = Point(x, y);
		tt[i] = Point(xx, yy);
		times[0][i] = t1;
		times[1][i] = t2;
	}
	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) {
			if (i == j)
				continue;
			Point s = intersect(ss[i], tt[i], ss[j], tt[j]);
			
			if (fabs(s.x - INF) < eps && fabs(s.y - INF) < eps)
				continue;
			
			double ret1 = calc(i, s);
			double ret2 = calc(j, s);
			father[find(i)] = find(j);
		}
	
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		find(i);
		cnt[father[i]]++;
		ans = max(ans, cnt[father[i]]);
	}
	
	printf("%d\n", ans);
	return 0;
}
