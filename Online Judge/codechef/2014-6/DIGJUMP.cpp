#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
using namespace std;

const int N = 111111;

set<int> pos[10];
int f[N];
char buf[N];
vector<int> queue;

int main() {
	scanf("%s", buf);
	int n = strlen(buf);
	for(int i = 0; i < n; i++) {
		f[i] = -1;
		pos[buf[i] - '0'].insert(i);
	}	
	f[0] = 0;
	pos[buf[0] - '0'].erase(0);
	queue.push_back(0);
	for(int head = 0; head < (int)queue.size(); head++) {
		int x = queue[head];
		int v = buf[x] - '0';
		for(set<int> :: iterator it = pos[v].begin(); it != pos[v].end(); ++it) {
			queue.push_back(*it);
			f[*it] = f[x] + 1;
		}
		pos[v].clear();
		if (x < n - 1 && f[x + 1] == -1) {
			f[x + 1] = f[x] + 1;
			queue.push_back(x + 1);
			pos[buf[x + 1] - '0'].erase(x + 1);
		}
		if (x > 0 && f[x - 1] == -1) {
			f[x - 1] = f[x] + 1;
			queue.push_back(x - 1);
			pos[buf[x - 1] - '0'].erase(x - 1);
		}
	}
	printf("%d\n", f[n - 1]);
	return 0;
}
