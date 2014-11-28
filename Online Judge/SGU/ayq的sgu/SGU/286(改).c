#include <stdio.h>

long e[250505]={0},next[250505],last[250505]={0},link[501][501]={0},num[501][501]={0},f[501]={0},hash[501]={0};
char app[250005]={'\0'};
long n,tot,flag=1;

void add(long a,long b)
{
   e[++tot]=b;
   next[tot]=next[a];
   last[tot]=a;
   last[next[tot]]=next[last[tot]]=tot;
}

void dfs(long now)
{
   long i;
   hash[now]=1;
   for (i=next[now];i;i=next[now])
   {
      link[now][e[i]]=1;
      next[last[i]]=next[i];
      last[next[i]]=last[i];
      next[last[i^1]]=next[i^1];
      last[next[i^1]]=last[i^1];
      dfs(e[i]);
   }
}

long match(long now)
{
   long i;
   for (i=1;i<=n;i++)
      if (link[now][i]&&hash[i]!=flag)
      {
         hash[i]=flag;
         if (!f[i]||match(f[i]))
         {
            f[i]=now;
            return 1;
         }
      }
   return 0;
}

int main()
{
   long i,k,a,b;
   scanf("%ld%ld",&n,&k);
   tot=n+1+(n&1);
   for (i=1;i<=n*k/2;i++)
   {
      scanf("%ld%ld",&a,&b);
      num[a][b]=num[b][a]=i;
      add(a,b);
      add(b,a);
   }
   for (i=1;i<=n;i++)
      if (!hash[i])
         dfs(i);
   for (i=1;i<=n;i++)
   {
      flag++;
      if (!match(i))
      {
         printf("NO\n");
         goto end;
      }
   }
   printf("YES\n");
   for (i=1;i<=n;i++)
      app[num[f[i]][i]]=1;
   for (i=1;i<=n*k/2;i++)
      if (app[i])
         printf("%ld\n",i);
   end:
       system("pause");
   return 0;
}
