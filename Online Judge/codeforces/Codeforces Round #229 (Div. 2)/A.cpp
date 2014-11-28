#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

int ans1, ans2;
int hash[111], hash1[111];
int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (hash[a] == 0) {
			ans1++;
			hash[a] = 1;
		}
		
		if (hash1[b] == 0) {
			ans2++;
			hash1[b] = 1;
		}
	} 
	
	printf("%d\n", min(ans1, ans2));
	return 0;
}
