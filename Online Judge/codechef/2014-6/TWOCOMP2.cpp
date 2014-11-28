#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int N = 111111, LOG = 18, M = 2222222; 
const int INF = 111111111;

int father[N][LOG], dep[N], dis[N];
int n, m1, m2, source, target;
vector<int> edge[N];

const int NSIZE = 2000;
const int MSIZE = 1000000;
const int OO = INF;

struct MaxFlow
{
	int e[MSIZE], succ[MSIZE], last[NSIZE], val[MSIZE], sum, tot;
	int dis[NSIZE], pre[NSIZE], gap[NSIZE];
	
	MaxFlow () {}
	
	void init (int _tot)
	{
		int i;
		tot = _tot;
		for (i = 0; i <= tot; i++)
			last[i] = dis[i] = gap[i] = 0;
		sum = 1;
	}
	
	void add(int a, int b, int c)
	{
		e[++sum] = b, succ[sum] = last[a], last[a] = sum;
		e[++sum] = a, succ[sum] = last[b], last[b] = sum;
		val[sum - 1] = c, val[sum] = 0;
	}
	
	int sap(int s, int t)
	{
		int Now, Flow, i, Ans = 0;
		gap[0] = tot;
		for (Now = s; dis[s] < tot; )
		{
			for (i = last[Now]; i != 0; i = succ[i])
				if (val[i] > 0 && dis[Now] == dis[e[i]] + 1)
				{
					pre[e[i]] = i, Now = e[i];
					break;
				}
			if (Now == t)
			{
				for (Flow = OO; Now != s; Now = e[pre[Now] ^ 1])
					Flow = min(Flow, val[pre[Now]]);
				Ans += Flow;
				for (Now = t; Now != s; Now = e[pre[Now] ^ 1])
					val[pre[Now]] -= Flow, val[pre[Now] ^ 1] += Flow;
			}
			
			else if (i == 0)
			{
				if (gap[dis[Now]] == 1)
					return Ans;
				for (Flow = tot, i = last[Now]; i != 0; i = succ[i])
					if (val[i] > 0 && dis[e[i]] + 1 < Flow)
						Flow = dis[e[i]] + 1;
				gap[dis[Now]]--, gap[Flow]++, dis[Now] = Flow;
				if (Now != s)
					Now = e[pre[Now] ^ 1];
			}
		}
		
		return Ans;
	}
}SAP;


void bfs(int source) {
	vector<int> queue;
	queue.push_back(source);
	father[source][0] = 0;
	dep[source] = 0;
	for(int head = 0; head < (int)queue.size(); head++) {
		int x = queue[head];
		for(int i = 0; i < (int)edge[x].size(); i++) {
			int y = edge[x][i];
			if (y == father[x][0]) {
				continue;
			}
			queue.push_back(y);
			dep[y] = dep[x] + 1;
			father[y][0] = x;
		}
	}
	for(int i = 1; i < LOG; i++)
		for(int j = 1; j <= n; j++) {
			father[j][i] = father[father[j][i - 1]][i - 1];
		}
}

int getLCA(int a, int b) {
	if (dep[a] < dep[b]) {
		swap(a, b);
	}
	for(int i = LOG - 1; i >= 0; i--) {
		if (dep[a] - (1 << i) >= dep[b])
			a = father[a][i];
	}
	if (a == b)
		return a;
	for(int i = LOG - 1; i >= 0; i--) {
		if (father[a][i] != father[b][i]) {
			a = father[a][i];
			b = father[b][i];
		}
	}
	return father[a][0];
}

int jump(int a, int b) {
	for(int i = LOG - 1; i >= 0; i--) {
		if (b >> i & 1) {
			a = father[a][i];
		}
	}
	return a;
}

inline bool isUpper(int a, int b) {
	if (dep[a] > dep[b])
		return 0;
	return jump(b, dep[b] - dep[a]) == a;
}

int onLine(int a, int b, int c, int d) {
	if (!isUpper(d, a))
		return 0;
	if (isUpper(a, b) || isUpper(a, c))
		return 1;
	return 0;
}



int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &n, &m1, &m2);
	for(int i = 1; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	source = m1 + m2 + 1;
	target = m1 + m2 + 2;
	SAP.init(target);
	bfs(1);
	vector<pair<int, int> > paths;
	int ans = 0;
	for(int i = 1; i <= m1; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		paths.push_back(make_pair(a, b));
		SAP.add(source, i, c);
		ans += c;
	}
	for(int i = 1; i <= m2; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		for(int j = 0; j < m1; j++) {
			int c = paths[j].first, d = paths[j].second;
			int lab = getLCA(a, b), lcd = getLCA(c, d);
			if (onLine(lab, c, d, lcd) || onLine(lcd, a, b, lab)) {
				SAP.add(j + 1, i + m1, INF);
			}
		}
		SAP.add(i + m1, target, c);
		ans += c;
	}
	ans -= SAP.sap(source, target);
	printf("%d\n", ans);
	return 0;
}
