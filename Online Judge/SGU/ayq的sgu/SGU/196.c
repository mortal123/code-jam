#include<stdio.h>

long f[10001]={0};

int main()
{
   long i,n,m,a,b;
   long long ans=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld",&a,&b);
      f[a]++;
      f[b]++;
   }
   for (i=1;i<=n;i++)
      ans+=(long long)f[i]*f[i];
   printf("%I64d\n",ans);
   return 0;
}
