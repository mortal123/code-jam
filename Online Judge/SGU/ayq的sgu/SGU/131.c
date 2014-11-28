#include<stdio.h>

long link[512][512]={0},a[10]={0};
long long f[10][512]={0};
long m,n,way,ans=0;

void dfs(long now)
{
   if (now>m)
      way++;
   else if (!a[now])
      dfs(now+1);
   else if (a[now]==1)
   {
      a[now]--;
      if (a[now+1]==3)
      {
	     a[now+1]-=3;
         dfs(now+1);
	     a[now+1]+=3;
      }
      a[now]++;
   }
   else if (a[now]==2)
   {
      a[now]-=2;
      if (a[now+1]==3)
      {
	     a[now+1]-=3;
         dfs(now+1);
	     a[now+1]+=3;
      }
      if (a[now+1]==2||a[now+1]==3)
      {
         a[now+1]-=2;
         dfs(now+1);
	     a[now+1]+=2;
      }
      a[now]+=2;
   }
   else
   {
      a[now]-=3;
      dfs(now+1);
      if (a[now+1]==1||a[now+1]==3)
      {
         a[now+1]--;
         dfs(now+1);
	     a[now+1]++;
      }
      if (a[now+1]==2||a[now+1]==3)
      {
         a[now+1]-=2;
         dfs(now+1);
	     a[now+1]+=2;
      }
      a[now]+=3;
   }
}

long check(long x,long y)
{
   long i;
   for (i=0;i<m;i++)
   {
      a[i+1]=0;
      if ((x&(1<<i))==0)
         a[i+1]++;
      if (y&(1<<i))
         a[i+1]+=2;
   }
   way=0;
   dfs(1);
   return way;
}

int main()
{
   long i,j,k;
   scanf("%ld%ld",&n,&m);
   for (i=0;i<(1<<m);i++)
      for (j=0;j<(1<<m);j++)
         link[i][j]=check(i,j);
   f[0][(1<<m)-1]=1;
   for (i=1;i<=n;i++)
      for (j=0;j<(1<<m);j++)
         for (k=0;k<(1<<m);k++)
            f[i][k]+=link[j][k]*f[i-1][j];
   printf("%I64d\n",f[n][(1<<m)-1]);
   return 0;
}
