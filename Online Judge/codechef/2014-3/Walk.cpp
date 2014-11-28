#include <iostream>
#include <algorithm>
using namespace std;

int test;

int main() {
	ios::sync_with_stdio(false);
	cin >> test;
	while(test--) {
		int ans = 0;
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++) {
			int x;
			cin >> x;
			ans = max(ans, x + i - 1);
		}
		cout << ans << endl;
	}
	
	return 0;
}
