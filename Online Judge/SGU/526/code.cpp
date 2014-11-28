#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;

const int MAXN = 6100;
const double inf = 1e100;
const double eps = 1e-12;

struct Stone {
	double l, r, t;
	Stone(double l, double r, double t) : l(l), r(r), t(t) {}
	int hit(double pos) {
		if (pos > l + eps && pos < r - eps)
			return 1;
		return 0;
	}
};

struct PT {
	double time, pos, lastHit;
	PT(double time, double pos) : time(time), pos(pos) {
		lastHit = -inf;
	}
	
	friend int operator<(const PT &a, const PT &b) {
		if (fabs(a.time - b.time) > eps)
			return a.time < b.time;
		return a.pos + eps < b.pos;
	}
	
	friend int operator ==(const PT &a, const PT &b) {
		if (fabs(a.time - b.time) < eps && fabs(a.pos - b.pos) < eps)
			return 1;
		return 0;
	}
};


int sign(double a) {
	return a < eps ? -1 : a > eps;
}

vector<PT> vec;
vector<Stone> stones;
double G, vmax;
int n;
bool flag = false;
double ans = inf;
int last;
int pre[MAXN], visit[MAXN];
vector<int> anss;
vector<pair<double, double> > ansss;

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%lf %lf %d", &vmax, &G, &n);
	vec.push_back(PT(0, 0));
	vec.push_back(PT(inf, G));
	for(int i = 1; i <= n; i++) {
		double l, r, t;
		scanf("%lf %lf %lf", &l, &r, &t);
		stones.push_back(Stone(l, r, t));
		vec.push_back(PT(t, l));
		vec.push_back(PT(t, r));
	}
	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	for(int i = 0; i < vec.size(); i++) {
		for(int j = 0; j < stones.size(); j++)
			if (stones[j].hit(vec[i].pos) && stones[j].t < vec[i].time + eps) {
				vec[i].lastHit = max(vec[i].lastHit, stones[j].t);
			}
	}
	vec[vec.size() - 1].lastHit = -inf;
	visit[0] = 1;
	for(int i = 0; i < vec.size(); i++) {
		if (!visit[i])
			continue;
		double pos, lt = inf, rt = inf;
		for(int j = 0; j < stones.size(); j++) {
			if (stones[j].t + eps < vec[i].time)
				continue;
			pos = vec[i].pos + vmax * (stones[j].t - vec[i].time);
			if (stones[j].hit(pos))
				rt = min(rt, stones[j].t);
				
			pos = vec[i].pos - vmax * (stones[j].t - vec[i].time);
			if (stones[j].hit(pos))
				lt = min(lt, stones[j].t);
		}
		for(int j = i + 1; j < vec.size(); j++) {
			if (j != vec.size() - 1 && visit[j]) 
				continue;
			double needTime = fabs(vec[i].pos - vec[j].pos) / vmax;
			double arriveTime = needTime + vec[i].time;
			if (arriveTime > vec[j].time + eps || arriveTime < vec[j].lastHit + eps)
				continue;
			if (vec[j].pos > vec[i].pos && arriveTime > rt + eps || vec[j].pos < vec[i].pos && arriveTime > lt + eps)
				continue;
			visit[j] = 1;
			if (j == vec.size() - 1) {
				if (arriveTime < ans) {
					ans = arriveTime;
					pre[j] = i;
				}
			} else {
				pre[j] = i;
			}
		}
	}
	if (!visit[vec.size() - 1])
		printf("-1\n");
	else {
		int now = vec.size() - 1;
		vec[now].time = ans;
		while(now) {
			anss.push_back(now);
			now = pre[now];
		}
		reverse(anss.begin(), anss.end());
		int p = 0;
		for(int i = 0; i < anss.size(); i++) {
			int now = anss[i];
			if (fabs(vec[now].pos - vec[p].pos) > eps)
				ansss.push_back(make_pair(sign(vec[now].pos - vec[p].pos) * vmax, fabs(vec[now].pos - vec[p].pos) / vmax));
			double t = vec[now].time - vec[p].time - fabs(vec[now].pos - vec[p].pos) / vmax;
			if (t > eps)
				ansss.push_back(make_pair(0, t));
			p = now;
		}
		printf("%d\n", ansss.size());
		for(int i = 0; i < ansss.size(); i++) {
			printf("%.12lf %.12lf\n", ansss[i].first, ansss[i].second);
		}
	}
}
