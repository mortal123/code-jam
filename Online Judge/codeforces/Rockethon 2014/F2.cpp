#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111;
struct Node {
	int tag;
	long long maxR, posR, maxL, posL, middle, pl, pr, sum;
}T[N * 4];

int n, times;
int a[N], b[N];

void update(int x) {
	if (T[x << 1 | 1].maxR > T[x << 1 | 1].sum + T[x << 1].maxR) {
		T[x].maxR = T[x << 1 | 1].maxR;
		T[x].posR = T[x << 1 | 1].posR;
	} else {
		T[x].maxR = T[x << 1 | 1].sum + T[x << 1].maxR;
		T[x].posR = T[x << 1].posR;
	}
	
	if (T[x << 1].maxL > T[x << 1].sum + T[x << 1 | 1].maxL) {
		T[x].maxL = T[x << 1].maxL;
		T[x].posL = T[x << 1].posL;
	} else {
		T[x].maxL = T[x << 1].sum + T[x << 1 | 1].maxL;
		T[x].posL = T[x << 1 | 1].posL;
	}
	
	long long vmid = T[x << 1].maxR + T[x << 1 | 1].maxL;
	if (vmid > T[x << 1].middle && vmid > T[x << 1 | 1].middle) {
		T[x].middle = vmid;
		T[x].posL = T[x << 1].posL;
		T[x].posR = T[x << 1 | 1].posR;
	} else if (T[x << 1].middle > T[x << 1 | 1].middle) {
		T[x].middle = T[x << 1].middle;
		T[x].posL = T[x << 1].posL;
		T[x].posR = T[x << 1].posR;
	} else {
		T[x].middle = T[x << 1 | 1].middle;
		T[x].posL = T[x << 1 | 1].posL;
		T[x].posR = T[x << 1 | 1].posR;
	}
}

void reverse(int x) {
	tag ^= 1;
	
}

void build(int x, int l, int r) {
	T[x].tag = 0;
	if (l == r) {
		if (b[l] >= 0) {
			maxR = maxL = middle = b[l];
			posR = posL = pl = pr = l;
		} else {
			maxR = maxL = pl = pr = -1;
		}
		T[x].sum = b[l];
		return;
	}
	
	int mid = (l + r) / 2;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
	update(x);
}

int main() {
	scanf("%d %d", &n, &times);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		b[i] = a[i] - a[i - 1];
	}
	
	build(1, 1, n);
	return 0;
} 
