#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int N = 55555;
const int inf = 1000000000;

int dis[N];
int buf[2][N], hash[N];
int cur, nxt;
int n, a[N];
int delta;

__inline void read(int &x) {
	static char ch;
	for(ch = getchar(); ch < '0' || ch > '9'; ch = getchar());
	x = 0;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) 
		x = x * 10 + ch - '0';
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}	
	
	for(int i = 0; i < a[n - 1]; i++)
		dis[i] = inf;
	
	dis[0] = 0;
	cur = 0;
	nxt = 1;
	buf[cur][0] = 1;
	delta = a[n - 1];
	
	if (a[0] <= 10000) {
		buf[cur][0] = 0;
		delta = a[0];
		while(1) {
			int minV = inf, c;
			for(int i = 0; i < a[0]; i++) {
				if (!hash[i] && minV > dis[i]) {
					minV = dis[i];
					c = i;
				}
			}
			
			if (minV == inf)
				break;
			hash[c] = 1;
				
			for(int i = 1; i < n; i++) {
				int aug = (c + a[i]) / a[0];
				int tar = (c + a[i]) % a[0];
				if (!hash[tar])
					dis[tar] = min(dis[tar], dis[c] + aug);
			}
		}
	}
	
	while(buf[cur][0] > 0) {
		
		buf[nxt][0] = 0;
		
		for(int head = 1; head <= buf[cur][0]; head++) {
			int x = buf[cur][head];
			for(int j = 0; j < n - 1 && x + a[j] < a[n - 1]; j++) {
				int tar = x + a[j];
				if (dis[tar] != inf)
					continue;
				dis[tar] = dis[x];
				buf[cur][++buf[cur][0]] = tar;
			}
		}
		
		for(int head = 1; head <= buf[cur][0]; head++) {
			int x = buf[cur][head];		
			for(int j = n - 2; j >= 0 && x + a[j] >= a[n - 1]; j--) {
				int tar = x + a[j] - a[n - 1];
				if (dis[tar] != inf)
					continue;
				dis[tar] = dis[x] + 1;
				buf[nxt][++buf[nxt][0]] = tar;
			}
		}
		
		swap(cur, nxt);
	}
	
	int m;
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) {
		int x;
		scanf("%d", &x);
		if (dis[x % delta] == inf) {
			printf("NIE\n");
			continue;
		} else {
			int c = x % delta;
			if (1LL * delta * dis[c] + c > x) {
				printf("NIE\n");
			} else {
				printf("TAK\n");
			}
		}
	}
	
	return 0;
}
