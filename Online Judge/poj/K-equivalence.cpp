#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const long long inf = (1LL << 63) - 1;

struct Section {
	long long l, r;
	Section(long long l, long long r) : l(l), r(r) {}
	inline friend Section operator +(const Section &a, long long b) {
		return Section(max(1LL, a.l + b), min(a.r + b, inf));
	}
	inline bool appear(int digit, long long div) {
		long long ll = l / div, rr = r / div;
		if (rr / 10 > ll / 10 + 1)
			return true;
		else if (rr / 10 == ll / 10 + 1) {
			return digit >= ll % 10 || digit <= rr % 10;
		} else {
			return digit >= ll % 10 && digit <= rr % 10;
		}
		
	} 
};

Section mergy(const Section &a, const Section &b) {
	return Section(max(a.l, b.l), min(a.r, b.r));
}

vector<Section> sections, newSec, block;
Section all(1LL, inf);
int n, father[12];

int find(int x) {
	return father[x] == x ? x : father[x] = find(father[x]);
}

bool solve(int p, int q, int k) {
	long long pv = p, qv = q, div = 1;
	for(int i = 1; i <= k; i++)
		pv *= 10, qv *= 10, div *= 10;
	long long delta = qv - pv;
	newSec.clear();
	for(int i = 0; i < sections.size(); i++) {
		newSec.push_back(Section(sections[i] + delta));
	}
	for(int i = 0, j = 0; i < newSec.size(); i++) {
		while(j < block.size() && block[j].r < newSec[i].l)
			j++;
		while(j < block.size() && block[j].l <= newSec[i].r) {
			Section tmp = mergy(newSec[i], block[j]);
			if (tmp.appear(q, div))
				return false;
			if (block[j].r <= newSec[i].r)
				j++;
			else
				break;
		}
	}
	return true;
}

int main() {
	freopen("input.txt", "r", stdin);
	//printf("%I64d\n", inf);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		long long l, r;
		scanf("%I64d %I64d", &l, &r);
		sections.push_back(Section(l, r));
	}	
	if (sections[0].l != 1) {
		block.push_back(Section(1, sections[0].l - 1));
	}
	for(int i = 1; i < sections.size(); i++) {
		block.push_back(Section(sections[i - 1].r + 1, sections[i].l - 1));
	}
	block.push_back(Section(sections[sections.size() - 1].r + 1, inf));
	
	for(int i = 1; i <= 9; i++)
		father[i] = i;
	for(int i = 1; i <= 9; i++)
		for(int j = i + 1; j <= 9; j++)
			if (find(i) != find(j)) {
				bool flag = true;
				for(int k = 0; k <= 18 && flag; k++)
					if (!solve(i, j, k))
						flag = false;
				for(int k = 0; k <= 18 && flag; k++)
					if (!solve(j, i, k))
						flag = false;
				if (flag)
					father[father[i]] = father[j];
			}
	static int visit[10];
	for(int i = 1; i <= 9; i++)
		visit[i] = 0;
	for(int i = 1; i <= 9; i++) {
		if (visit[i])
			continue;
		for(int j = i; j <= 9; j++)
			if (!visit[j] && find(i) == find(j)) {
				printf("%d", j);
				visit[j] = 1;
			}
		printf("\n");
	}
	return 0;
} 
