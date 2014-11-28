#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 333333;

double ans = 0;
char str[N];
int n;

int main() {
	scanf("%d", &n);
	scanf("%s", str);
	double sum = 0;
		
	for(int i = 0; i < n; i++) {
		if (str[i] == 'x') {
			sum = 0;
		} else if (str[i] == 'o') {
			sum += 1;
		} else {
			(sum += 1) /= 2;
		}
		
		ans += sum;
	}
	
	sum = 0;
	
	for(int i = n - 1; i >= 0; i--) {
		if (str[i] == 'x') {
			sum = 0;
		}
		
		if (str[i] == 'o') {
			ans += sum;
			sum += 1;
		} else if (str[i] == '?') {
			ans += sum / 2;
			(sum += 1) /= 2;
		}
	}
	
	printf("%.4lf\n", ans);
	return 0;
}
