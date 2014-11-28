#include <stdio.h>
#include <string.h>
#define max(a,b) ((a)>(b)?(a):(b))

long f[1001][27]={0},g[1001][27]={0},dp[61][1001][11]={0},len[61][1001]={0},t[1001]={0},hash[1001]={0},ans[101]={0};
char str[28]={'\0'};
long flag=0;

long dfs(long now,long x)
{
   hash[now]=flag;
   if (g[now][x]&&hash[f[now][x]]==flag)
      return 0;
   if (!g[now][x])
      return f[now][x];
   return dfs(f[now][x],x);
}

int main()
{
   long i,j,a,b,k,s,x,l,n;
   gets(str+1);
   l=strlen(str+1);
   scanf("%ld%ld%ld",&k,&s,&x);
   for (i=1;i<=x;i++)
      scanf("%ld",&t[i]);
   for (i=1;i<=k;i++)
      for (j=1;j<=l;j++)
         scanf("%ld",&f[i][j]);
   for (i=1;i<=k;i++)
      for (j=1;j<=l;j++)
         scanf("%ld",&g[i][j]);
   for (i=1;i<=k;i++)
      for (j=1;j<=l;j++)
         if (g[i][j])
         {
            flag++;
            f[i][j]=dfs(i,j);
            if (f[i][j])
               g[i][j]=0;
         }
   dp[0][s][1]=len[0][s]=1;
   scanf("%ld",&n);
   for (i=0;i<n;i++)
      for (j=1;j<=k;j++)
         if (len[i][j])
            for (a=1;a<=l;a++)
               if (f[j][a])
               {
                  len[i+1][f[j][a]]=max(len[i+1][f[j][a]],len[i][j])+1;
                  for (b=1;b<=len[i+1][f[j][a]];b++)
                  {
                     dp[i+1][f[j][a]][b]+=dp[i][j][b]+dp[i+1][f[j][a]][b-1]/1000000000;
                     dp[i+1][f[j][a]][b-1]%=1000000000;
                  }
                  if (!dp[i+1][f[j][a]][len[i+1][f[j][a]]])
                     len[i+1][f[j][a]]--;
               }
   for (i=1;i<=x;i++)
      for (j=1;j<=10;j++)
      {
         ans[j]+=dp[n][t[i]][j]+ans[j-1]/1000000000;
         ans[j-1]%=1000000000;
      }
   j=0;
   for (i=10;i>=1;i--)
   {
      if (ans[i])
         j++;
      if (j||i==1)
      {
         if (j>1)
            printf("%.9ld",ans[i]);
         else
            printf("%ld",ans[i]);
      }
   }
   printf("\n");
   return 0;
}
