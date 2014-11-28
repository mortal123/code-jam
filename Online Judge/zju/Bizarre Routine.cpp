#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

const int N = 11111;

int array[N], minTimes[N], maxTimes[N];
int n, expect, a, b;

void work(int l, int r, int expect) {
	if (l > r)
		return;
	assert(minTimes[r - l + 1] <= expect && expect <= maxTimes[r - l + 1]);
	if (l == r) {
		array[l] = l;
		return;
	}
	expect -= (r - l);
	int mid, ll = (l + r) / 2, rr = r;
	while(ll < rr) {
		mid = (ll + rr) / 2;
		if (maxTimes[mid - l] + maxTimes[r - mid] < expect)
			ll = mid + 1;
		else
			rr = mid;
	}
	int leftExpect = maxTimes[ll - l], rightExpect = expect - maxTimes[ll - l];
	if (rightExpect < minTimes[r - ll]) {
		rightExpect = minTimes[r - ll];
		leftExpect = expect - minTimes[r - ll];
	}
	work(l, ll - 1, leftExpect);
	work(ll + 1, r, rightExpect);
	array[ll] = ll;
	int p = (l * a + r * b) / (a + b);
	swap(array[r], array[ll]);
	swap(array[p], array[r]);
}

int main() {
	freopen("input.txt", "r", stdin);
	while(cin >> n >> expect >> a >> b) {
		minTimes[1] = maxTimes[1] = 0;
		for(int i = 2; i <= n; i++) {
			maxTimes[i] = maxTimes[i - 1] + (i - 1);
			minTimes[i] = minTimes[i / 2] + minTimes[i - i / 2 - 1] + (i - 1);
		}
		if (expect < minTimes[n] || expect > maxTimes[n]) {
			printf("NOWAY\n");
		} else {
			work(0, n - 1, expect);
			for(int i = 0; i < n; i++) {
				printf("%d%c", array[i] + 1, i == n - 1 ? '\n' : ' ');
			}
		}
	}
	return 0;
} 
