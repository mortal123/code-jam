#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <cstring>
#include <string>
using namespace std;

const int M = 26;
const int N = 111111;

double final[M][M], table[M][M];
char source[N], target[N];
int n, k;

void multi(double a[M][M], double b[M][M]) {
	static double ret[M][M];
	for(int i = 0; i < M; i++)
		for(int j = 0; j < M; j++) {
			ret[i][j] = 0;
			for(int k = 0; k < M; k++) {
				ret[i][j] += a[i][k] * b[k][j];
			}
		}
	for(int i = 0; i < M; i++) 
		for(int j = 0; j < M; j++) {
			a[i][j] = ret[i][j];
		}
}

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d %d", &n, &k);
		scanf("%s", source);
		for(int i = 0; i < M; i++)
			for(int j = 0; j < M; j++) {
				scanf("%lf", &table[i][j]);
				final[i][j] = table[i][j];
			}

		k--;
		while(k) {
			if (k & 1) {
				multi(final, table);
			}
			k >>= 1;
			multi(table, table);
		}
		set<string> s;
		double total = 0;
		for(int i = 0; i < n; i++) {
			scanf("%s", target);
			if (strlen(source) == strlen(target) && s.count(target) == 0) {
				s.insert(target);
				double answer = 1;
				for(int j = 0; source[j]; j++) {
					answer *= final[source[j] - 'a'][target[j] - 'a'];
				}
				total += answer;
			}
		}
		printf("%.8f\n", total);
	}
}