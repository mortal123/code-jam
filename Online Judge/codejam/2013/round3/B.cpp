#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 40;

int N;
int area;
struct node
{
	int x, y, num;
	friend int operator <(node a, node b)
	{
		if (a.x != b.x)
			return a.x < b.x;
		return a.y < b.y;
	}
}p[MAXN], w[MAXN], sta[MAXN], zero;

int cross(node a, node b, node c)
{
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

int calc_area(node p[], int n)
{
	for(int i = 1; i <= n; i++)
		w[i] = p[i];
	sort(w + 1, w + n + 1);
	int top = 0;
	for(int i = 1; i <= n; i++) {
		while(top > 2 && cross(sta[top - 1], sta[top], w[i]) >= 0)
			top--;
		sta[++top] = w[i];
	}
	int t = top;
	for(int i = n - 1; i >= 1; i--) {
		while(top > t && cross(sta[top - 1], sta[top], w[i]) >= 0)
			top--;
		sta[++top] = w[i];
	}
	sta[0] = sta[top];
	int res = 0;
	for(int i = 1; i <= top; i++)
		res += cross(zero, sta[i - 1], sta[i]);
	if (res < 0)
		res = -res;
	return res;
}

int ch[MAXN];

int intersect(node a, node b, node c, node d)
{
	if (cross(a, b, c) == cross(a, b, d))
		return 0;
	if (cross(a, b, c) * cross(a, b, d) >= 0)
		return 0;
	if (cross(c, d, a) * cross(c, d, b) >= 0)
		return 0;
	return 1;
}

int dis(node a, node b)
{
	int x = a.x - b.x;
	int y = a.y - b.y;
	return x * x + y * y;
}

int in_seg(node a, node b, node c)
{
	if (cross(a, b, c) == 0 && dis(a, c) < dis(a, b) && dis(b, c) < dis(b, a) && dis(a, c) > 0)
		return 1;
	return 0;
}

int check() {
	sta[0] = sta[N]; 
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
			if (intersect(sta[i - 1], sta[i], sta[j - 1], sta[j]))
				return 0;
	int res = 0;
	for(int i = 1; i <= N; i++)
		res += cross(zero, sta[i - 1], sta[i]);
	if (res < 0)
		res = -res;
	return res;
}

int ok;

void dfs(int dep, int top) {
	if (ok)
		return;
	if (dep > N) {
		int tmp = check();
		if (tmp * 2 > area) {
			for(int i = 1; i <= N; i++) {
				printf(" %d", sta[i].num - 1);
			}
			printf("\n");
			ok = 1;
		}
		return;
	}
	for(int i = 1; i <= N; i++) {
		if (!ch[i]) {
			sta[top + 1] = p[i];
			int flag = 1;
			for(int j = 1; j <= N; j++) {
				if (ch[j] && in_seg(sta[top], p[i], p[j]))
					flag = 0;
			}
			ch[i] = 1;
			if (flag)
				dfs(dep + 1, top + 1);
			ch[i] = 0;
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int T;
	zero.x = 0; zero.y = 0;
	scanf("%d\n", &T);
	for(int t = 1; t <= T; t++) {
		printf("Case #%d:", t);
		scanf("%d", &N);
		for(int i = 1; i <= N; i++) {
			scanf("%d %d", &p[i].x, &p[i].y);
			p[i].num = i;
		}
		area = calc_area(p, N);
		for(int i = 1; i <= N; i++)
			ch[i] = 0;
		ok = 0;
		dfs(1, 0);
	}
	return 0;
}
