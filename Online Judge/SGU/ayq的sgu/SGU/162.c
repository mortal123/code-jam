#include <stdio.h>
#include <math.h>

int main()
{
   double a,b,c,d,f,e,xd,yd,x,y,z,p;
   scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&e,&f);
   xd=(e*e+d*d-f*f)/(2*d);
   yd=sqrt(e*e-xd*xd);
   x=(a*a+d*d-b*b)/(2*d);
   y=(yd*yd+(xd-x)*(xd-x)-(d-x)*(d-x)-c*c+b*b)/(2*yd);
   z=sqrt(a*a-x*x-y*y);
   p=(d+e+f)/2;
   printf("%.4lf\n",sqrt(p*(p-d)*(p-e)*(p-f))*z/3);
   return 0;
}
