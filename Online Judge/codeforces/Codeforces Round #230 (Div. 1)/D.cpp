#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
using namespace std;

vector<int> numbers;

const int N = 111111;
const int INF = 11111111;
const int DEBUG = 0;

int n;
int a[3][N], pos[3][N * 3];
set<int> appear[3];
set<pair<int, int> > s;
map<int, int> trash;
priority_queue<int> value;
int start[3] = {0};

void assert(bool flag) {
	if (!flag) {
		printf("over\n");
		exit(0);
	}
}

void readArray(int a[], int n) {
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		numbers.push_back(a[i]);
	}
}

int hash[N * 3];

void erase(pair<int, int> del) {
	set<pair<int, int> > :: iterator it, it1, it2;
	it = s.lower_bound(del);
	//assert(it != s.begin());
	it1 = it; 
	it1++;
	//assert(it1 != s.end());
	trash[it->first + it1->second]++;
	it2 = it;
	it2--;
	trash[it2->first + it->second]++;
	value.push(-(it2->first + it1->second));
	s.erase(del);
} 

void insert(int a, int b, bool sensive = true) {
	pair<int, int> temp = make_pair(a, b);
	if (sensive)
		temp = make_pair(a ? a : INF, b ? b : INF);
		
	set<pair<int, int> > :: iterator it;
	it = s.lower_bound(temp);
	//assert(it != s.end());
	if (it->second >= temp.second)
		return ;
	while(1) {
		it = s.upper_bound(temp);
		//assert(it != s.begin());
		--it;
		if (it->second <= temp.second) {
			erase(*it);
		} else {
			break;
		}
	}
	
	it = s.upper_bound(temp);
	//assert(it != s.end());
	int t = it->second;
	pair<int, int> later = *it;
	//assert(it != s.begin());
	--it;
	t += it->first;
	trash[t]++;
	
	value.push(-(later.second + temp.first));
	value.push(-(it->first + temp.second));
	
	s.insert(temp);
}

int getMin() {
	while(!value.empty()) {
		int x = -value.top();
		if (trash[x]) {
			trash[x]--;
			value.pop();
		} else {
			return x;
		}
	}
	//assert(false);
}

void show(int a[]) {
	for(int i = 1; i <= n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int main() {
	freopen("input.txt", "r", stdin);
	
	scanf("%d", &n);
	for(int i = 0; i < 3; i++)
		readArray(a[i], n);
	
	sort(numbers.begin(), numbers.end());
	numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < 3; j++) {
			a[j][i] = lower_bound(numbers.begin(), numbers.end(), a[j][i]) - numbers.begin();
			appear[j].insert(a[j][i]);
		}
	}
	
	if (DEBUG) {
		show(a[0]);
		show(a[1]);
		show(a[2]);
	}
	
	for(int i = 0; i < 3; i++) {
		for(int j = 1; j <= n; j++) {
			if (hash[a[i][j]] == 0) {
				hash[a[i][j]] = 1;
				pos[i][a[i][j]] = j;
			} else {
				a[i][j] = -1;
			}
		}
		
		for(int j = 1; j <= n; j++)
			if (a[i][j] >= 0)
				hash[a[i][j]] = 0;
	}
	
	for(int i = 1; i <= n; i++) {
		if (a[1][i] != -1 && !appear[0].count(a[1][i]) && !appear[2].count(a[1][i]))
			start[1] = i;
		if (a[2][i] != -1 && !appear[1].count(a[2][i]) && !appear[0].count(a[2][i]))
			start[2] = i;
	}
	
	s.insert(make_pair(0, INF + 1));
	s.insert(make_pair(INF + 1, 0));
	value.push(0);
	insert(start[1], INF, 0);
	insert(INF, start[2], 0);	
	
	vector<int> list;
	for(int i = 1; i <= n; i++) {
		if (i > start[1] && a[1][i] >= 0)
			list.push_back(a[1][i]);
		if (i > start[2] && a[2][i] >= 0)
			list.push_back(a[2][i]);
	}
	
	sort(list.begin(), list.end());
	list.erase(unique(list.begin(), list.end()), list.end());
	for(int i = 0; i < (int)list.size(); i++) {
		if (!appear[0].count(list[i]))
			insert(pos[1][list[i]], pos[2][list[i]]);
	}
	
	int ans = INF;
	
	for(int i = n; i >= 0; i--) {
		if (DEBUG) {
			printf("step %d\n", i);
			for(set<pair<int, int> > :: iterator it = s.begin(); it != s.end(); ++it) {
				printf("(%d, %d) ", it->first, it->second);
			}
			printf("\n");
		}
		ans = min(ans, i + getMin());
		if (a[0][i] == -1)
			continue;
		if (!appear[1].count(a[0][i]) && !appear[2].count(a[0][i]))
			break;
		if (i > 0)
			insert(pos[1][a[0][i]], pos[2][a[0][i]]);
	}
	
	printf("%d\n", ans);
	
	return 0;
} 
