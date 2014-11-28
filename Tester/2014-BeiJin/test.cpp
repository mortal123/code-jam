#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5;

int a[111111];

int main() {
	for(int i = 1; i <= N; i++) {
		for(int j = i; j <= N; j += i) {
			a[j]++;
		}
	}
	long long res = 0;
	for(int i = 1; i <= N; i++) {
		res += 1LL * a[i] * a[i];
	}
	cout << res << endl;
}