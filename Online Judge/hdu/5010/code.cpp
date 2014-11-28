#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int N = 10;
const int MOD = 1e7 * 4 + 7;

char map[N][N];
int visit[MOD + 1], id[N][N];
int n = 6, m = 8, times = 0, tot;
int dist[MOD + 1], queue[MOD + 1], hit[N][N], times2;
pair<int, int> pigs[N], mouses[N], squ[N], nut, pos[N * N];

int dx[] = {1, 0, 0, -1};
int dy[] = {0, 1, -1, 0};
int tail, s[3], totalCalc;
vector<int > vec;

void myAssert(bool flag) {
	if (!flag) {
		int a = 0, b = 1;
		b /= a;
	}
}

int simple(int state) {
	vec.clear();
	for(int i = 0; i < s[0] + s[1] + s[2]; i++) {
		vec.push_back(state % tot);
		state /= tot;
	}	
	reverse(vec.begin(), vec.end());
	sort(vec.begin(), vec.begin() + s[0]);
	sort(vec.begin() + s[0], vec.begin() + s[0] + s[1]);
	sort(vec.begin() + s[0] + s[1], vec.end());
	for(int i = 0; i < s[0] + s[1] + s[2]; i++) {
		state = state * tot + vec[i];
	}
	return state;
}

int go(int state, int x, int y, int dx, int dy, int type, int power, int ds) {
	if (x == -1 && y == -1) {
		return 0;
	}
	totalCalc++;
	state -= id[x][y] * power;
	bool eaten = false;
	while(!eaten) {
		x += dx;
		y += dy;
		if (x < 0 || x >= n || y < 0 || y >= m || hit[x][y] == times2 || map[x][y] != '.') {
			x -= dx;
			y -= dy;
			break;
		}
		if (type != 2) {
			for(int j = 0; j < s[2]; j++) {
				if (abs(x - pigs[j].first) + abs(y - pigs[j].second) == 1) {
					eaten = true;
				}
			}
			if (eaten) {
				break;
			}
		} else {
			int pp = 1;
			for(int j = 0; j < s[2]; j++) {
				pp *= tot;
			}
			for(int j = s[1] - 1; j >= 0; j--) {
				if (abs(x - mouses[j].first) + abs(y - mouses[j].second) == 1) {
					eaten = true;
					state -= id[mouses[j].first][mouses[j].second] * pp;
				}
				pp *= tot;
			}
			
			for(int j = s[0] - 1; j >= 0; j--) {
				if (abs(x - squ[j].first) + abs(y - squ[j].second) == 1) {
					return 0;
				}
			}
		}
		if (abs(x - nut.first) + abs(y - nut.second) == 1) {
			return type == 0;
		}
	}
	
	if (!eaten || eaten && type == 2) {
		state += id[x][y] * power;
	}
	
	//state = simple(state);
	//cout << state % MOD << endl;
	if (visit[state] == times) {
		return 0;
	}
	visit[state % MOD] = times;
	dist[tail] = ds + 1;
	queue[tail++] = state;
	return 0;
}

int main() {
	freopen("input.txt", "r", stdin);
	while(scanf("%s", map[0]) == 1) {
		totalCalc = 0;
		for(int i = 1; i < n; i++) {
			scanf("%s", map[i]);
		}
		pos[0] = make_pair(-1, -1);
		tot = 1;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++) {
				if (map[i][j] == 'S' || map[i][j] == 'M') {
					for(int d = 0; d < 4; d++) {
						int x = i + dx[d], y = j + dy[d];
						if (x >= 0 && y >= 0 && x < n && y < m && map[x][y] == 'P') {
							map[i][j] = '.';
						}
					}
				}
				if (map[i][j] == 'N') {
					nut = make_pair(i, j);
				}
				if (map[i][j] != '#') {
					pos[tot] = make_pair(i, j);
					id[i][j] = tot++;
				}
			}
		++times;
		int source = 0;
		for(int i = 0; i < 3; i++) {
			s[i] = 0;
		}
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++) {
				if (map[i][j] == 'S') {
					source = source * tot + id[i][j];
					squ[s[0]] = make_pair(i, j);
					s[0]++;
				}
			}
		
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++) {
				if (map[i][j] == 'M') {
					source = source * tot + id[i][j];
					mouses[s[1]] = make_pair(i, j);
					s[1]++;
				}
			}
		
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++) {
				if (map[i][j] == 'P') {
					source = source * tot + id[i][j];
					pigs[s[2]] = make_pair(i, j);
					s[2]++;
				}
			}
		
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++) {
				if (map[i][j] != '#') {
					map[i][j] = '.';
				}
			}
		
		visit[source] = times;
		dist[0] = 0;
		tail = 0;
		queue[tail++] = source;
		for(int head = 0; head < tail; head++) {
			int state = queue[head];
			int ss = queue[head];
			//puts("P");
			++times2;
			for(int i = s[2] - 1; i >= 0; i--) {
				pigs[i] = pos[state % tot];
				state /= tot;
				hit[pigs[i].first][pigs[i].second] = times2;
				//printf("%d %d\n", pigs[i].first, pigs[i].second);
			}
			//puts("M");
			for(int i = s[1] - 1; i >= 0; i--) {
				mouses[i] = pos[state % tot];
				state /= tot;
				hit[mouses[i].first][mouses[i].second] = times2;
				//printf("%d %d\n", mouses[i].first, mouses[i].second);
			}
			//puts("S");
			for(int i = s[0] - 1; i >= 0; i--) {
				squ[i] = pos[state % tot];
				state /= tot;
				hit[squ[i].first][squ[i].second] = times2;
				//printf("%d %d\n", squ[i].first, squ[i].second);
			}
			//printf("(%d %d)\n", head, dist[head]);
			int power = 1;
			for(int i = s[2] - 1; i >= 0; i--) {
				for(int dir = 0; dir < 4; dir++) {
					go(ss, pigs[i].first, pigs[i].second, dx[dir], dy[dir], 2, power, dist[head]);
				}
				power *= tot;
			}
			for(int i = s[1] - 1; i >= 0; i--) {
				for(int dir = 0; dir < 4; dir++) {
					go(ss, mouses[i].first, mouses[i].second, dx[dir], dy[dir], 1, power, dist[head]);
				}
				power *= tot;
			}
			
			for(int i = s[0] - 1; i >= 0; i--) {
				for(int dir = 0; dir < 4; dir++) {
					if (go(ss, squ[i].first, squ[i].second, dx[dir], dy[dir], 0, power, dist[head])) {
						printf("%d", dist[head] + 1);
						//printf("%d %d\n", pigs[0].first, pigs[0].second);
						goto finish;
					}
				}
				power *= tot;
			}
		}
		myAssert(false);
		finish:puts("");
	}
	return 0;
}
