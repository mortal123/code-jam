#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;
long long ans = 0, l, v1, v2, t;
int main()
{
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	cin >> l >> v1 >> v2 >> t;
	if (v1 < v2)
		swap(v1, v2);
	ans += v1 * t / l;
	long long a = v1 * t % (2 * l);
	long long b = v2 * t % (2 * l);
	if ((a < l && b < l && a + b >= l) || 
		(a < l && b >= l && b - l <= a) || 
		(a >= l && b >= l && a + b >= 3 * l) || 
		(a >= l && b < l && a - l >= b))
		ans++;
	a = v1 / __gcd(v1, v2);
	b = v2 / __gcd(v1, v2);
	if ((a % 2) ^ (b % 2))
	{
		if (b & 1)
		{
			swap(a, b);
			swap(v1, v2);
		}
		ans -= ((v1 * t) / (a * l) + 1) / 2;
	}
	cout << ans << endl;
	return 0;
} 
