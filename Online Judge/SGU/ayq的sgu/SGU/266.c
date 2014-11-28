#include <stdio.h>
#include <math.h>
#define pi 3.14159265359
#define abb(a) ((a)>0?(a):(-(a)))
#define max(a,b) ((a)>(b)?(a):(b))
#define dis(x1,y1,z1,x2,y2,z2) sqrt(((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1))+((z2)-(z1))*((z2)-(z1)))

int main()
{
   double i,r,r2,x1,y1,z1,x2,y2,z2,a,b,c,d,x,y,ans,eps,dis,sina;
   scanf("%lf%lf%lf%lf%lf%lf%lf",&r,&x1,&y1,&z1,&x2,&y2,&z2);
   a=dis(x1,y1,z1,0,0,0);
   b=dis(x2,y2,z2,0,0,0);
   d=sqrt(b*b-r*r);
   c=dis(x1,y1,z1,x2,y2,z2);
   ans=2*pi*r*(2*r+(b*b-r*r)/b-b+(a*a-r*r)/a-a);
   dis=a-(a*a-r*r)/a;
   x=(a*a+b*b-c*c)/2/a;
   y=sqrt(abb(b*b-x*x));
   eps=(r-dis)/300000;
   if (y>1e-8)
      for (i=dis+eps/2;i<r;i+=eps)
      {
         r2=sqrt(r*r-i*i);
         sina=((x-i)*(x-i)+y*y+r2*r2-d*d)/2/r2/y;
         if (sina>-1&&sina<1)
            ans-=(pi/2-asin(sina))*2*r*eps;
         else if (sina<=-1)
            ans-=2*r*pi*eps;
      }
   else if (x>0)
      ans=2*pi*r*(r+max((b*b-r*r)/b-b,(a*a-r*r)/a-a));
   printf("%.3lf\n",ans);
   return 0;
}
