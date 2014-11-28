#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
using namespace std;

const double eps = 1e-8, inf = 1e60, pi = acos(-1.0);
const int N = 155, M = N * N * 2;;

struct Point {
	double x, y;
	Point(double x, double y) : x(x), y(y) {}
	Point() {}
	friend inline Point operator -(const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	double arg() {
		return atan2(y, x);
	}
	friend inline bool operator != (const Point &a, const Point &b) {
		return fabs(a.x - b.x) > eps || fabs(a.y - b.y) > eps;
	}
};

struct eglist {
	int sum, other[M], succ[M], last[M];
	double cost[M];
	void clear() {
		memset(last, -1, sizeof(last));
		sum = 0;
	}
	void addEdge(int a, int b, double c) {
		other[++sum] = b, succ[sum] = last[a], last[a] = sum, cost[sum] = c;
	}
}e;

double calcDist(Point a, Point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int map[N];

struct Component {
	vector<Point> points;
	int map[N][N];
	vector<pair<int, pair<int, int> > > warp;
	int startID;
	void clear() {
		points.clear();
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				map[i][j] = 0;
		warp.clear();
	}
	void solveID(int &start) {
		startID = start;
		start += (int)points.size();		
	}
	Point calcCenter() {
		Point center;
		center.x = center.y = 0;
		for(int i = 0; i < (int)points.size(); i++) {
			center.x += points[i].x;
			center.y += points[i].y;
		}
		center.x /= (int)points.size();
		center.y /= (int)points.size();
		return center;
	}
	vector<pair<pair<double, double>, int> > sortedPoint(Point center) {
		vector<pair<pair<double, double>, int> > pot;
		for(int i = 0; i < (int)points.size(); i++) {
			pot.push_back(make_pair(make_pair((points[i] - center).arg(), calcDist(points[i], center)), i));
		}
		sort(pot.begin(), pot.end());
		return pot;
	}
	void solve();
}block[N];

void Component::solve() {
	for(int x = 0; x < (int)points.size(); x++)
		for(int y = 0; y < (int)points.size(); y++) {
			if (map[x][y]) 
				e.addEdge(startID + x, startID + y, calcDist(points[x], points[y]));
		}
	for(int i = 0; i < (int)warp.size(); i++) {
		e.addEdge(startID + warp[i].first, block[warp[i].second.first].startID + warp[i].second.second, 0);
	}
}

pair<int, pair<int, int> > make_triple(int a, int b, int c) {
	return make_pair(a, make_pair(b, c));
}

int totID;
int n;
int ma[N], mb[N];

double norm(double x) {
	if (x < 0)
		x += 2 * pi;
	if (x + eps > 2 * pi)
		x -= 2 * pi;
	return x;
}

bool check(Component &a, Component &b) {
	if (a.points.size() != b.points.size())
		return false;
	Point centerA = a.calcCenter(), centerB = b.calcCenter();
	vector<pair<pair<double, double>, int> > veca = a.sortedPoint(centerA);
	vector<pair<pair<double, double>, int> > vecb = b.sortedPoint(centerB);
	vector<Point> pa, pb;
	int n = (int)a.points.size();
	for(int i = 0; i < n; i++) {
		pa.push_back(a.points[i] - centerA);
		pb.push_back(b.points[i] - centerB);
		ma[veca[i].second] = i;
		mb[vecb[i].second] = i;
	}
	
	for(int ptr = 0; ptr < n; ptr++) {
		// veca[i].second   vecb[i + ptr].second;
		
		bool flag = true;
		// check vectex
		for(int i = 0; i < n && flag; i++) {
			if (fabs(veca[i].first.second - vecb[(ptr + i) % n].first.second) > eps 
			||  fabs((veca[i].first.first - veca[0].first.first) - norm(vecb[(i + ptr) % n].first.first - vecb[ptr].first.first)) > eps)
				flag = false;
		}
		// check edge
		for(int i = 0; i < n && flag; i++)
			for(int j = 0; j < n && flag; j++) {
				int vx = vecb[(ma[i] + ptr) % n].second, vy = vecb[(ma[j] + ptr) % n].second;
				if (a.map[i][j] && !b.map[vx][vy]) {
					flag = false;
				}
				vx = veca[(mb[i] + n - ptr) % n].second, vy = veca[(mb[j] + n - ptr) % n].second;
				if (b.map[i][j] && !a.map[vx][vy]) {
					flag = false;
				}
			}
		if (flag) {
			for(int i = 0; i < n; i++) {
				int ai = a.startID + veca[i].second, bi = b.startID + vecb[(i + ptr) % n].second;
				e.addEdge(ai, bi, 0);
				e.addEdge(bi, ai, 0);
			}
			return true;
		}
	}
	return false;
	
}

double dist[N * N];
int visit[N * N], queue[N * N], from[N * N];

double spfa(int source, int target) {
	int tail = 0;
	for(int i = 0; i < totID; i++) {
		dist[i] = inf;
		visit[i] = 0;
	}
	visit[source] = 1, dist[source] = 0;
	queue[tail++] = source;
	from[source] = -1;
	for(int head = 0; head != tail; (head += 1) %= totID) {
		int x = queue[head];
		visit[x] = 0;
		for(int i = e.last[x]; ~i; i = e.succ[i]) {
			int y = e.other[i];
			if (dist[x] + e.cost[i] + eps < dist[y]) {
				dist[y] = dist[x] + e.cost[i];
				if (!visit[y]) {
					visit[y] = 1;
					from[y] = x;
					queue[tail] = y;
					(tail += 1) %= totID;
				}
			}
		}
	}
	/*
	int t = target;
	while(t != -1) {
		printf("%d %f\n", t, dist[t]);
		t = from[t];
	}*/
	if (dist[target] > inf / 2) {
		return -1;
	} else {
		return dist[target];
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	while(scanf("%d", &n) == 1 && n) {
		totID = 0;
		e.clear();
		for(int i = 0; i < n; i++) {
			block[i].clear();
			int A, B, C;
			scanf("%d", &A);
			for(int j = 0; j < A; j++) {
				double x, y;
				scanf("%lf %lf", &x, &y);
				block[i].points.push_back(Point(x, y));
			}
			scanf("%d", &B);
			for(int j = 0; j < B; j++) {
				int x, y;
				scanf("%d %d", &x, &y);
				x--; y--;
				block[i].map[x][y] = block[i].map[y][x] = 1;
			}
			scanf("%d", &C);
			for(int j = 0; j < C; j++) {
				int x, y, z;
				scanf("%d %d %d", &x, &y, &z);
				x--, y--, z--;
				block[i].warp.push_back(make_triple(x, y, z));
			}
			block[i].solveID(totID);
		}
		for(int i = 0; i < n; i++)
			block[i].solve();
		for(int i = 0; i < n; i++)
			for(int j = i + 1; j < n; j++) {
				if (check(block[i], block[j])) {
					//printf("%d %d yes\n", i, j);
				}
			}
		int sl, sd, tl, td;
		scanf("%d %d %d %d", &sl, &sd, &tl, &td);
		sl--; sd--; tl--; td--;
		printf("%.10f\n", spfa(block[sl].startID + sd, block[tl].startID + td));
	}
	return 0;
} 
