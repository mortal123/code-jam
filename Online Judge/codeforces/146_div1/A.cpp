#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
long long N;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> N;
	if (N == 1)
	{
		printf("%d\n", 1);
	}
	else
	if (N == 2)
	{
		printf("%d\n", 2);
	}
	else
	{
		long long tmp = 1;
		if (N % 2 == 1)
			cout << N * (N - 1) * (N - 2) << endl;
		else
			cout << max((N - 1) * (N - 2) * (N - 3), N * (N - 1) * (N - 2) / 2) << endl;
	}
	return 0;
}
