#include<stdio.h>

long e[10001]={0},next[10001]={0},head[101]={0},du[101]={0},f[101]={0},ans[101]={0},d[101]={0};
long totm=0;

void add(long a,long b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   du[b]++;
}

int main()
{
   long i,a,b,n,m,now,tot=0,st=1,en=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld",&a,&b);
      add(a,b);
   }
   for (i=1;i<=n;i++)
      if (!du[i])
         d[++en]=i;
   while (st<=en)
   {
      now=d[st++];
      f[++tot]=now;
      for (i=head[now];i;i=next[i])
      {
         du[e[i]]--;
         if (!du[e[i]])
            d[++en]=e[i];
      }
   }
   if (tot==n)
   {
      for (i=1;i<=n;i++)
         ans[f[i]]=i;
      for (i=1;i<n;i++)
         printf("%ld ",ans[i]);
      printf("%ld\n",ans[n]);
   }
   else
      printf("No solution\n");
   return 0;
}
