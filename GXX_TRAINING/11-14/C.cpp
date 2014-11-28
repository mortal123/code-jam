#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 11;

double lower, upper, para[N]; 
int n;

void dfs(int dep, double upper, double sign, double &res) {
	if (dep == n) {
		if (upper > 0) {
			double cur = 1;
			for(int i = 0; i < n; i++) {
				cur = cur * upper / (i + 1);
			}
			res += sign * cur;
		}
		return;
	}
	// lower
	dfs(dep + 1, upper - (-para[dep]), sign * 1, res);
	// upper
	dfs(dep + 1, upper - para[dep], sign * -1, res);
}

double solve(int upper) {
	double result = 0;
	dfs(0, upper, 1, result);
	return result;
}

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d %lf %lf", &n, &lower, &upper);
		double total = 1;
		for(int i = 0; i < n; i++) {
			scanf("%lf", &para[i]);
			total *= 2 * para[i];
		}
		printf("%.9f\n", (solve(upper) - solve(lower)) / total);
	}
	return 0;
}