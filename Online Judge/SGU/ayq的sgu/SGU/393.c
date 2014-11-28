#include <stdio.h>

long hash[500]={0},a[18]={0},rec[18]={0};
char str[51][5]={0};
long n,m,ans=14,flag=0;

void dfs(long now,long max)
{
   long i;
   if (max>=ans)
      return;
   if (now==m+1)
   {
      flag++;
      for (i=1;i<=n;i++)
      {
         if (hash[(a[str[i][0]]<<4)+a[str[i][1]]]==flag)
            return;
         hash[(a[str[i][0]]<<4)+a[str[i][1]]]=flag;
      }
      ans=max;
      for (i=1;i<=m;i++)
         rec[i]=a[i];
   }
   else 
      for (i=1;i<=max+1;i++)
      {
         a[now]=i;
         dfs(now+1,max+(i>max));
      }
}

int main()
{
   long i,j;
   scanf("%ld%ld\n",&m,&n);
   for (i=1;i<=n;i++)
   {
      scanf("%s",str[i]);
      str[i][0]-='a'-1;
      str[i][1]-='a'-1;
   }
   dfs(1,0);
   printf("%ld\n",ans);
   for (i=1;i<=ans;i++)
   {
      for (j=1;j<=m;j++)
         if (rec[j]==i)
            putchar(j+'a'-1);
      puts("");
   }
   return 0;
}
