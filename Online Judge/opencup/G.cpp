#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> State;
typedef pair<State, double> Pair;
typedef vector<Pair> Map;

const int N = 6;

double pro[N][N][2];
int n, m, visit[N + 1];

int minimize(vector<int> &state) {
	fill(visit, visit + m + 1, -1);
	visit[0] = 0;
	visit[m] = m;
	int cnt = 0;
	bool found = false;
	for(int i = 0; i < (int)state.size(); i++) {
		int t = state[i];
		if (visit[state[i]] == -1) {
			visit[state[i]] = ++cnt;
		}
		state[i] = visit[state[i]];
		found |= (!state[i]);
	}
	return found;
}

int replace(State &state, int v, int tv) {
	if (v != m) {
		for(int i = 0; i < (int)state.size(); i++) {
			if (state[i] == v)
				state[i] = tv;
		}
	}
}

double solve(int bx, int by) {
	if (bx == 0 && by == 0)
		return 0;
	Map* states = new Map();
	{
		State s(m, m);
		s[m - 1] = 0;
		states->push_back(make_pair(s, pro[0][0][1]));
	}
	
	for(int i = 0; i < n; i++)
		for(int j = !i; j < m; j++) {
			Map* newStates = new Map();
			sort(states->begin(), states->end());
			for(auto it = states->begin(); it != states->end(); ) {
				double sp = 0;
				Map :: iterator cp = it;
				while(it != states->end() && it->first == cp->first)
					sp += (it++)->second;
				for(int iter = 0; iter < 2; iter++) {
					if (i == bx && j == by && iter)
						continue;
					State state = cp->first;
					if (iter) {
						int id = state[0];
						if (j) {
							id = min(id, state[m - 1]);
						}
						if (id == m) {
							id = m - 1;
						}
						replace(state, state[0], id);
						if (j) {
							replace(state, state[m - 1], id);
						}
						state.push_back(id);
					} else {
						state.push_back(m);
					}
					state = State(state.begin() + 1, state.end());
					if (minimize(state) && pro[i][j][iter] > 0.) {
						newStates->push_back(make_pair(state, sp * pro[i][j][iter]));
					}
				}	
			}
			delete states;
			states = newStates;
		}
	
	double result = 0;
	for(int i = 0; i < (int)((*states).size()); i++) {
		if ((*states)[i].first[m - 1] == 0)
			result += (*states)[i].second;
	}
	
	return result;
}

int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++) {
			scanf("%lf", &pro[i][j][0]);
			pro[i][j][1] = 1 - pro[i][j][0];
		}	
	double all = solve(-1, -1);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			double result = solve(i, j) / all;
			printf("%.6f%c", result, j == m - 1 ? '\n' : ' ');
		}
	}
}
