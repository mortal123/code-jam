#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 21000;
const double eps = 1e-12;

int n, s, vmin, vmax;
vector<pair<double, int> > vec;
int visit[MAXN];

int sign(double x) {
	return x < -eps ? -1 : x > eps;
}

struct Light {
	int x, r, g, d, id;
	void read(int _id) {
		scanf("%d %d %d %d", &x, &r, &g, &d);
		if (d > g)
			d -= g + r;
		id = _id;
	}
	int _push(int t, int idd) {
		if (t <= 0)
			return vmax;
		double v = (double)x / t;
		if (idd > 0 && sign(v - vmin) >= 0 && sign(v - vmax) < 0 || idd < 0 && sign(v - vmin) > 0 && sign(v - vmax) <= 0) {
			vec.push_back(make_pair(v, idd));
		}
		return v;
	}
	void push() {
		for(int i = d; ; i += g + r) {
			if (_push(i, -id) < vmin)
				break;
			if ( _push(i + r, id) < vmin)
				break;
		}
	}
	int ask(int v) {
		double t = (double)x / v;
		for(int i = d; ; i += g + r) {
			if (i > t)
				return 0;
			if (i <= t + eps && i + g + r + eps >= t) {
				if (i + eps < t && t < i + r - eps)
					return 1;
				return 0;
			}
		}
	}
}light[MAXN];

void print(double ansV, int cnt) {
	printf("%.12lf\n", ansV);
	printf("%d\n", cnt);
	for(int j = 1; j <= n; j++)
		if (visit[j]) {
			cnt--;
			printf("%d%c", j, cnt == 0 ? '\n' : ' ');
		}
	exit(0);
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d %d %d", &n, &s, &vmin, &vmax);
	for(int i = 1; i <= n; i++) {
		light[i].read(i);
		light[i].push();
	}
	for(int i = 1; i <= n; i++)
		if (light[i].ask(vmin))
			vec.push_back(make_pair(vmin - 1, i));
	sort(vec.begin(), vec.end());
	
	int best = n + 1, cnt = 0;
	double ansV;
	for(int i = 1; i <= n; i++)
		visit[i] = 0;
	//for(int i = 0; i < vec.size(); i++)
	//	printf("(%lf, %d)\n", vec[i].first, vec[i].second);
	for(int i = 0, j; i < vec.size(); i = j) {
		double v = vec[i].first;
		j = i;
		while(j < vec.size() && fabs(vec[j].first - v) < eps && vec[j].second < 0) {
			cnt--;
			visit[-vec[j].second] = 0;
			j++;
		}
		if (cnt <= best && sign(v - vmin) >= 0) {
			best = cnt;
			ansV = v;
		}
		while(j < vec.size() && fabs(vec[j].first - v) < eps && vec[j].second > 0) {
			cnt++;
			visit[vec[j].second] = 1;
			j++;
		}
	}
	
	int ccnt = 0;
	for(int i = 1; i <= n; i++)
		ccnt += light[i].ask(vmax);
	if (ccnt <= best) {
		for(int i = 1; i <= n; i++)
			visit[i] = light[i].ask(vmax);
		print(vmax, ccnt);
	} 
	
	cnt = 0;
	for(int i = 1; i <= n; i++)
		visit[i] = 0;
	for(int i = 0, j; i < vec.size(); i = j) {
		double v = vec[i].first;
		j = i;
		while(j < vec.size() && fabs(vec[j].first - v) < eps && vec[j].second < 0) {
			cnt--;
			visit[-vec[j].second] = 0;
			++j;
		}
		if (fabs(v - ansV) < eps) {
			print(ansV, cnt);
		}
		while(j < vec.size() && fabs(vec[j].first - v) < eps && vec[j].second > 0) {
			cnt++;
			visit[vec[j].second] = 1;
			++j;
		}
	}
	return 0;
} 
