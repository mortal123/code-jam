#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 11111;

int n;
int x[N], y[N], tot;
vector<pair<int, int> > answer;
int number[N], pos[N];
int mat[55][55], choose[N];

bool solve(int yy) {
	for(int i = 0; i < 32; i++) {
		for(int j = 1; j <= tot; j++) {
			mat[i + 1][j] = (x[j] >> i & 1);
		}
		mat[i + 1][tot + 1] = (yy >> i & 1);
	}	
	for(int i = 1; i <= 32 && i <= tot; i++) {
		int c = -1;
		for(int j = i; j <= 32; j++) {
			if (mat[j][i] == 1) {
				c = j;
				break;
			}
		}
		if (c == -1) {
			continue;
		}
		for(int j = 1; j <= tot + 1; j++) {
			swap(mat[i][j], mat[c][j]);
		}
		for(int j = 1; j <= 32; j++) {
			if (i != j && mat[j][i]) {
				for(int k = 1; k <= tot + 1; k++) {
					mat[j][k] ^= mat[i][k];
				}
			}
		}
	}
	for(int i = 1; i <= tot; i++) {
		choose[i] = 0;
	}
	int result = 0;
	for(int i = tot; i >= 1; i--) {
		int cnt = 0;
		for(int j = 1; j <= tot; j++) {
			if (mat[i][j]) {
				cnt++;
				if (mat[i][tot + 1]) {
					choose[j] = 1;
					break;
				}
			}
		}
		if (mat[i][tot + 1] && cnt == 0) {
			return false;
		}
	}
	for(int i = 1; i <= tot; i++) {
		result ^= (choose[i] * x[i]);
	}
	return result == yy;
} 

bool show(vector<int> a, int b) {
	for(int j = 0; j < (int)a.size(); j++) {
		if ((b ^ a[j]) < b) {
			b ^= a[j];
		}
	}
	return b == 0;
}

bool show(vector<int> a, vector<int> b) {
	for(int i = 0; i < (int)b.size(); i++) {
		if (!show(a, b[i])) {
			return false;
		}
	}
	return true;
}

int getHigh(int x) {
	int res = -1;
	for(int i = 0; i < 32; i++) {
		if (x >> i & 1) {
			res = i;
		}
	} 
	return res;
}

void print(int i, int j) {
	x[i] ^= j;
	answer.push_back(make_pair(i, j));
}

void sswap(int i, int j) {
	if (i == j) {
		return ;
	}
	print(i, j);
	print(j, i);
	print(i, j);
	
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &x[i]);
	}
	for(int i = 1; i <= n; i++) {
		scanf("%d", &y[i]);
	}
	tot = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= tot; j++) {
			if ((x[i] ^ x[j]) < x[i]) {
				print(i, j);
			}
		}
		if (x[i] == 0) {
			continue;
		}
		int h = getHigh(x[i]), rank = 0;
		for(int j = 1; j <= tot; j++) {
			if (h == getHigh(x[j])) {
				rank = -1;
				break;
			} else {
				if (getHigh(x[j]) < h) {
					rank = j;
				}
			}
		}
		if (rank != -1) {
			sswap(++tot, i);
			for(int j = tot - 1; j > rank; j++) {
				sswap(j, j + 1);
			}
		}
	}
	
	for(int i = 1; i <= tot; i++) {
		number[getHigh(x[i])] = x[i];
		pos[getHigh(x[i])] = i;
	}
	for(int i = n; i > tot; i--) {
		for(int j = 31; j >= 0; j--) {
			if ((x[i] >> j & 1) != (y[i] >> j & 1)) {
				if (!number[j]) {
					printf("-1\n");
					return 0;
				}
				print(i, pos[j]);
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		printf("%d %d\n", x[i], y[i]);
	}
	vector<int> vecy;
	while(tot) {
		vecy.clear();
		for(int i = 1; i < tot; i++) {
			vecy.push_back(y[i]);
		} 
		bool succ = false;
		vector<int> vecx;
		for(int c = 1; c <= tot; c++) {
			vecx.clear();
			for(int j = 1; j <= tot; j++) {
				if (j != c) {
					vecx.push_back(x[j]);
				}
			}
			if (show(vecx, vecy)) {
				succ = true;
				sswap(c, tot);
			}
		}
		if (!succ || !solve(y[tot])) {
			printf("-1\n");
			return 0;
		}
		if (choose[tot] == 0) {
			print(tot, tot);
		}
		for(int j = 1; j < tot; j++) {
			if (choose[j]) {
				print(tot, j);
			}
		}
		
		tot--;
	}
	
	printf("%d\n", (int)answer.size());
	for(int i = 0; i < (int)answer.size(); i++) {
		printf("%d %d\n", answer[i].first, answer[i].second);
	}
	return 0;
}

