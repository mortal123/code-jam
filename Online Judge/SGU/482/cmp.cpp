#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxint = 0x7fffffff;
const long long max64 = 0x7fffffffffffffffll;
const int N = 5010;
const int inf = 1 << 28;
int n;
int dp[N][128],pre[N][128][2],h[N],perimeter,area,res,out[N],top,vis[128];
int cacu(int h, int last) { return h-last+abs(h-last)+2; }

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output2.txt", "w", stdout);
    int i,j,k,s,x,y;
    scanf("%d",&n);
    h[0] = 0,perimeter = 0,area = 0,res = 0;
    for(i = 1;i <= n;i++) {
        scanf("%d",h + i);
        perimeter += cacu(h[i],h[i-1]);
        area += h[i];
    }
    for(i = 0;i < N;i++) {dp[0][i] = 0;}
    for(i = 1;i < N;i++) {
        for(j = 0;j < N;j++) {
            dp[i][j] = -1;
        }
    }
    for(i = 1;i <= n;i++) {
        for(s = h[i];s < N;s++) {
            for(j = i - 1;j >= 0;j --) {
                if(dp[s-h[i]][j] >= 0) {
                    if (dp[s][i] < dp[s-h[i]][j] + cacu(h[i],h[j])) {
                        dp[s][i] = dp[s-h[i]][j] + cacu(h[i],h[j]);
                        pre[s][i][0] = s - h[i];
                        pre[s][i][1] = j;
                     }
                 }
             }
             if(dp[s][i] + dp[s][i] >= perimeter) {
                 if (res < area - s) {
                     res = area - s;
                     x = s,y = i;
                 }
             }
         }
     }
     printf("%d\n",res);
     if(res > 0) {
         while(x != 0 && y != 0) {
             vis[y] = 1;
             int tx = pre[x][y][0];
             int ty = pre[x][y][1];
             x = tx,y = ty;
         }
         for(i = 1;i <= n;i++) {
             if(!vis[i]) {
                 out[top++] = i;
             }
         }
     }
     printf("%d\n",top);
     
     if(top > 0)
         printf("%d",out[0]);
     for(i = 1;i < top;i++) {
         printf(" %d",out[i]);
     }
     if(top > 0)
         putchar(10);
     
     return 0;
 }
 
