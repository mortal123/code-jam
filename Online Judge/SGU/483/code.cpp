#include <cstdio>
#include <cstdlib>
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;

vector<int> l, r;
int n, h;

int main () {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	l.clear();
	r.clear();
	cin >> n >> h;
	h++;
	int center = h * h;
	int count = center;
	for(int i = h; count <= n; i++) {
		if (count + i <= n)
			l.push_back(count + i);
		if (count + 2 * i <= n)
			r.push_back(count + 2 * i);
		count += 2 * i;
	}
	for(int i = l.size() - 1; i >= 0; i--)
		cout << l[i] << " ";
	cout << center;
	for(int i = 0; i < r.size(); i++)
		cout << " " << r[i];
	cout << endl;
	return 0; 
}
