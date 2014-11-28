#include<math.h>
#include<time.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define oo 1000000000
#define pi 3.14159265359
#define zero(a) (abb(a)<=1e-7)
#define lowbit(a) ((a)&(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abb(a) ((a)>0?(a):(-(a)))
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y2))
#define dj(x1,y1,x2,y2) ((x1)*(y1)+(y1)*(y2))
#define dis(x1,y1,x2,y2) sqrt(((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1)))

char map[30][30]={0};
long hash[30]={0};
long n,m,ans;

void dfs(long now,long s1,long s2)
{
   long i;
   if (s1>=ans||s1+n-now+1<s2)
      return;
   if (now==n+1)
   {
      ans=s1;
      return;
   }
   dfs(now+1,s1+1,s2);
   for (i=1;i<=m;i++)
      if (map[now][i]=='*')
      {
         if (!hash[i])
            s2++;
         hash[i]++;
      }
   dfs(now+1,s1,s2);
   for (i=1;i<=m;i++)
      if (map[now][i]=='*')
         hash[i]--;
}

int main()
{
   long i,j,l=-1,r,mid;
   scanf("%ld%ld\n",&n,&m);
   for (i=1;i<=n;i++)
      gets(map[i]+1);
   ans=max(n,m);
   dfs(1,0,0);
   printf("%ld\n",ans);
   return 0;
}
