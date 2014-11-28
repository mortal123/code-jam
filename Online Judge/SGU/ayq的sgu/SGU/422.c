#include <stdio.h>
#define oo 1e20
#define min(a,b) ((a)<(b)?(a):(b))

double f[3002]={0},a[3002]={0};

int main()
{
   long i,j,n,t;
   double p,s,v;
   scanf("%ld%ld",&n,&t);
   for (i=1;i<=n;i++)
      scanf("%lf",&a[i]);
   for (i=n;i>=1;i--)
   {
      f[i]=oo;
      p=1;
      v=t+1;
      s=0;
      for (j=1;i+j<=n+1;j++)
      {
         f[i]=min(f[i],(v+p*(1-a[i+j-1])*f[i+j]+j*a[i])/(1-a[i]));
         p*=1-a[i+j-1];
         s+=p*a[i+j];
         v+=s+f[i+j]*(p*a[i+j])+1;
      }
   }
   printf("%.10lf\n",f[1]);
   return 0;
}
