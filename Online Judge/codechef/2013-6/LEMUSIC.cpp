#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

vector <pair<long long, long long> > vec;
long long ans = 0;
vector <long long> vec2;

int main()
{
	int T, n;
	cin >> T;
	while(T--)
	{
		vec.clear();
		vec2.clear();
		ans = 0;
		cin >> n;
		for(int i = 1; i <= n; i++)
		{
			long long b, l;
			cin >> b >> l;
			vec.push_back(make_pair(b, l));
		}
		sort(vec.begin(), vec.end());
		long long dif = 0;
		for(int i = 0; i < n; i++)
			if (i == 0 || vec[i].first != vec[i - 1].first)
				dif++;
		for(int i = 0; i < n;)
		{
			int j = i;
			long long sum = 0;
			while(j < n && vec[j].first == vec[i].first)
			{
				sum += vec[j].second;
				j++;
			}
			ans += (sum - vec[i].second) * dif;
			vec2.push_back(vec[i].second);
			i = j;
		}
		sort(vec2.begin(), vec2.end());
		long long now = 0;
		for(int i = 0; i < vec2.size(); i++)
		{
			ans += vec2[i] * (i + 1);
		}
		cout << ans << endl;
	}
	return 0;
}
