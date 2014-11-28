#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

const int MAXN = 1000;
const int inf = 1000000000;

string ans;
bool mirrorX, mirrorY;
int n, sx, sy, w, h, left[MAXN], right[MAXN];
vector<pair<int, int> > nodes;

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &n, &sx, &sy);
	int minx = inf, maxx = -inf, maxy = -inf, miny = inf;
	for(int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		nodes.push_back(make_pair(x, y));
		minx = min(minx, x);
		maxx = max(maxx, x);
		miny = min(miny, y);
		maxy = max(maxy, y);
	}
	if (sx > minx && sx < maxx || sy > miny && sy < maxy) {
		printf("-1\n");
		return 0;
	}
	if (sx >= maxx) {
		mirrorX = true;
		sx = -sx;
		for(int i = 0; i < nodes.size(); i++)
			nodes[i].first = -nodes[i].first;
	} 
	if (sy >= maxy) {
		mirrorY = true;
		sy = -sy;
		for(int i = 0; i < nodes.size(); i++) 
			nodes[i].second = -nodes[i].second;
	}
	maxx = -inf, maxy = -inf;
	for(int i = 0; i < nodes.size(); i++) {
		nodes[i].first -= sx;
		nodes[i].second -= sy;
		maxx = max(maxx, nodes[i].first);
		maxy = max(maxy, nodes[i].second);
	}
	minx = miny = 0;
	sx = sy = 0;
	if (!maxx)
		maxx++;
	if (!maxy)
		maxy++;
	/*	
	{
		printf("%d %d\n", sx, sy);
		for(int i = 0; i < nodes.size(); i++)
			printf("%d %d\n", nodes[i].first, nodes[i].second);	
	}
	*/
	for(int i = 0; i <= maxy; i++)
		left[i] = maxx - 1, right[i] = minx + 1;
	for(int i = 0; i < nodes.size(); i++) {
		left[nodes[i].second] = min(left[nodes[i].second], nodes[i].first);
		right[nodes[i].second] = max(right[nodes[i].second], nodes[i].first);
	}
	for(int i = maxy - 1; i >= 0; i--)
		left[i] = min(left[i], left[i + 1]);
	for(int i = 0; i < maxy - 1; i++)
		right[i] = max(right[i], left[i + 2] + 1);
	for(int i = 1; i <= maxy; i++)
		right[i] = max(right[i], right[i - 1]);
	int x = 0, y = 0;
	
	ans += 'N'; y++;
	for(int i = 1; i < maxy; i++) {
		while(x < left[i + 1]) {
			ans += 'E'; x++;
		}	
		ans += 'N'; y++; 
	}
	ans += 'E'; x++;
	while(x < right[maxy])
		ans += 'E', x++;
	ans += 'S'; y--;
	while(x > right[maxy - 1])
		ans += 'W', x--;
	for(int i = maxy - 1; i > 0; i--) {
		while(x > right[i - 1]) {
			ans += 'W'; x--;
		}
		ans += 'S'; y--;
	}
	
	while(x > 0)
		ans += 'W', x--;
	
	int area = 0;
	int px = 0, py = 0;
	x = 0, y = 0;
	for(int i = 0; i < ans.size(); i++) {
		if (ans[i] == 'E') {
			x++;
		} else if (ans[i] == 'W') {
			x--;
		} else if (ans[i] == 'N') {
			y++;
		} else if (ans[i] == 'S') {
			y--;
		}
		area += px * y - x * py;
		px = x; py = y;
	}
	printf("%d\n", -area / 2);
	//printf("%s", ans.c_str());
	//return 0;
	for(int i = 0; i < ans.size(); i++) {
		if (mirrorX) {
			if (ans[i] == 'E')
				ans[i] = 'W';
			else if (ans[i] == 'W')
				ans[i] = 'E';
		} 
		if (mirrorY) {
			if (ans[i] == 'N')
				ans[i] = 'S';
			else if (ans[i] == 'S')
				ans[i] = 'N';
		}
		printf("%c", ans[i]);
	}
	printf("\n");
	return 0;
} 
