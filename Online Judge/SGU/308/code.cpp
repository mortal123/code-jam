#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <ctime>
using namespace std;

const int BOUND = 10000;
const double pi = acos(-1.0);
const double DIST = 0.01;
const double INF = 1e100;

struct Point {
	double x, y, z;
	Point(double x, double y, double z) : x(x), y(y), z(z) {}
	Point() {}
}source, target;

vector<Point> rd;
int n = BOUND;
vector<int> e[BOUND + 100];

Point randPoint() {
	double w = (double)rand() / 32768.0 * (2 * pi), z = (double)rand() / 32768.0 * 2 - 1;
	return Point(cos(w) * sqrt(1 + z * z), sin(w) * sqrt(1 + z * z), z);
}

int q[BOUND + 10];
double dis[BOUND + 100];
int visit[BOUND + 100];

__inline double calcDist(const Point &a, const Point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

__inline double calcDist2(const Point &a, const Point &b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
}

void spfa() {
	for(int i = 0; i < n; i++)
		dis[i] = INF;
	dis[0] = 0;
	q[1] = 0;
	visit[0] = 1;
	for(int head = 0, tail = 1; head != tail;) {
		head = (head + 1) % n;
		int x = q[head];
		visit[x] = 0;
		for(int i = 0; i < (int)e[x].size(); i++) {
			int y = e[x][i];
			double delta = calcDist(rd[x], rd[y]);
			if (dis[x] + delta < dis[y]) {
				dis[y] = dis[x] + delta;
				if (!visit[y]) {
					visit[y] = 1;
					tail = (tail + 1) % n;
					q[tail] = y;
				}
			}
		}
	}
}

int main() {
	scanf("%lf %lf %lf", &source.x, &source.y, &source.z);
	scanf("%lf %lf %lf", &target.x, &target.y, &target.z);
	rd.push_back(source);
	rd.push_back(target);
	for(int i = 2; i < n; i++) {
		rd.push_back(randPoint());
	}
	
	long long en = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < i; j++) {
			if (calcDist2(rd[i], rd[j]) < DIST) {
				e[i].push_back(j);
				e[j].push_back(i);
				en += 2;
			}
		}
	//printf("%I64d\n", en);
	spfa();
	printf("%.7f\n", dis[1]);
	return 0;
}
