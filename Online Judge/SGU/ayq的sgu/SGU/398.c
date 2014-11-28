#include <stdio.h>

char link[55][55]={'\0'},hash[55]={'\0'};
long l[55]={0};
long n;

void dfs(long now,long dis)
{
   long i;
   if (dis==2)
      hash[now]=1;
   else
      for (i=1;i<=n;i++)
         if (link[now][i])
            dfs(i,dis+1);
}

int main()
{
   long i,j,x,a,b,ans=0;
   scanf("%ld%ld",&n,&x);
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&a);
      for (j=1;j<=a;j++)
      {
         scanf("%ld",&b);
         link[i][b]=1;
      }
   }
   dfs(x,0);
   for (i=1;i<=n;i++)
      if (hash[i]&&!link[x][i]&&i!=x)
         l[++ans]=i;
   printf("%ld\n",ans);
   for (i=1;i<=ans;i++)
      printf("%ld%c",l[i],(i==ans)?'\n':' ');
   return 0;
}
