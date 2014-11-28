#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

const int N = 222222;
const int LIMIT = 1000;

vector<int> e[N];
int n, m;
int sv[N];

FILE *fout;

int main() {
	fout = fopen("output2.txt", "w");
	srand(time(0));
	freopen("input.txt", "w", stdout);
	printf("%d\n", n = 100000);
	for(int i = 0; i < n; i++) {
		printf("%d ", LIMIT);
	}	
	for(int i = 1; i < n; i++) {
		printf("%d %d\n", 0, i);
	}
	printf("\n");
	printf("%d\n", m = 100000);
	long long special = 0;
	long long ans = 1LL * LIMIT * n;
	for(int i = 1; i <= m; i++) {
		int type = rand() % 2 + 1;
		if (type == 1) {
			printf("2\n%I64d %d\n", -special, LIMIT);
			ans += 1LL * n * LIMIT;
		} else if (type == 2) {
			printf("4\n%I64d\n", -special);
			fprintf(fout, "%I64d\n", ans);
			special += ans;
		}
	}
	return 0;
}
