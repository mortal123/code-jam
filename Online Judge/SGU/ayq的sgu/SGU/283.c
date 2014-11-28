#include <stdio.h>
#include <math.h>

int main()
{
   double x1,y1,vx1,vy1,r1,m1,x2,y2,vx2,vy2,r2,m2,t,x,y,vx,vy,a,b,c,d,dis,drt,meet;
   scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",&x1,&y1,&vx1,&vy1,&r1,&m1,&x2,&y2,&vx2,&vy2,&r2,&m2,&t);
   x=x2-x1;
   y=y2-y1;
   vx=vx1-vx2;
   vy=vy1-vy2;
   a=vx*vx+vy*vy;
   b=-2*(x*vx+y*vy);
   c=x*x+y*y-(r1+r2)*(r1+r2);
   drt=b*b-4*a*c;
   if (drt>1e-7)
   {
      meet=(-b-sqrt(drt))/2/a;
      if (meet>1e-7&&meet<t-1e-7)
      {
         x1+=meet*vx1;
         y1+=meet*vy1;
         x2+=meet*vx2;
         y2+=meet*vy2;
         t-=meet;
         x=x2-x1;
         y=y2-y1;
         vx=vx2-vx1;
         vy=vy2-vy1;
         dis=x*x+y*y;
         d=2*(vx*x+vy*y)/(dis/m1+dis/m2);
         vx1+=d/m1*x;
         vy1+=d/m1*y;
         vx2-=d/m2*x;
         vy2-=d/m2*y;
      }
   }
   printf("%.3lf %.3lf %.3lf %.3lf\n%.3lf %.3lf %.3lf %.3lf\n",x1+t*vx1,y1+t*vy1,vx1,vy1,x2+t*vx2,y2+t*vy2,vx2,vy2);
   return 0;
}
