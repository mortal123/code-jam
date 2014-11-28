#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <complex>
#include <cstdio>

#define foreach(container, it) \
    for(typeof((container).begin()) it = (container).begin(); it!=(container).end(); ++it)
    
using namespace std;

const int N = 33333;
const double pi = acos(-1.0);

typedef complex<double> Complex;

// oper = 1 FFT   oper = -1 DFT
// n 为正常的两倍大小，且为2的幂次
// DFT 后，数字应该除以n 再加0.5取上整  
// sincos函数为第一个为sin(p0),第二个为cos(p0)
void FFT(Complex P[], int n, int oper) {
	for (int i = 1, j = 0; i < n - 1; i++) {
		for (int s = n; j ^= s >>= 1, ~j & s;);
		if (i < j)
			swap(P[i], P[j]);
	}
	Complex unit_p0;
	for (int d = 0; (1 << d) < n; d++) {
		int m = 1 << d, m2 = m * 2;
		double p0 = pi / m * oper;
		sincos(p0, &unit_p0.imag(), &unit_p0.real());
		for (int i = 0; i < n; i += m2) {
			Complex unit = 1;
			for (int j = 0; j < m; j++) {
				Complex &P1 = P[i + j + m], &P2 = P[i + j];
				Complex t = unit * P1;
				P1 = P2 - t;
				P2 = P2 + t;
				unit = unit * unit_p0;
			}
		}
	}
}

int n;
vector<int> e[N];
bool exist[N];
int father[N], size[N];
Complex a[N * 4], b[N * 4], c[N * 4], d[N * 4];
long long cnt[N * 4];

int search(int source) {
	vector<int> q;
	q.push_back(source);
	father[source] = -1;
	for(int head = 0; head < (int)q.size(); head++) {
		int x = q[head];
		size[x] = 0;
		foreach(e[x], it) {
			if (!exist[*it] || *it == father[x])
				continue;
			q.push_back(*it);
			father[*it] = x;
		}
	}
	
	int total = (int)q.size(), res = -1, minV = total + 1;
	for(int i = total - 1; i >= 0; i--) {
		int x = q[i];
		size[x] = 1;
		
		int cur = 0;
		foreach(e[x], it) {
			if (!exist[*it] || *it == father[x])
				continue;
			size[x] += size[*it];
			cur = max(cur, size[*it]);
		}
		
		cur = max(total - size[x], cur);
		
		if (cur < minV) {
			minV = cur;
			res = x;
		}
	}
	
	return res;
}

int calcSize(int source) {
	vector<int> q;
	father[source] = -1;
	q.push_back(source);
	for(int head = 0; head < (int)q.size(); head++) {
		int x = q[head];
		foreach(e[x], it) {
			if (!exist[*it] || *it == father[x])
				continue;
			father[*it] = x;
			q.push_back(*it);
		}
	}
	
	return (int)q.size();
}

void solve(int r, Complex b[], int &m) {
	vector<int> q;
	q.push_back(r);
	father[r] = -1;
	
	static int depth[N];
	depth[r] = 1;
	
	for(int head = 0; head < (int)q.size(); head++) {
		int x = q[head];
		foreach(e[x], it) {
			if (!exist[*it] || *it == father[x])
				continue;
			depth[*it] = depth[x] + 1;
			father[*it] = x;
			q.push_back(*it);
		}
	}
	
	for(m = 1; m <= 2 * depth[q.back()]; m *= 2);
	for(int i = 0; i < m; i++)
		b[i] = Complex(0, 0);
	for(int i = 0; i < (int)q.size(); i++) {
		b[depth[q[i]]].real() += 1;
	}
}

void divide(int source) {
	int x = search(source);
	exist[x] = false;
	vector<pair<int, int> > sons;
	foreach(e[x], it) {
		if (!exist[*it])
			continue;
		sons.push_back(make_pair(calcSize(*it), *it));
	}
	
	sort(sons.begin(), sons.end());
	a[0].real() = 1;
	int m = 2, mm;
	foreach(sons, it) {
		int y = it->second;
		solve(y, b, mm);
		m = max(m, mm);
		for(int i = 0; i < m; i++) {
			c[i] = a[i];
			d[i] = b[i];
			a[i] += b[i];
		}
		
		FFT(c, m, 1);
		FFT(d, m, 1);
		for(int i = 0; i < m; i++) {
			c[i] = c[i] * d[i];
		}
		FFT(c, m, -1);
		
		for(int i = 0; i < m; i++) {
			cnt[i] += (long long)((c[i].real() / m) + 0.5);
		}
	}
	
	for(int i = 0; i < m; i++) {
		a[i] = Complex(0, 0);
	}
	
	foreach(e[x], it) {
		if (exist[*it]) {
			divide(*it);
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		e[a].push_back(b);
		e[b].push_back(a);
	}
	
	fill(exist, exist + n, true);
	divide(0);
	double result = 0;
	for(int i = 1; i <= n; i++) {
		result += 2.0 * cnt[i] / (i + 1);
	}
	
	printf("%.4f\n", result + n);
	return 0;
}
