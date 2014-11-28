#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int N = 111;

double pro[N][N][N];

int main() {
	int n = 20;
	for(int i = 0; i < n; i++) {
		pro[0][i][i] = 1;
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < n; j++) {
			for(int k = 0; k < n; k++) {
				if (k != i && k != j) {
					for(int l = 0; l < n; l++) {
						pro[i][k][l] += pro[i - 1][k][l] / n;
					}
				} else if (k == i) {
					for(int l = 0; l < n; l++) {
						pro[i][k][l] += pro[i - 1][j][l] / n;
					}
				} else if (k == j) {
					for(int l = 0; l < n; l++) {
						pro[i][k][l] += pro[i - 1][i][l] / n;
					}
				}
			}
		}
	}
	for(int i = 0; i < n; i++, printf("\n"))
		for(int j = 0; j < n; j++) {
			printf("%.4f ", pro[n][i][j]);
		}
	return 0;
}
