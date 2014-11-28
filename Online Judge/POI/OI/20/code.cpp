#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

const int N = 111111;
const int M = 111111;
const int INF = N + 2;

set<int> para[N], sonPara[N], haveSonPara[N];
set<pair<int, int> > linked;
set<int> tempSet;
int n, m, source, costA, costB, father[N], dep[N], disB[N], son[N];

struct eglist {
	int other[M * 2], succ[M * 2], last[M * 2], sum;
	void clear() {
		fill(last, last + 2 * M, -1);
		sum = 0;
	}
	
	void addEdge(int a, int b) {
		other[sum] = b, succ[sum] = last[a], last[a] = sum++;
		other[sum] = a, succ[sum] = last[b], last[b] = sum++;
	}
};

eglist e, nte;

bool mark[M * 2];
int inUse[N], timeStamp = 0;

int main() {
	freopen("input.txt", "r", stdin);
	
	scanf("%d %d %d %d %d", &n, &m, &source, &costA, &costB);
	
	e.clear();
	nte.clear();
	
	for(int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		e.addEdge(a, b);
	}
	
	// bfs
	vector<int> queue;
	queue.push_back(source);
	fill(dep + 1, dep + n + 1, -1);
	dep[source] = 0;
	
	for(int head = 0; head < (int)queue.size(); head++) {
		int x = queue[head];
		for(int j = e.last[x]; ~j; j = e.succ[j]) {
			int y = e.other[j];
			if (dep[y] == -1) {
				son[x]++;
				dep[y] = dep[x] + 1;
				father[y] = x;
				queue.push_back(y);
				mark[j] = mark[j ^ 1] = true;
			}
		}
	}
	
	for(int i = 0; i < e.sum; i += 2) {
		if (mark[i])
			continue;
		int u = e.other[i], v = e.other[i ^ 1];
		if (dep[u] == dep[v]) {
			para[u].insert(v);
			para[v].insert(u);
			if (u != source)
				sonPara[father[u]].insert(v);
			if (v != source)
				sonPara[father[v]].insert(u);
		} else {
			nte.addEdge(u, v);
		}
	}
	
	fill(disB, disB + n + 1, INF);
	disB[source] = 0;
	for(int x = 1; x <= n; x++) {
		if (dep[x] % 2 == 0)
			continue;
		int uhCount = 0, huCount = 0, dhCount = 0, hdCount = 0;
		
		tempSet.clear();
		++timeStamp;
		for(set<int> :: iterator it = para[x].begin(); it != para[x].end(); ++it) {
			if (father[*it] != father[x])
				tempSet.insert(father[*it]);
			hdCount += son[*it];
			inUse[*it] = timeStamp;
		}
		
		for(int j = nte.last[x]; ~j; j = nte.succ[j]) {
			int y = nte.other[j];
			if (dep[y] < dep[x]) { // imply x != source
				if (para[father[x]].count(y))
					uhCount++;
				if (tempSet.count(y))
					huCount++;
			} else { // dis[y] > dis[x]
				if (inUse[father[y]] == timeStamp) {
					--hdCount;
				}
				
				if (sonPara[x].count(y)) {
					dhCount++;
				}
			}
		}
		
		if (uhCount < (int)para[father[x]].size() || huCount < (int)tempSet.size()) {
			disB[x] = (dep[x] + 1) / 2;
			continue;
		}
		
		if (dhCount < (int)sonPara[x].size() || hdCount) {
			disB[x] = (dep[x] + 1) / 2 + 1;
		}
	}
	
	for(int i = 0; i < (int)queue.size(); i++) {
		int x = queue[i];
		if (dep[x] > 1) {
			disB[x] = min(disB[x], disB[father[father[x]]] + 1);
		}
	}
	
	for(int i = (int)queue.size() - 1; i >= 0; i--) {
		int x = queue[i];
		if (dep[x] > 1) {
			disB[father[father[x]]] = min(disB[father[father[x]]], disB[x] + 1);
		}
	}
	
	for(int x = 1; x <= n; x++) {
		printf("%d\n", min(min(dep[x] * costA, dep[x] / 2 * costB + dep[x] % 2 * costA), 
			disB[x] * costB));
	}
	return 0;
} 
