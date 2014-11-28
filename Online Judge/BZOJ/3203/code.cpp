#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
using namespace std;
typedef long long ll;

const int MAXN = 100000;

ll a[MAXN + 10], x[MAXN + 10], d;
int n;
multiset<ll> S;
int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d %lld", &n, &d);
	S.clear();
	for(int i = 1; i <= n; i++) {
		scanf("%lld %lld", &a[i], &x[i]);
	}
	int p = 1;
	long long totHp = 0;
	double ans = 0;
	for(int i = 1; i <= n; i++) {
		while(!S.empty())
		{
			set<ll> :: iterator it;
			it = S.begin();
			if ((*it) - d * i <= 0) {
				totHp -= (*it) - d * (i - 1);
				S.erase(it);
			} else {
				break;
			}
		}
		totHp -= d * S.size();
		S.insert(a[i] + d * i);
		totHp += a[i];
		ans += (double)(totHp) / x[i];
		cout << (double)totHp / x[i] << endl;
	}
	cout << ans << endl;
	return 0;
} 
