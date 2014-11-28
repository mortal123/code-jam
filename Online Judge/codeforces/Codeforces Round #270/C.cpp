#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int N = 111111;

int n, idx;
pair<string, string> a[N];
string pre;

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i = 1; i <= n; ++i) {
		cin >> a[i].first >> a[i].second;
	}
	for(int i = 1; i <= n; ++i) {
		cin >> idx;
		if(i == 1) {
			pre = min(a[idx].first, a[idx].second);
		} else {
			bool ok = false;
			if(a[idx].first > pre) {
				pre = a[idx].first;
				ok = true;
			}
			if((!ok && a[idx].second > pre) || (ok && a[idx].second < pre)) {
				pre = a[idx].second;
				ok = true;
			}
			if(!ok) {
				cout << "NO" << endl;
				return 0;
			}
		}
	}
	cout << "YES" << endl;
	return 0;
}
