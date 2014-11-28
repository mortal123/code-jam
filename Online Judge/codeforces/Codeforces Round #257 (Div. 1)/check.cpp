#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 111111;

int used[N];

void dfs(int x, int ans) {
	dfs(x + 1, ans);
	
}

int main() {
	dfs(2, 0);
	return 0;
}

