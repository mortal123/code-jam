#include<stdio.h>
#include<math.h>
#define pi 3.14159265358979323846
#define dis(x1,y1,x2,y2) sqrt(((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1)))

double D(double x,double y)
{
   if (x>0&&y>=0)
      return atan(y/x);
   if (x<0&&y>=0)
      return pi-atan(-y/x);
   if (x<0&&y<0)
      return pi+atan(y/x);
   if (x>0&&y<0)
      return 2*pi-atan(-y/x);
   if (y>0)
      return pi/2;
   return pi/2*3;
}

int main()
{
   long i,n,a,b;
   double x1,y1,x2,y2,x,y,r,l,c,d;
   scanf("%ld%ld%ld%lf%lf%lf%lf",&n,&a,&b,&x1,&y1,&x2,&y2);
   l=dis(x1,y1,x2,y2);
   c=(pi-2*pi*(b-a)/n)/2;
   r=l/2/cos(c);
   x=((y1-y2)*(y1*x2-x1*y2-r*l*sin(c))+(x2-x1)*(x1*x2+y1*y2-x1*x1-y1*y1+r*l*cos(c)))/((y1-y2)*(y1-y2)+(x2-x1)*(x2-x1));
   y=((x2-x1)*(y1*x2-x1*y2-r*l*sin(c))-(y1-y2)*(x1*x2+y1*y2-x1*x1-y1*y1+r*l*cos(c)))/((y1-y2)*(y1-y2)+(x2-x1)*(x2-x1));
   d=D(x1-x,y1-y)+2*pi*(a-1)/n;
   for (i=1;i<=n;i++)
      printf("%.6lf %.6lf\n",x+fabs(r)*cos(d-2*pi*(i-1)/n)+0.00000001,y+fabs(r)*sin(d-2*pi*(i-1)/n)+0.00000001);
   return 0;
}
