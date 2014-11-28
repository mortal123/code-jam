
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1111;

int n, m;
int cnt[3], sum[N * 2];
char buf[100];
char output[N][3];

int change(int &a, int b) {
	if (a > b)
		a--;
	else
		a++;
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			scanf("%s", buf);
			if (buf[0] == '1' && buf[1] == '1')
				cnt[2]++;
			else if (buf[0] == '0' && buf[1] == '0')
				cnt[0]++;
			else
				cnt[1]++;			
		}
	
	int from = 1, to = m;
	
	for(int i = 1; i <= n; i++) {
		for(int j = from; ; change(j, to)) {
			if (cnt[2]) {
				cnt[2]--;
				output[j][0] = '1'; output[j][1] = '1';
				sum[j * 2]++; 
				sum[j * 2 + 1]++;
			} else if (cnt[1]) {
				if (sum[j * 2] < sum[j * 2 + 1]) {
				output[j][0] = '1'; output[j][1] = '0';
					sum[j * 2]++;
				} else {
				output[j][0] = '0'; output[j][1] = '1';
					sum[j * 2 + 1] ++;
				}
				cnt[1]--;
			} else {
				output[j][0] = '0'; output[j][1] = '0';
			}
			if (j == to) {
				for(int k = 1; k <= m; k++)
					printf("%s ", output[k]);
				printf("\n");
				break;
			}
		}
		swap(from, to);
	}
	return 0;
}
