#include<stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))

int main()
{
   double p;
   long i,n;
   long long t,l,v,ans=0;
   scanf("%lf%ld",&p,&n);
   l=(p+0.0000001)*10000;
   for (i=1;i<=n;i++)
   {
      scanf("%I64d%I64d",&t,&v);
      ans=(ans+t*v*10000)%l;
   }
   printf("%.4lf",min(ans,l-ans)/10000.0);
   return 0;
}
