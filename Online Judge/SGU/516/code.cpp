#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXLEN = 1000000;
const int WEEKLEN = 11000;
const int MAXN = 100005;
const int NAMELEN = 100;

struct Name {
	struct Node {
		int id;
		Node *next[52];
		Node() {
			id = -1;
		}
	};
	
	Node Me[MAXLEN];
	Node *root;
	int totID, use;
	
	Name() {
		totID = 0;
		root = &Me[use = 1];
	}
	
	int char2int(char x) {
		if (x >= 'A' && x <= 'Z')
			return x - 'A';
		return x - 'a' + 26;
	}
	
	int askID(char buf[]) {
		Node *tmp = root;
		int idx;
		for(int i = 0; buf[i]; i++) {
			idx = char2int(buf[i]);
			if (tmp->next[idx] == NULL) {
				tmp->next[idx] = &Me[++use];
			}
			tmp = tmp->next[idx];
		}
		if (tmp->id == -1)
			tmp->id = totID++;
		return tmp->id; 
	}
}names;

int invalidCnt = 0, slot = 0, hash[MAXN * 2], timeChecker[MAXN * 2];
int T1, T2, n, m, T;

vector<pair<int, int> > tmp;

struct WeekInfo {
	vector<pair<int, int> > duty;
	int start, end;
	bool invalid;
	WeekInfo() {
		duty.clear();
		invalid = false;
	}
	void push(int L, int R, int ID) {
		L = max(L, start);
		R = min(R, end);
		if (L > R)
			return;
		invalidCnt -= invalid;
		invalid = false;
		if (L <= start && R >= end) {
			duty.clear();
			duty.push_back(make_pair(R, ID));
			if (end - start + 1 > T * 60)
				invalid = true;
			invalidCnt += invalid;
			return;
		}
		tmp.clear();
		int i = 0;
		while(i < duty.size()) {
			pair<int, int> now = make_pair(min(duty[i].first, L - 1), duty[i].second);
			if (now.first >= start)
				tmp.push_back(now);
			if (now.first == L - 1)
				break;
			++i;
		}
		tmp.push_back(make_pair(R, ID));
		while(i < duty.size() && duty[i].first <= R)
			++i;
		while(i < duty.size()) {
			tmp.push_back(duty[i]);
			++i;
		}
		duty = tmp;
		++slot;
		int last = start;
		for(int i = 0; i < duty.size(); i++) {
			if (hash[duty[i].second] != slot) {
				hash[duty[i].second] = slot;
				timeChecker[duty[i].second] = 0;
			}
			if ((timeChecker[duty[i].second] += duty[i].first - last + 1) > T * 60) {
				invalid = true;
				break;
			}
			//printf("warn %d\n", timeChecker[duty[i].second]);
			last = duty[i].first + 1;
		}
		invalidCnt += invalid;
	}
	void show() {
		printf("begin at %d\n", start);
		for(int i = 0; i < duty.size(); i++) {
			printf("%d %d\n", duty[i].first, duty[i].second);
		}
		printf("end at %d\n\n", end);
	}
}weeks[670];
int weekNum;

int readInt(char buf[], int l, int r) {
	int res = 0;
	for(int i = l; i <= r; i++)
		res = res * 10 + buf[i] - '0';
	return res;
}

int Time[13][32][24][60], extra[1000000], Month[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

int readTime() {
	static char bufTime1[20], bufTime2[20];
	scanf("%s %s", bufTime1, bufTime2);
	int MM = readInt(bufTime1, 5, 6);
	int DD = readInt(bufTime1, 8, 9);
	int hh = readInt(bufTime2, 0, 1);
	int mm = readInt(bufTime2, 3, 4);
	return Time[MM][DD][hh][mm];
}

int readName() {
	static char buf[NAMELEN];
	scanf("%s", buf);
	return names.askID(buf);
}

void init() {
	weekNum = 0;
	int weekDay = 4, minute = 0, ext = 0;
	for(int MM = 1; MM <= 12; MM++)
		for(int DD = 1; DD <= Month[MM]; DD++) {
			if (weekNum == 0 || weekDay == 1) {
				weeks[++weekNum].start = ext + 1;
			}
			//printf("%d %d %d\n", MM, DD, minute);
			for(int hh = 0; hh < 24; hh++)
				for(int mm = 0; mm < 60; mm++) {
					Time[MM][DD][hh][mm] = minute;
					extra[minute++] = ext;
					if (!(weekDay <= 5 && hh >= 9 && hh < 18)) 
						ext++;
				}
			if (weekDay == 7) {
				weeks[weekNum].end = ext;
			}
			weekDay = weekDay % 7 + 1;
		}
}

void modify(int L, int R, int ID) {
	L = max(extra[L] + 1, extra[T1] + 1); 
	R = min(extra[T2], extra[R]);
	if (L > R)
		return;
	for(int i = 1; i <= weekNum; i++) {
		if (weeks[i].start > weeks[i].end)
			continue;
		weeks[i].push(L, R, ID);
		//weeks[i].show();
	}
}

int nameIDs[MAXN], timeSlots[MAXN];

int main() {
	freopen("input.txt", "r", stdin);
	init();
	scanf("%d %d %d", &n, &m, &T);
	T1 = readTime(); T2 = readTime();
	for(int i = 1; i <= weekNum; i++) {
		weeks[i].start = max(weeks[i].start, extra[T1] + 1);
		weeks[i].end = min(weeks[i].end, extra[T2]);
	}
	for(int i = 1; i <= n; i++) {
		timeSlots[i] = readTime();
		nameIDs[i] = readName();
	}
	timeSlots[n + 1] = T2;
	for(int i = 1; i <= n; i++) {
		modify(timeSlots[i], timeSlots[i + 1], nameIDs[i]);
	}
	
	int ans = 0, lastTime = T1;
	for(int i = 1; i <= m; i++) {
		int t1 = readTime(), t2 = readTime(), t3 = readTime();
		int nameID = readName();
		if (t1 >= T2)
			continue;
		if (invalidCnt == 0)
			ans += max(t1 - lastTime, 0);
		modify(t2, t3, nameID);
		lastTime = max(lastTime, t1);
	}
	if (invalidCnt == 0)
		ans += T2 - lastTime;
	//printf("%d %d\n", ans, (T2 - T1));
	printf("%.12lf", (double)ans / (T2 - T1));
}
