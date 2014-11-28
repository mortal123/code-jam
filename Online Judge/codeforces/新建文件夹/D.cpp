#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const long long mod = 1000000009;

int n;
long long C, ans;

long long pow(long long a, long long b)
{
	if (b == 0)
		return 1;
	if (b == 1)
		return a % mod;
	long long tmp = pow(a, b / 2);
	tmp = tmp * tmp % mod;
	if (b % 2)
		tmp = tmp * a % mod;
	return tmp;
}

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	C = 1;
	for(int i = 1; i < n; i++)
	{
		// C[n][i] * (2 ^ (n -  i))
		C = C * (n - i + 1) % mod * pow(i, mod - 2) % mod;
		ans = (ans + C * ((pow(2, n - i) - 1 + mod) % mod) % mod) % mod; 
		//cout << C << " " << (pow(2, n - i) - 1) << endl;
	}
	cout << ans << endl;
	return 0;
} 
