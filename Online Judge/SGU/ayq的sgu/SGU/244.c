#include <stdio.h>
#include <math.h>
#define abb(a) ((a)>0?(a):(-(a)))
#define zero(a) (abb(a)<=1e-7)

double h,d,m;

long work()
{
   double x,t,p,q;
   if (d<h||m<h)
      return 0;
   p=sqrt(m*m-h*h+1e-50);
   q=p-sqrt(d*d-h*h+1e-50);
   if (zero(p-q))
   {
      if (zero(p))
         x=1;
      else
         return 0;
   }
   else
   {
      t=q*(p*p+h*h-p*q)/(p-q)+1e-50;
      if (t<0)
         return 0;
      x=sqrt(t);
   }
   if (abb(q)>=x-1e-7)
      return 0;
   printf("YES\n%.8lf %.8lf\n%.8lf %.8lf\n%.8lf %.8lf\n",p,h,-x,0.0,x,0.0);
   return 1;
}

int main()
{
   scanf("%lf%lf%lf",&h,&d,&m);
   if (!work())
      printf("NO\n");
   return 0;
}
