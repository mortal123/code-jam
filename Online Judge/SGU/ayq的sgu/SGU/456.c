#include<stdio.h>

double n,p;
long m;

long check(double now)
{
   long i;
   double s=n;
   for (i=1;i<=m;i++)
   {
      s=s*(1+p)-now;
      if (s<=-0.00000001)
         return -1;
   }
   return 1;
}

int main()
{
   double l=0,r,mid;
   scanf("%lf%ld%lf",&n,&m,&p);
   p/=100;
   r=n*(1+p);
   while (l<r-0.00000001)
   {
      mid=(l+r)/2;
      if (check(mid)<0)
         r=mid;
      else
         l=mid;
   }
   printf("%.5lf",r);
   return 0;
}
