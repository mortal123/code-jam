#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 100000;
const int MaxLen = 1000;

int score[2][N];
int a[N];

int main() {
	freopen("input.txt", "r", stdin);
	int test;
	scanf("%d", &test);
	while(test--) {
		int Num;
		scanf("%d", &Num);
		for(int i = 0; i <= MaxLen; i++)
			score[0][i] = score[1][i] = 0;
		while(Num--) {
			int n;
			scanf("%d", &n);
			for(int i = 1; i <= n; i++)
				scanf("%d", &a[i]);
			sort(a + 1, a + n + 1);
			n = unique(a + 1, a + n + 1) - a - 1;
			int now = -1;
			int last = -10;
			for(int i = 1; i <= n; i++) {
				int x = a[i] % 2 + 2;
				x %= 2;
				if (x == last && now == 0) {
					score[x][now] ++;
				} else {
					now++;
					score[x][now] ++;
				}
				last = x;
			}
		}
		for(int i = MaxLen; i >= 1; i--) {
			for(int j = 0; j < 2; j++) {
				score[j][i - 1] += score[j][i] / 2;
				score[j][i] %= 2;
			}
		}
		bool finish = false;
		for(int i = 0; i <= MaxLen; i++) {
			if (score[0][i] != score[1][i]) {
				if (score[0][i] > score[1][i]) {
					printf("EVEN\n");
				} else {
					printf("ODD\n");
				}
				finish = true;
				break;
			}
		}
		if (!finish) {
			printf("DON'T PLAY\n");
		}
	}
	return 0;
}
