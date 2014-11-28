#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int N = 111;
const int MOD = 1000000007;

int C[N][N];
long long n;
int k;

int m;

struct Matrix {
	long long dat[N][N];
	
	void clear() {
		memset(dat, 0, sizeof(dat));
	}
	
	inline Matrix friend operator *(const Matrix &a, const Matrix &b) {
		Matrix c;
		for(int i = 0; i < m; i++)
			for(int j = 0; j < m; j++) {
				c.dat[i][j] = 0;
				for(int k = 0; k < m; k++) {
					(c.dat[i][j] += a.dat[i][k] * b.dat[k][j] % MOD) %= MOD;
				}
			}
		return c;
	}
}A, B;

int main() {
	scanf("%I64d %d", &n, &k);
	for(int i = 0; i <= k; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j++) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
		}
	}	
	
	m = 2 * k + 3;
	A.clear();
	B.clear();
	
	B.dat[0][0] = 1;
	A.dat[0][0] = 1;
	for(int i = 1; i <= k + 1; i++) {
		A.dat[i][0] = 1;
		A.dat[i + 1 + k][0] = 1;
		B.dat[0][i] = C[k][i - 1];
		B.dat[0][k + 1 + i] = C[k][i - 1];
		for(int j = 1; j <= i; j++) {
			B.dat[i][j] = C[i - 1][j - 1];
			B.dat[i][j + k + 1] = C[i - 1][j - 1];
			B.dat[i + 1 + k][j] = C[i - 1][j - 1];
		}
	}
	
	n--;
	
	while(n) {
		if (n & 1) {
			A = B * A;
		}
		
		n >>= 1;
		B = B * B;
	}
	
	printf("%I64d\n", A.dat[0][0]);
	
	return 0;
} 
