
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1111111;

int a[N], ans[N];
int n, times;
bool found = false;

int smaller(int a[], int b[]) {
	for(int i = n; i >= 1; i--) {
		if (a[i] < b[i])
			return 1;
		if (a[i] > b[i])
			return 0;
	}
	return 0;
}

void solve(int pre) {
	int left = pre;
	for(int i = n; i >= 1; i--) {
		a[i] = left / times;
		left = (left % times) * 10 + a[i];
	}
	
	if (a[n] == 0 || a[1] != pre)
		return;
	
	if (a[n] && !found || smaller(a, ans)) {
		for(int i = 1; i <= n; i++)
			ans[i] = a[i];
	}
	
	found = true;
}

int main() {
	scanf("%d %d", &n, &times);	
	for(int i = 1; i < 10; i++) {
		solve(i);
	}
	
	if (!found)
		printf("Impossible\n");
	else {
		for(int i = n; i >= 1; i--) {
			printf("%d", ans[i]);
		}	
		printf("\n");
	}
	return 0;
}
