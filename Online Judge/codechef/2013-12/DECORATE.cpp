#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

const int N = 222222, NN = 666;
const int multi = 137;
const int MOD = (int)(1e9 + 7);
const int rp = 10;

char buf[N];
int n, len;
set<long long> s;
long long power[N];

void myAssert(int flag) {
	if (!flag) {
		while(1);
	}
}

struct bigNum {
	vector<int> dat;	
	void clear() {
		dat.clear();
		dat.push_back(0);
	}
	
	void operator *= (int k) {
		for(int i = 0; i < (int)dat.size(); i++)
			dat[i] *= k;
		for(int i = 0; i < (int)dat.size(); i++) {
			if (dat[i] >= rp) {
				if (i == (int)dat.size() - 1) {
					dat.push_back(0);
				}
				dat[i + 1] += dat[i] / rp;
				dat[i] %= rp;
			}
		}
	}
	
	void operator /= (int k) {
		for(int i = (int)dat.size() - 1; i >= 0; i--) {
			if (i)
				dat[i - 1] += dat[i] % k * rp;
			dat[i] /= k;
		}
		while(dat.size() > 1 && dat[(int)dat.size() - 1] == 0)
			dat.pop_back();
	}
	
	void operator += (const bigNum o) {
		for(int i = 0; i < (int)o.dat.size(); i++) {
			if (i >= (int)dat.size())
				dat.push_back(0);
			dat[i] += o.dat[i];
		}
		
		for(int i = 0; i < (int)dat.size(); i++) {
			if (dat[i] >= rp) {
				if (i == (int)dat.size() - 1) {
					dat.push_back(0);
				}
				dat[i + 1] += dat[i] / rp;
				dat[i] %= rp;
			}
		}	
	}
	void print() {
		printf("%d", dat[(int)dat.size() - 1]);
		for(int i = (int)dat.size() - 2; i >= 0; i--)
			printf("%d", dat[i]);
		printf("\n");
	}
};

long long getHashCode(long long hash[], int l, int r) {
	return (hash[r] - hash[l - 1] * power[r - l + 1] % MOD + MOD) % MOD;
}

int countNumber(char str[], int len) {
	static int rad[N];
    static long long hash[N];
    
	for(int i = 1, j = 0, k; i <= len; i += k, j = max(j - k, 0)) {
        while(str[i - j - 1] == str[i + j + 1])
			++j;
        rad[i] = j;
        for (k = 1; k <= j && rad[i - k] != rad[i] - k; ++k) {
            rad[i + k] = min(rad[i - k], rad[i] - k);
        }
    }
    
    int result = 0;
    
    hash[0] = 0;
    for(int i = 1; i <= len; i++) {
    	hash[i] = (hash[i - 1] * multi + str[i] - 'a' + 1) % MOD;
    }
    
    s.clear();
    
    for(int i = 1; i <= len; i++) {
    	int ed = !(isalpha(str[i]));
    	if (!isalpha(str[i - rad[i]]))
    		rad[i]--;
    	for(int j = rad[i]; j >= ed; j -= 2) {
    		long long tmp = getHashCode(hash, i - j, i + j);
    		if (s.count(tmp)) {
    			break;
    		} else {
    			/*
				printf("%d %d\n", i - j, i + j);
    			for(int k = i - j; k <= i + j; k++) {
    				printf("%c", str[k]);
    			}
    			printf("\n");
    			*/
    			s.insert(tmp);
    			result++;
    		}
    	}
    }
    
    return result;
}

int calc(int order[], int n) {
	static int visit[NN];
	for(int i = 0; i < n; i++)
		visit[i] = 0;
		
	int res = 0;
	
	for(int i = 0; i < n; i++) {
		if (visit[i])
			continue;
		++res;
		int x = i;
		while(!visit[x]) {
			visit[x] = 1;
			x = order[x];
		}
	}
	
	return res;
}

int main() {
	freopen("input.txt", "r", stdin);
	
	gets(buf + 1);
	len = strlen(buf + 1);
	myAssert(len);
	power[0] = 1;
	
	for(int i = 1; i <= (len << 1); ++i) {
		power[i] = power[i - 1] * multi % MOD;
	}
	
	static char cpy[N];
	cpy[0] = 0;
	for(int i = 1; i <= len; i++) {
		cpy[i * 2 - 1] = buf[i];
		cpy[i * 2] = 'z' + 1;
	}
	cpy[len * 2] = 1;
	
	int number = countNumber(cpy, len * 2 - 1);
	myAssert(number);
	//printf("%d\n", number);
	//return 0;
	
	static int order[NN];
	
	bigNum ans, ret;
	ans.clear();
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) 
			order[(i + j) % n] = j;
		int tmp = calc(order, n);
		ret.clear();
		ret.dat[0] = 1;
		for(int j = 1; j <= tmp; j++)
			ret *= number;
		ans += ret;
		
		for(int j = 0; j + j < n; j++)
			swap(order[j], order[n - j - 1]);
		tmp = calc(order, n);
		ret.clear();
		ret.dat[0] = 1;
		for(int j = 1; j <= tmp; j++)
			ret *= number;
		ans += ret;
	}
	
	ans /= (2 * n);
	
	ans.print();
	
	return 0;
}
