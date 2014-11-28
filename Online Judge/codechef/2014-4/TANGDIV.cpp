#include <cstdio>
#include <cstdlib>
#include <map>
using namespace std;

map<int, int> hash;

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		int n, k, p;
		scanf("%d %d %d", &n, &k, &p);
		hash.clear();
		for(int i = 1; i <= k; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			if (--a == 0)
				a = n;
			hash[a] = hash[b] = 1;
		}
		bool flag = true;
		for(int i = 1; i <= p; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			if (--a == 0)
				a = n;
			if (hash[a] == 0 || hash[b] == 0)
				flag = false;
		}
		printf(flag ? "Yes\n" : "No\n");
	}
	return 0;
}
