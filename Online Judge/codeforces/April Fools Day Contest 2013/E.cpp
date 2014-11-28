#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 4000;

string str;

int main()
{
	cin >> str;
	if (str.length() % 2 == 1)
	{
		printf("No\n");
		exit(0);
	}
	int l = 0, r = str.length() - 1;
	while(l < r)
	{
		if (str[l] != str[r])
		{
			printf("No\n");
			exit(0);
		}
		l++; r--;
	}
	printf("Yes\n");
	return 0;
}

