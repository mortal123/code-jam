#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int N = 20;
const long long BOUND = 10000000000LL;
vector<long long> vec;

int a[N], n;
bool b[20];

long long pow(long long a, long long b) {
	long long res = 1;
	for(int i = 1; i <= b; i++)
		res *= a;
	return res;
}

long long count(long long m) {
	return upper_bound(vec.begin(), vec.end(), m) - vec.begin() - 1;
}

int main() {
	b[0] = b[1] = b[4] = b[9] = true;
	freopen("input.txt", "r", stdin);
	for(long long i = 0; i * i <= BOUND; i++) {
		long long tmp = i * i;
		bool flag = true;
		while(tmp) {
			if (b[tmp % 10] == false)
				flag = false;
			tmp /= 10;
		}
		if (flag)
			vec.push_back(i * i);
	}
	int test;
	cin >> test;
	long long left, right;
	while(test--) {
		cin >> left >> right;
		cout << count(right) - count(left - 1) << endl;
	}
	return 0;
} 
