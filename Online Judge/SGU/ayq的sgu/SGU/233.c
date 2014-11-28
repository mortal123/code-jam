#include <stdio.h>
#include <math.h>
#define pi 3.14159265359
#define abb(a) ((a)>0?(a):(-(a)))
#define zero(a) (abb(a)<=1e-8)
#define max(a,b) ((a)>(b)?(a):(b))
#define dis(x1,y1,x2,y2) sqrt(((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1)))

double D(double x,double y)
{
   if (x>1e-8&&y>=-1e-8)
      return atan(y/x);
   if (x<-1e-8)
      return pi+atan(y/x);
   if (x>1e-8)
      return 2*pi-atan(-y/x);
   if (y>0)
      return pi/2;
   return pi*3/2;
}

int main()
{
   long t;
   double x,y,r,x1,y1,x2,y2,x3,y3,h,a,c,p,q,A,B,C,drt,pc,rx,ry,dis;
   scanf("%ld",&t);
   while (t--)
   {
      scanf("%lf%lf%lf%lf%lf%lf%lf",&x,&y,&r,&x1,&y1,&x2,&y2);
      if (zero((x1+x2)/2-x)&&zero((y1+y2)/2-y))
         a=D((x1-x2)/2,(y1-y2)/2)+pi/2;
      else
      {
         h=dis(x1,y1,x2,y2)/2;
         c=dis((x1+x2)/2,(y1+y2)/2,x,y);
         a=D((x1-x2)/2,(y1-y2)/2)-D(x-(x1+x2)/2,y-(y1+y2)/2);
         a=cos(a+pi/2);
         p=2*c*a;
         q=r*r+h*h-c*c;
         A=p*p-4*r*r;
         B=2*p*q;
         C=q*q-4*r*r*h*h;
         drt=max(B*B-4*A*C,1e-30);
         pc=(-B+sqrt(drt))/2/A;
         a=D((x1-x2)/2,(y1-y2)/2);
         rx=(x1+x2)/2+pc*cos(a+pi/2);
         ry=(y1+y2)/2+pc*sin(a+pi/2);
         c=dis(x,y,rx,ry);
         if (!zero(c-r+sqrt(pc*pc+h*h)))
         {
            rx=(x1+x2)/2+pc*cos(a-pi/2);
            ry=(y1+y2)/2+pc*sin(a-pi/2);
         }
         dis=dis(x1,y1,rx,ry);
         pc=(-B-sqrt(drt))/2/A;
         a=D((x1-x2)/2,(y1-y2)/2);
         x3=(x1+x2)/2+pc*cos(a+pi/2);
         y3=(y1+y2)/2+pc*sin(a+pi/2);
         c=dis(x,y,x3,y3);
         if (!zero(c-r+sqrt(pc*pc+h*h)))
         {
            x3=(x1+x2)/2+pc*cos(a-pi/2);
            y3=(y1+y2)/2+pc*sin(a-pi/2);
         }
         if (dis(x1,y1,x3,y3)<dis)
         {
            rx=x3;
            ry=y3;
         }
         a=D(rx-x,ry-y);
      }
      printf("%.6lf %.6lf\n",x+r*cos(a)+1e-9,y+r*sin(a)+1e-9);
   }
   return 0;
}
