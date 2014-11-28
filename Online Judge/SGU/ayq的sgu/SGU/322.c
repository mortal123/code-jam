#include <stdio.h>

long hash[2001]={0},next[10002]={0},last[10002]={0},e[10002]={0};
char rec[2001][2001]={0},link[2001][2001]={0};
long totm,a,b,flag=0;

void add(long a,long b)
{
   e[++totm]=b;
   last[totm]=a;
   next[totm]=next[a];
   next[last[totm]]=last[next[totm]]=totm;
}

void del(long a)
{
   next[last[a]]=next[a];
   last[next[a]]=last[a];
}

long dfs(long x,long y)
{
   long i;
   if (x==y)
      return 1;
   hash[y]=flag;
   for (i=next[y];i;i=next[i])
      if (hash[e[i]]!=flag&&dfs(x,e[i]))
      {
         if (!link[y][e[i]])
         {
            a=y;
            b=i;
         }
         return 1;
      }
   return 0;
}

int main()
{
   long i,j,n,ans=0;
   scanf("%ld",&n);
   totm=n+!(n&1);
   for (i=1;i<n;i++)
   {
      scanf("%ld%ld",&a,&b);
      rec[a][b]=rec[b][a]=1;
      add(a,b);
      add(b,a);
   }
   for (i=1;i<n;i++)
   {
      scanf("%ld%ld",&a,&b);
      link[a][b]=link[b][a]=1;
   }
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         if (!rec[i][j]&&link[i][j])
            ans++;
   printf("%ld\n",ans);
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         if (!rec[i][j]&&link[i][j])
         {
            flag++;
            dfs(i,j);
            del(b);
            del(b^1);
            add(i,j);
            add(j,i);
            printf("1 %ld %ld %ld %ld\n",i,j,a,e[b]);
         }
   return 0;
}
