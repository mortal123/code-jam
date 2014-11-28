#include<cstring>
#include<cstdio>
#include<algorithm>
#include<ctime>
#include<cstdlib>
using namespace std;
int infi(2e9 + 123);
int n, ans, ansa[11111], ansb[11111], o1[11111], o2[11111], ans1[11111], ans2[11111], a[11111], b[11111];
bool cmp1(int x, int y) {
	return b[x] - a[x] < b[y] - a[y];
}
bool cmp2(int x, int y) {
	return b[x] - a[x] > b[y] - a[y];
}
void renewAns() {
	int t1(0), t2(0), ans;
	fill(ans1 + 1, ans1 + 1 + n, -infi);
	fill(ans2 + 1, ans2 + 1 + n, -infi);
	for(int i(1), j(1); i <= n or j <= n; ) {
		if(j == n + 1 or i != n + 1 and t1 <= t2) {
			t1 = max(t1, ans2[o1[i]] + b[o1[i]]);
			ans1[o1[i]] = t1;
			t1 += a[o1[i]];
			i++;
		}else {
			t2 = max(t2, ans1[o2[j]] + a[o2[j]]);
			ans2[o2[j]] = t2;
			t2 += b[o2[j]];
			j++;
		}
	}
	ans = max(t1, t2);
	/*if(ans == 39 and ::ans != 39) {
		for(int i(1); i <= n; i++) printf("%d\n", o1[i]);
		for(int i(1); i <= n; i++) printf("%d\n", o2[i]);
		for(int i(1); i <= n; i++) printf("%d\n", ans1[i]);
		for(int i(1); i <= n; i++) printf("%d\n", ans2[i]);
		
	}*/
	if(ans < ::ans) {
		copy(ans1 + 1, ans1 + 1 + n, ansa + 1);
		copy(ans2 + 1, ans2 + 1 + n, ansb + 1);
		::ans = ans;
	}
}
void printAns() {
	printf("%d\n", ans);
	for(int i(1); i <= n; i++) {
		printf("%d %d\n", ansa[i], ansb[i]);
	}
}


int solve() {
	scanf("%d", &n);
	int suma(0), sumb(0);
	srand(123184);
	for(int i(1); i <= n; i++) {
		scanf("%d%d", &a[i], &b[i]);
		//a[i] = rand() % 100000 + 1;
		//b[i] = rand() % 100000 + 1;
		
		suma += a[i];
		sumb += b[i];
	}
	a[0] = -1;
	b[0] = -1;
	ans = infi;
	int maxAi(0), maxBi(0);
	for(int i(1); i <= n; i++) {
		if(a[i] >= sumb - b[i] and b[i] >= suma - a[i]) {
			o1[1] = i;
			int c(1);
			for(int j(1); j <= n; j++) if(j != i) {
				o1[++c] = j;
			}
			copy(o1 + 1, o1 + 1 + n, o2 + 1);
			reverse(o2 + 1, o2 + 1 + n);
			
			renewAns();
			printAns();
			return 0;
		}
		if(a[i] > a[maxAi]) {
			maxAi = i;
		}
		if(b[i] > b[maxBi]) {
			maxBi = i;
		}
	}
	o1[1] = maxAi;
	int c(1);
	for(int i(1); i <= n; i++) if(i != maxAi) {
		o1[++c] = i;
	}
	sort(o1 + 2, o1 + n + 1, cmp1);
	for(int i(1); i < n; i++)
		o2[i] = o1[i + 1];
	o2[n] = maxAi;
	renewAns();

	o2[1] = maxBi;
	c = 1;
	for(int i(1); i <= n; i++) if(i != maxBi) {
		o2[++c] = i;
	}
	sort(o2 + 2, o2 + n + 1, cmp2);
	for(int i(1); i < n; i++)
		o1[i] = o2[i + 1];
	o1[n] = maxBi;
	renewAns();
	
	for(int i(1); i <= 100; i++) {
		for(int j(1); j <= n; j++)
			o1[j] = j, o2[j] = j;
		random_shuffle(o1 + 1, o1 + 1 + n);
		random_shuffle(o2 + 1, o2 + 1 + n);
		renewAns();
	}
	for(int i(1); i <= 20; i++) {
		for(int j(1); j <= n; j++)
			o1[j] = j;
		random_shuffle(o1 + 1, o1 + 1 + n);
		copy(o1 + 1, o1 + 1 + n, o2 + 1);
		reverse(o2 + 1, o2 + 1 + n);
		swap_ranges(o2 + 1, o2 + 1 + n / 3, o2 + 1 + n / 3);
		renewAns();
	}
	printAns();
}

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		solve();
	}
}