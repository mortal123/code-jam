#include <stdio.h>

long map[105][105]={0};
char hash[105]={'\0'},ans[105]={'\0'};
long n;

long dfs(long now,long last,long h)
{
   long i,flag=0;
   hash[now]=1;
   for (i=1;i<=n;i++)
      if (map[now][i]&&(i!=last||map[now][i]>1))
      {
         if (!hash[i])
         {
            if (dfs(i,now,h+1))
               ans[now]=flag=1;
         }
         else if (h>1&&(i==1||map[1][i]>1))
            ans[1]=ans[i]=flag=1;
      }
   return flag;
}

int main()
{
   long i,m,a,b,d=0,s=0,flag=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld",&a,&b);
      if (a==1||b==1)
         d=1;
      map[a][b]++;
      map[b][a]++;
   }
   dfs(1,0,0);
   for (i=2;i<=n;i++)
      if (map[1][i]>1)
         s++;
   if (s>1||!d)
      ans[1]=1;
   for (i=2;i<=n;i++)
   {
      if (hash[i]&&(!map[1][i]||(map[1][i]&1)||s>1))
         ans[i]=1;
      if (map[1][i]>1&&!(map[1][i]&1))
         ans[1]=1;
   }
   for (i=1;i<=n;i++)
      if (ans[i])
      {
         if (flag)
            printf(" ");
         flag=1;
         printf("%ld",i);
      }
   printf("\n");
   return 0;
}
