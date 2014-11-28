#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <ctime>
#include <cstdlib>

typedef long long LL;
using namespace std;

const int N = 100;
char a[N], b[N];

LL calc(char *a, char *b) {
    int la = strlen(a);
    int lb = strlen(b);
    int len = min(la, lb);
    LL ans = 0, r = 1;
    for (int i = 1; i <= len; ++i) {
        r <<= 1;
        if (strncmp(a + la - i, b, i) == 0) 
			ans += r;
    } 
	return ans;
}

LL gcd(LL x, LL y){
	if (y == 0) {
		return x;
	} else {
		return gcd(y, x % y);	
	}
}

void solve() {
    scanf("%s%s", a, b);
    int la = strlen(a);
    int lb = strlen(b);
    LL u = calc(b, b) - calc(b, a);
    LL v = u + calc(a, a) - calc(a, b);
	LL g = gcd(u, v);
	u /= g;
	v /= g;
	cout << u << '/' << v << '\n';
}

int main() {
    int cas;
    scanf("%d", &cas);
    for (int C = 1; C <= cas; ++C) {
		printf("Case #%d:\n", C);
        solve();
    }
    return 0;
}
