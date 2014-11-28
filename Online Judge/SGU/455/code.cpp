#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXLEN = 2000000;

long long a, b, c;

long long f(const long long x)
{
	return (a * x + x % b) % c;
}

int Solve(long long a, long long b, long long c)
{
	/*long long now = 1;
	for(int i = 1; i <= 10; i++)
	{
		cout << now << endl;
		now = f(now);
	}*/
	long long p1 = f(1), p2 = f(p1);
	for(int i = 1; i <= MAXLEN; i++)
	{
		if (p1 == p2)
			break;
		p1 = f(p1);
		p2 = f(p2); p2 = f(p2);
	}
	if (p1 != p2)
		return 0;
	p1 = 1;
	int first = -1;
	for(int i = 0; i <= MAXLEN + 1; i++)
	{
		if (p1 == p2)
		{
			first = i;
			break;
		}
		p1 = f(p1); p2 = f(p2);
	}
	if (p1 != p2)
		return 0;
	p2 = f(p1);
	for(int i = first + 1; i <= MAXLEN; i++)
	{
		if (p2 == p1)
		{
			cout << i << endl;
			return 1;
		} else
			p2 = f(p2);
	}
	return 0;
}

int main()
{
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	cin >> a >> b >> c;
	if (!Solve(a, b, c))
		printf("-1\n");
	return 0;
} 
