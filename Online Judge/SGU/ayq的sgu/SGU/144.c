#include<stdio.h>

int main()
{
   long x,y;
   double z;
   scanf("%ld%ld%lf",&x,&y,&z);
   printf("%.7lf\n",z*(60*(y-x)-z/2)/(1800*(y-x)*(y-x)));
   return 0;
}
