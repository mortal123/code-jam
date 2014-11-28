#include <math.h>
#include <stdio.h>
#define oo 10000000
#define zero(a) (abb(a)<=1e-7)
#define abb(a) ((a)>0?(a):(-(a)))
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))
#define dis(x1,y1,x2,y2) sqrt(((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1)))

struct case1
{
   double x,y;
}p[10005]={0,0},d[10005]={0,0};
struct case2
{
   double x1,y1,x2,y2;
}l[10005]={0,0,0,0};
long rec[10005]={0};
long n;

struct case1 solve(double a,double b,double c,double d,double e,double f,double g,double h)
{
   struct case1 t;
   double k1,k2,b1,b2;
   if (zero(a-c))
   {
      t.x=a;
      t.y=(h-f)/(g-e)*(a-e)+f;
   }
   else if (zero(e-g))
   {
      t.x=e;
      t.y=(d-b)/(c-a)*(e-a)+b;
   }
   else
   {
      k1=(d-b)/(c-a);
      k2=(h-f)/(g-e);
      b1=b-a*k1;
      b2=f-e*k2;
      t.x=(b2-b1)/(k1-k2);
      t.y=k1*t.x+b1;
   }
   return t;
}

long check(double m)
{
   long i,flag,st=1,en=2;
   double D,dx,dy;
   if (m>0.5&&m<1)
      i=1;
   for (i=1;i<=n;i++)
   {
      D=dis(p[i].x,p[i].y,p[i+1].x,p[i+1].y);
      dx=(p[i].y-p[i+1].y)/D*m;
      dy=(p[i+1].x-p[i].x)/D*m;
      l[i]=(struct case2){p[i].x+dx,p[i].y+dy,p[i+1].x+dx,p[i+1].y+dy};
   }
   rec[1]=1;
   rec[2]=2;
   d[1]=solve(l[1].x1,l[1].y1,l[1].x2,l[1].y2,l[2].x1,l[2].y1,l[2].x2,l[2].y2);
   for (i=3;i<=n;i++)
   {
      dx=l[rec[st]].x1+(l[rec[st]].x1-l[rec[st]].x2)*oo;
      dy=l[rec[st]].y1+(l[rec[st]].y1-l[rec[st]].y2)*oo;
      flag=(cj(dx-l[i].x1,dy-l[i].y1,l[i].x2-l[i].x1,l[i].y2-l[i].y1)>-1e-8);
      dx=l[rec[en]].x2+(l[rec[en]].x2-l[rec[en]].x1)*oo;
      dy=l[rec[en]].y2+(l[rec[en]].y2-l[rec[en]].y1)*oo;
      flag&=(cj(dx-l[i].x1,dy-l[i].y1,l[i].x2-l[i].x1,l[i].y2-l[i].y1)>-1e-8);
      while (st<en&&cj(d[en-1].x-l[i].x1,d[en-1].y-l[i].y1,l[i].x2-l[i].x1,l[i].y2-l[i].y1)>-1e-8)
         en--;
      while (st<en&&cj(d[st].x-l[i].x1,d[st].y-l[i].y1,l[i].x2-l[i].x1,l[i].y2-l[i].y1)>-1e-8)
         st++;
      if (st==en&&flag)
         return 1;
      rec[++en]=i;
      d[en-1]=solve(l[rec[en-1]].x1,l[rec[en-1]].y1,l[rec[en-1]].x2,l[rec[en-1]].y2,l[rec[en]].x1,l[rec[en]].y1,l[rec[en]].x2,l[rec[en]].y2);
   }
   return 0;
}

int main()
{
   long i;
   double m,l=0,r=oo;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%lf%lf",&p[i].x,&p[i].y);
   p[n+1]=p[1];
   while (l<r-1e-6)
   {
      m=(l+r)/2;
      if (check(m))
         r=m;
      else
         l=m;
   }
   printf("%.3lf\n",r);
   return 0;
}
