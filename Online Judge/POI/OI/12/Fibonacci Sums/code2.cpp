#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1111111;

int a[N];

void myAssert(bool flag) {
	if (!flag)
		while(1);
}


int main() {
	freopen("input.txt", "r", stdin);
	
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		a[i] += x;
	}
	
	for(int i = 1; i < N; i++)
		if (a[i]) {
			n = i;
		}
	
	for(int i = N - 1; i >= 1; i--) {
		if (i == 2) {
			i = 2;
		}
		if (a[i] == 2) {
			if (a[i + 1] == 1) {
				myAssert(a[i + 2] == 0);
				a[i] = 1;
				a[i + 1] = 0;
				a[i + 2] = 1;
			} else {
				myAssert(a[i + 1] == 0);
				if (i > 1 && a[i - 1] == 1)
					continue;
				if (i == 1) {
					a[i + 1] = 1;
					a[i] = 0;
				} else if (i == 2) {
					myAssert(a[i - 1] == 0);
					a[i + 1] = a[i - 1] = 1;
					a[i] = 0;
				} else if (a[i - 2] < 2) {
					a[i + 1] = 1;
					a[i] = 0;
					a[i - 2] ++;
				}
			}
		}
	}
	
	for(int i = 1; i < N - 1; i++) {
		if (a[i + 1] == 0 && a[i] == 2 && a[i - 1] == 1) {
			a[i - 1] = 0;
			a[i] = a[i + 1] = 1;
		}
	}
	
	for(int i = 1; i < N; i++) {
		myAssert(a[i] == 0 || a[i] == 1);
	}
	
	for(int i = 1, j = 1; i < N; i = j) {
		if (a[i] == 0) {
			j = i + 1;
			continue;
		}
		
		for(j = i; a[j] == 1; j++);
		for(int k = j; k - 2 >= i; k -= 2) {
			a[k] = 1;
			a[k - 1] = a[k - 2] = 0;
		}
	}
	
	n = 0;
	for(int i = 1; i < N; i++) {
		if (a[i]) {
			n = i;
		}
	}
	
	printf("%d", n);
	for(int i = 1; i <= n; i++) {
		printf(" %d", a[i]);
	}
	printf("\n");
	return 0;
}
