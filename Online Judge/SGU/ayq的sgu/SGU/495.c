#include<stdio.h>
#include<math.h>

int main()
{
   double n,m;
   scanf("%lf%lf",&n,&m);
   printf("%.9lf\n",n*(1-pow((n-1)/n,m)));
   return 0;
}
