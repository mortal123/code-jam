#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int LENGTH = 150, MOD = 666;

int f[LENGTH][MOD + 5][3], mark[LENGTH][MOD + 5][3], sum[MOD + 5][3], temp[MOD + 5][3];
char number[LENGTH];
int n, times[3] = {11, 101, 335};
vector<int> remain[MOD + 5];

int modify(int x) {
	return (x % MOD + MOD) % MOD;
}

int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%s", number);
	n = strlen(number);
	if (n >= LENGTH)
		while(1);
	for(int i = 0; i < MOD; i++) {
		remain[(i * 10) % MOD].push_back(i);
	}
	
	for(int i = n - 1; i >= 0; i--) { 
		memset(f, 0, sizeof(f));
		memset(sum, 0, sizeof(sum));
		memset(temp, 0, sizeof(temp));
		
		sum[0][1] = 1;
		
		for(int j = i; j < n; j++) {
			for(int k = 0; k < MOD; k++)
				for(int l = 0; l < 3; l++) {
					if (i == j) {
						if (l == 2 && k == number[j] - '0')
							f[j][k][l] = 1;
					} else if (number[i] != number[j]) {
						f[j][k][l] = 0;
					} else {
						int t = modify(k - times[l] * (number[i] - '0'));
						for(int it = 0; it < (int)remain[t].size(); it++)
							(f[j][k][l] += sum[remain[t][it]][(l + 1) % 3]) %= MOD;
					}
				}
			
			for(int k = 0; k < MOD; k++)
				for(int l = 0; l < 3; l++) {
					(sum[k][l] += mark[j][k][l]) %= MOD;
					(temp[k][l] += f[j][k][l] + mark[j][k][l]) %= MOD;
					(mark[j][k][l] += f[j][k][l]) %= MOD;
					f[j][k][l] = temp[k][l];
				}
		//printf("%d\n", i);
		}
	}
	
	int ans = (f[n - 1][0][0] + f[n - 1][0][1] + f[n - 1][0][2]) % MOD;
	printf("%d\n", ans ? ans : MOD);
	return 0;
} 
