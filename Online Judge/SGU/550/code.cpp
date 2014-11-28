#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <vector>
#define foreach(container,it) \
    for(typeof((container).begin()) it = (container).begin();it!=(container).end();++it)
    
using namespace std;

const int N = 222222;
const int MOD = 99990001;

set<pair<int, int> > edge[N];
pair<int, int> eglist[N];

int size[N], total, belone[N], tag[N], weight[N];
int n, useful[N];
int father[N], hash[N], timestamp;

vector<int> vec, queue, q[2];
typeof(edge[0].begin()) cur[N];

pair<int, int> probe(int source) {
	vec.clear();
	queue.clear();
	queue.push_back(source);
	father[source] = -1;
	
	for(int head = 0; head < (int)queue.size(); head++) {
		int x = queue[head];
		foreach(edge[x], it) {
			if (it->first == father[x])
				continue;
			father[it->first] = x;
			vec.push_back(it->second);
			queue.push_back(it->first);
		}
	}
}

__inline void read(int &a) {
	char ch;
	for(ch = getchar(); ch < '0' || ch > '9'; ch = getchar());
	
	a = 0;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) {
		a = a * 10 + ch - '0';
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		edge[i].clear();
	}
	
	size[total = 1] = n;
	for(int i = 1; i < n; i++) {
		int a, b;
		read(a); 
		read(b); 
		read(weight[i]);
		
		edge[a].insert(make_pair(b, i));
		edge[b].insert(make_pair(a, i));
		useful[a]++;
		useful[b]++;
		eglist[i] = make_pair(a, b);
		belone[i] = total;
	}
	
	for(int i = 1; i < n; i++) {
		int p;
		scanf("%d", &p);
		int group = belone[p], a = eglist[p].first, b = eglist[p].second;
		int w = (weight[p] + tag[group]) % MOD;
		printf("%d\n", w);
		fflush(stdout);
		
		edge[a].erase(make_pair(b, p));
		edge[b].erase(make_pair(a, p));
		
		
		q[0].clear();
		q[0].push_back(a);
		cur[a] = edge[a].begin();
		q[1].clear();
		q[1].push_back(b); 
		cur[b] = edge[b].begin();
		int stop[2] = {1, 1}, top[2] = {0, 0}, minV[2] = {a, b};
		
		hash[a] = hash[b] = ++timestamp;
		while(1) {
			for(int i = 0; i < 2; i++) {
				stop[i] = 1;
				while(top[i] >= 0) {
					int x = q[i][top[i]];
					for(typeof(edge[0].begin()) &it = cur[x]; stop[i] && it != edge[x].end(); ++it) {
						if (hash[it->first] == timestamp) {
							continue;
						}
						
						hash[it->first] = timestamp;
						minV[i] = min(minV[i], it->first);
						cur[it->first] = edge[it->first].begin();
						q[i].push_back(it->first);
						top[i]++;
						stop[i] = 0;
					}
					
					if (stop[i]) {
						top[i]--;
						q[i].pop_back();
					} else {
						break;
					}
				}
			}
			
			if (stop[0] || stop[1])
				break;
		}
		
		if (stop[0] && stop[1]) {
			if (minV[1] < minV[0])
				swap(a, b);
		} else if (stop[1]) {
			swap(a, b);
		}
		
		probe(a);
		
		tag[++total] = 0;
		size[total] = 1;
		for(int j = 0; j < (int)vec.size(); j++) {
			belone[vec[j]] = total;
			(weight[vec[j]] += tag[group]) %= MOD;
			weight[vec[j]] = 1LL * weight[vec[j]] * w % MOD;
			size[total]++;
		}
		
		(tag[group] += w) %= MOD;
		size[group] -= size[total];
		
	}
	
	return 0;
} 
