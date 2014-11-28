#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cstring>
using namespace std;

const int N = 1111111 * 2, ZERO = 1111111;

int a[N], b[N], c[N];
int n;

void myAssert(bool flag) {
	if (!flag) {
		while(1);
	}
}

void solve(int a[]) {
	for(int i = 1; i < N - 1; i++) {
		if (a[i] && a[i + 1]) {
			int t = min(a[i], a[i + 1]);
			a[i] -= t;
			a[i + 1] -= t;
			a[i + 2] += t;
		}
	}
}

int add(int a[], int pos) {
	while(1) {
		a[pos] += 1;
		if (a[pos + 1]) {
			a[pos]--;
			a[pos + 1]--;
			pos += 2;
		} else if (a[pos - 1]) {
			a[pos - 1]--;
			a[pos]--;
			pos++;
		} else {
			break;
		}
	}
}


int check(int a[]) {
	for(int i = 1; i < N; i++) {
		if (a[i] != 0 && a[i] != 1)
			return 0;
		if (i < N - 1 && a[i] && a[i + 1])
			return 0;
		if (a[i] < 0 || a[i] > 2)
			while(1);
	}
	return 1;
}

void Main(int a[]) {
	solve(a);
	for(int i = 1; i <= 12; i++)
		printf("%d ", a[ZERO + i]);
	printf("\n");
	int one = 0;
	for(int i = N - 1; i >= 1; i--) {
		if (i <= ZERO) {
			if ((ZERO - i) % 2 == 0) {
				one += a[i];
			}
			a[i] = 0;
			continue;
		}
		
		if (a[i] == 2) {
			if (a[i - 2] == 1) {
				a[i] = 0;
				add(a, i + 1);
				a[i - 2]++;
			} else if (a[i - 2] == 2) {
				int j = i - 2;
				for( ; a[j] == 2; j -= 2) {
					a[j + 2] = 1;
				}
				
				a[j + 2] = 0;
				// a[j] + 1  a[i + 2] + 1
				add(a, j);
				if (a[i + 2] == 0) {
					add(a, i + 2);
				} else if (a[i + 2] == 1) {
					a[i + 2]++;
					i += 3;
					continue;
				}
				
			} else if (a[i - 2] == 0) {
				a[i] = 0;
				add(a, i + 1);
				add(a, i - 2);
			}
		}
	}
	while(one--) {
		if (a[ZERO + 1] == 0) {
			add(a, ZERO + 1);
		} else if (a[ZERO + 1] == 1) {
			a[ZERO + 1] = 0;
			add(a, ZERO + 2);
		}
	}
	
	// check
	/*
	for(int i = ZERO + 1; i <= ZERO + length; i++) {
		//if (a[i] && a[i + 1])
		//	while(1);
		if (a[i] != 0 && a[i] != 1)
			while(1);
	}
	*/
} 

int main() {
	freopen("input.txt", "r", stdin);
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[ZERO + i]);
		myAssert(a[ZERO + i] >= 0 && a[ZERO + i] <= 1);
	}
	//Main(a);
	check(a);
	
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &b[ZERO + i]);
		myAssert(b[ZERO + i] >= 0 && b[ZERO + i] <= 1);
	}
	//Main(b);
	check(b);
	
	for(int i = 1; i < N; i++)
		a[i] += b[i];
	
	//while(!check(a))
	Main(a);
	//check(a);
	
	int length = 0;
	for(int i = ZERO + 1; i < N; i++)
		if (a[i]) {
			length = i - ZERO;
		}
	
	printf("%d", length);
	for(int i = 1; i <= length; i++) {
		printf(" %d", a[i + ZERO]);
	}
	
	printf("\n");
	return 0;
}
