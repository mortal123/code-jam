#include <stdio.h>
#include <math.h>

int main()
{
   double i,a,b,t,eps,ans=0;
   scanf("%lf%lf",&a,&b);
   if (a>b)
   {
      t=a;
      a=b;
      b=t;
   }
   eps=a/40000000;
   ans=a*b;
   for (i=eps;i<=a-eps;i+=eps)
      ans+=2*sqrt((a*a-i*i)*(b*b-i*i));
   printf("%.10lf\n",4*ans*eps);
   return 0;
}
