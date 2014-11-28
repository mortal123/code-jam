#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

struct Segment {
	int a, b, c;
	Segment(int a, int b, int c) : a(a), b(b), c(c) {}
	Segment() {}
	friend int operator <(Segment a, Segment b) {
		return a.a < b.a;
	}
};

vector<Segment> ver, hor;

int n;

inline bool inRange(int &a, int &b, int &c) {
	return a >= b && a <= c;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		if (x1 > x2 || x1 == x2 && y1 > y2)
			swap(x1, x2), swap(y1, y2);
		if (x1 == x2) {
			ver.push_back(Segment(x1, y1, y2));
		} else {
			hor.push_back(Segment(y1, x1, x2));
		}
	}
	sort(hor.begin(), hor.end());
	sort(ver.begin(), ver.end());
	
	long long ans = 0;
	for(int i = 0; i < ver.size(); i++)
		for(int j = i + 1; j < ver.size(); j++) {
			if (ver[i].a < ver[j].a) {
				long long cnt = 0;
				for(int k = 0; k < hor.size(); k++)
					if (inRange(hor[k].a, ver[i].b, ver[i].c) && inRange(hor[k].a, ver[j].b, ver[j].c)
					&& inRange(ver[i].a, hor[k].b, hor[k].c) && inRange(ver[j].a, hor[k].b, hor[k].c))	
						cnt++;
				ans += cnt * (cnt - 1) / 2;
			}
		}
	cout << ans << endl;
	return 0;
}
