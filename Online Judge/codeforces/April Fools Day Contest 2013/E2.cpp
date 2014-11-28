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
	int cnt1 = 0, cnt2 = 0;
	for(int i = 0; i < str.length(); i++)
	{
		if (str[i] == 'H')
		{
			if (cnt1 > 0)
			{
				if (cnt2)
				{
					printf("No\n");
					exit(0);
				} else
				{
					cnt1--;
				}
			} else
			{
				cnt1++;
			}
		} else
		{
			if (cnt2 > 0)
			{
				if (cnt1)
				{
					printf("No\n");
					exit(0);
				} else
				{
					cnt2--;
				}
			} else
			{
				cnt2++;
			}
		}
	}
	printf("Yes\n");
	return 0;
}

