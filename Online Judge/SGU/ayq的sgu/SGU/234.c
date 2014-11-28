#include <stdio.h>

long map[202][202]={0},f[201][201]={0},w[5][2]={{},{-1,0},{0,-1},{0,1},{1,0}},hash[201][201]={0};
char rec[202][202]={'\0'};
long n,m,flag=0;

long match(long x,long y)
{
   long i,px,py;
   for (i=1;i<=4;i++)
   {
      px=x+w[i][0];
      py=y+w[i][1];
      if (map[px][py]&&hash[px][py]!=flag&&!f[px][py])
      {
         f[px][py]=i;
         return 1;
      }
   }
   for (i=1;i<=4;i++)
   {
      px=x+w[i][0];
      py=y+w[i][1];
      if (map[px][py]&&hash[px][py]!=flag)
      {
         hash[px][py]=flag;
         if (match(px-w[f[px][py]][0],py-w[f[px][py]][1]))
         {
            f[px][py]=i;
            return 1;
         }
      }
   }
   return 0;
}

void dfs(long x,long y,long c)
{
   if (!c)
      rec[x][y]='G';
   else
      rec[x][y]='.';
   if (map[x-1][y]&&!rec[x-1][y]&&(!c||f[x][y]==4))
      dfs(x-1,y,c^1);
   if (map[x][y-1]&&!rec[x][y-1]&&(!c||f[x][y]==3))
      dfs(x,y-1,c^1);
   if (map[x][y+1]&&!rec[x][y+1]&&(!c||f[x][y]==2))
      dfs(x,y+1,c^1);
   if (map[x+1][y]&&!rec[x+1][y]&&(!c||f[x][y]==1))
      dfs(x+1,y,c^1);
}

int main()
{
   long i,j,ans=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
      {
         scanf("%ld",&map[i][j]);
         if (map[i][j])
            ans++;
         else
            rec[i][j]='#';
      }
   for (i=1;i<=n;i++)
      for (j=(i&1)+1;j<=m;j+=2)
         if (map[i][j])
         {
            flag++;
            ans-=match(i,j);
         }
   printf("%ld\n",ans);
   flag++;
   for (i=1;i<=n;i++)
      for (j=!(i&1)+1;j<=m;j+=2)
         if (f[i][j])
         {
            hash[i][j]=hash[i-w[f[i][j]][0]][j-w[f[i][j]][1]]=flag;
            f[i-w[f[i][j]][0]][j-w[f[i][j]][1]]=5-f[i][j];
         }
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         if (!rec[i][j]&&hash[i][j]!=flag)
            dfs(i,j,0);
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         if (!rec[i][j])
            dfs(i,j,0);
   for (i=1;i<=n;i++)
   {
      for (j=1;j<=m;j++)
         printf("%c",rec[i][j]);
      printf("\n");
   }
   return 0;
}
