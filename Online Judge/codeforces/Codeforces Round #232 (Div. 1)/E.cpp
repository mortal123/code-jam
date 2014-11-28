#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1111111;

long long times;
vector<pair<int, int> > factor[N];
int m, n;
long long cnt[N];

int main() {
	ios::sync_with_stdio(false);
	
	m = 0;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		int x;
		long long y;
		cin >> x >> y;
		m = max(m, x);
		cnt[x] += y;
	}
	
	cin >> times;
	
	for(int i = 2; i <= m; i++) 
		if (!factor[i].size()) {
			for(int j = i; j <= m; j += i) {
				int tmp = j;
				factor[j].push_back(make_pair(i, 0));
				while(tmp % i == 0) {
					tmp /= i;
					factor[j].back().second++;
				}	
			}
		}
	
	int steps = 0, aux = m;
	while(aux) {
		steps++;
		aux /= 2;
	}
	
	steps++;
	
	for(int i = 0; i < steps && times; i++, times--) {
		static long long newCount[N];
		for(int j = 2; j <= m; j++)
			newCount[j] = cnt[j];
			
		for(int j = 2; j <= m; j++) {
			if (cnt[j]) {
				newCount[j] --;
				for(int k = 0; k < (int)factor[j - 1].size(); k++) {
					newCount[factor[j - 1][k].first] += factor[j - 1][k].second;
				}
			}
		}
		
		for(int j = 2; j <= m; j++)
			cnt[j] = newCount[j];
	}
	
	for(int i = m; i >= 2; i--) {
		long long many = min(times, cnt[i]);
		cnt[i] -= many;
		for(int k = 0; k < (int)factor[i - 1].size(); k++) {
			cnt[factor[i - 1][k].first] += factor[i - 1][k].second * many;
		}
	}
	
	int number = 0;
	for(int i = 2; i <= m; i++) {
		if (cnt[i] > 0)
			number++;
	}
	
	cout << number << endl;
	for(int i = 2; i <= m; i++) {
		if (cnt[i] > 0) {
			cout << i << " " << cnt[i] << endl;
		}
	}
	
	return 0;
} 
