#include <stdio.h>

long c[1001]={0},du[1001]={0},rec[1001]={0};
char hash[1001]={0},g[1001][1001]={0};

int main()
{
   long i,n,m,t,a,b,p,v=0,tot=0;
   long long ans=0;
   scanf("%ld%ld",&n,&t);
   for (i=1;i<=n;i++)
      scanf("%ld",&c[i]);
   scanf("%ld",&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld",&a,&b);
      g[a][b]=1;
      du[b]++;
   }
   while (1)
   {
      p=0;
      for (i=1;i<=n;i++)
         if (!du[i]&&!hash[i]&&(!p||c[i]<c[p]))
            p=i;
      v+=c[p];
      if (!p||v>t)
         break;
      for (i=1;i<=n;i++)
         du[i]-=g[p][i];
      hash[p]=1;
      rec[++tot]=p;
      ans+=v;
   }
   printf("%ld %I64d\n",tot,ans);
   for (i=1;i<=tot;i++)
      printf("%ld%c",rec[i],(i==tot)?'\n':' ');
   return 0;
}
