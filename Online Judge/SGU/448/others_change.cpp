#include <stdio.h>
#define lowbit(a) ((a)&(-(a)))

int p[17][17],f[65537][17][5];
char hash[65537][17][6];
int n,m;
int dp(int, int, int);

void dfs(int cur,int win,int h,int now,int x,int a,int b)
{
   int i;
   if (now>n)
   {
      for (i=1;i<=n;i++)
         if ((x&(1<<i-1))&&p[win][i])
            f[cur][win][h]+=dp(cur^x,win,h-1)*dp(x,i,h-1);
   }
   else if (!(cur&(1<<now-1))||now==win)
      dfs(cur,win,h,now+1,x,a,b);
   else
   {
      if (a)
         dfs(cur,win,h,now+1,x-(1<<now-1),a-1,b);
      if (b)
         dfs(cur,win,h,now+1,x,a,b-1);
   }
}

int dp(int now,int win,int h)
{
   int i,s=0;
   if (lowbit(now)==now)
      return now==(1<<win-1);
   if (hash[now][win][h])
      return f[now][win][h];
   hash[now][win][h]=1;
   for (i=1;i<=n;i++)
      if (now&(1<<i-1))
         s++;
   dfs(now,win,h,1,now-(1<<win-1),s / 2, s - s / 2 - 1);
   return f[now][win][h];
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
   int i,j;
   scanf("%d%d",&n,&m);
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
         scanf("%d",&p[i][j]);
   j=0;
   for (i=1;i<n;i*=2)
      j++;
   printf("%d\n",dp((1<<n)-1,m,j));
   return 0;
}
