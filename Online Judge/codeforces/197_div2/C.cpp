#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

int W[2], last[2];
char str[20];
int m;
vector<int> vec[2];
int main() {
	freopen("input.txt", "r", stdin);
	scanf("%s%d", str + 1, &m);
	for(int i = 0; i < m; i++) {
		int now = i % 2;
		bool flag = false;
		for(int j = 1; j <= 10; j++) {
			if (str[j] == '1' && W[now] + j > W[now ^ 1] && j != last[now ^ 1]) {
				flag = true;
				last[now] = j;
				W[now] += j;
				vec[now].push_back(j);
				break;
			}
		}
		if (!flag) {
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");	
	for(int i = 0; i < vec[0].size(); i++) {
		printf("%d ", vec[0][i]);
		if (vec[1].size() > i) {
			printf("%d ", vec[1][i]);
		}
	}
	return 0;
}
