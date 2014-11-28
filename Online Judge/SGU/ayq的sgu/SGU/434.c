#include <stdio.h>
#define oo 1000000000

long f[2100001]={0},a[22]={0},b[22]={0};
long n;

long dp(long now,long s)
{
   long i,t;
   if (!now||f[now])
      return f[now];
   f[now]=oo;
   for (i=1;i<=n;i++)
      if ((now&(1<<(i-1)))&&((s>0)^(a[i]-b[i]>0)))
      {
         t=dp(now-(1<<(i-1)),s+a[i]-b[i]);
         if (t+(s!=b[i]-a[i])<f[now])
            f[now]=t+(s!=b[i]-a[i]);
      }
   return f[now];
}

int main()
{
   long i,j,sa=0,sb=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&a[i]);
      sa+=a[i];
   }
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&b[i]);
      sb+=b[i];
   }
   if (sa!=sb)
   {
      puts("-1");
      goto end;
   }
   for (i=1;i<=n;i++)
      if (a[i]==b[i])
      {
         for (j=i;j<n;j++)
         {
            a[j]=a[j+1];
            b[j]=b[j+1];
         }
         i--;
         n--;
      }
   printf("%ld\n",dp((1<<n)-1,0));
   end:
   return 0;
}
