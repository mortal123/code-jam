#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> a, b;

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		int aa, bb;
		scanf("%d %d", &aa, &bb);
		a.clear();
		while(aa) {
			a.push_back(aa & 1);
			aa >>= 1;
		}
		b.clear();
		while(bb) {
			b.push_back(bb & 1);
			bb >>= 1;
		}
		while(a.size() && b.size() && a.back() == b.back()) {
			a.pop_back();
			b.pop_back();
		}
		printf("%d\n", (int)a.size() + (int)b.size());
	}
	return 0;
}
