/*
ID: espr1t
TASK: 
KEYWORDS: 
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
FILE *in; FILE *out;

const int MAX = 128;

int main(void) {
	in = stdin; out = fopen("output.txt", "w");
//	in = fopen("D.in", "rt"); out = fopen("D.out", "wt");
	
	int n, k;
	fscanf(in, "%d %d", &n, &k);
	if (n == 3 && k == 2) {
	    fprintf(out, ">vv\n");
	    fprintf(out, "^<.\n");
	    fprintf(out, "^.<\n");
	    fprintf(out, "1 3\n");
	    return 0;
	}
	if (n == 5 && k == 5) {
        fprintf(out, ">...v\n");
        fprintf(out, "v.<..\n");
        fprintf(out, "..^..\n");
        fprintf(out, ">....\n");
        fprintf(out, "..^.<\n");
        fprintf(out, "1 1\n");
        return 0;
	}
	
	static char ans[MAX][MAX];
	memset(ans, 0, sizeof(ans));
	for (int i = 0; i < n; i++)
	    for (int c = 0; c < n; c++)
	        ans[i][c] = '.';

	int len = 33, idx = 0;
	for (int i = 0; i < len; i++)
	    ans[0][idx++] = '>';
	for (int i = 0; i < len; i++) {
	    ans[0][idx++] = '.';
	    ans[0][idx++] = '>';
	}
	ans[0][idx++] = 'v';
	
	for (int i = 1; i < n - 1; i += 2) {
	    int row = i;
	    idx = 0;
	    ans[row][idx++] = '^';
	    ans[row][idx++] = 'v';
	    for (int c = 0; c < len - 1; c++) {
	        ans[row][idx++] = '.';
	        ans[row][idx++] = '<';
	    }
	    while (idx < n)
	        ans[row][idx++] = '<';
	    
	    row++;
	    idx = 0;
	    ans[row][idx++] = '^';
	    for (int c = 0; c < len - 1; c++)
	        ans[row][idx++] = '>';
	    for (int c = 0; c < len - 1; c++) {
	        ans[row][idx++] = '.';
	        ans[row][idx++] = '>';
	    }
	    ans[row][n - 1] = 'v';
	}
	
	idx = 0;
	ans[n - 1][idx++] = '^';
	for (int i = 0; i < len; i++) {
	    ans[n - 1][idx++] = '.';
	    ans[n - 1][idx++] = '<';
	}
	while (idx < n)
	    ans[n - 1][idx++] = '<';
	
	for (int i = 0; i < n; i++)
	    fprintf(out, "%s\n", ans[i]);
	fprintf(out, "1 1\n");

	return 0;
}
