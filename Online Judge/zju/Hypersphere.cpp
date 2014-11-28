#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

long long MOD;
long long k, l;

inline void norm(long long &x) {
	x %= MOD;
	if (x < 0)
		x += MOD;
}

struct Matrix {
	long long dat[2][2];
	void clear() {
		memset(dat, 0, sizeof(dat));
	}
	inline friend Matrix operator *(const Matrix &a, const Matrix &b) {
		Matrix c;
		for(int i = 0; i < 2; i++)
			for(int j = 0; j < 2; j++) {
				c.dat[i][j] = 0;
				for(int k = 0; k < 2; k++) {
					c.dat[i][j] += a.dat[i][k] * b.dat[k][j];
					norm(c.dat[i][j]);
				}
			}
		return c;
	} 
};

int main() {
	freopen("input.txt", "r", stdin);
	while(cin >> k >> l) {
		MOD = k;
		Matrix A; A.clear();
		A.dat[0][0] = 2;
		A.dat[1][0] = 2 * l % MOD;
		Matrix B; B.clear();
		B.dat[0][1] = 1;
		B.dat[1][0] = (-l % MOD + MOD) % MOD;
		B.dat[1][1] = (2 * l) % MOD;
		while(k) {
			if (k & 1)
				A = B * A;
			k >>= 1;
			B = B * B;
		}
		A.dat[0][0]--;
		norm(A.dat[0][0]);
		cout << A.dat[0][0] << endl;
	}
	return 0;
}
