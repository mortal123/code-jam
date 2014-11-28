#include <stdio.h>
#include <math.h>
#define pi 3.14159265359
#define eps 1e-3
#define eps2 1e-10
#define abb(a) ((a)>0?(a):(-(a)))
#define zero(a) (abb(a)<=eps)
#define zero2(a) (abb(a)<=eps2)
#define max(a,b) ((a)>(b)?(a):(b))
#define dis(x1,y1,x2,y2) sqrt(((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1)))
#define in(x,a,b) ((a)<(b)&&(x)>=a-eps2&&(x)<=b+eps2||(a)>(b)&&((x)>=a-eps2||(x)<=b+eps2))

struct case1
{
   double x,y,r,st,en;
}p[51]={{0,0,0,0,0}};
struct case2
{
   double x,y;
}rec[5001]={{0,0}};
long tot=0;

double D(double x,double y)
{
   if (x>eps2&&y>=0)
      return atan(y/x);
   if (x<-eps2)
      return pi+atan(y/x);
   if (x>eps2)
      return 2*pi-atan(-y/x);
   if (y>0)
      return pi/2;
   return pi*3/2;
}

void set(double x,double y)
{
   long i;
   for (i=1;i<=tot;i++)
      if (zero(rec[i].x-x)&&zero(rec[i].y-y))
         return;
   rec[++tot]=(struct case2){x,y};
}

long cross(double x,double y,double r,double st1,double en1,double st2,double en2)
{
   if (zero2(st1-en2))
      set(x+r*cos(st1),y+r*sin(st1));
   if (zero2(en1-st2))
      set(x+r*cos(en1),y+r*sin(en1));
   if (st1<en1&&st2<en2)
      return en2>st1+eps2&&en1>st2+eps2;
   if (st1>en1&&st2>en2)
      return 1;
   return en2>st1+eps2||en1>st2+eps2;
}

void C(double *x,double *y,double d)
{
   double t=D(*x,*y)+d,dis=dis(*x,*y,0,0);
   *x=dis*cos(t);
   *y=dis*sin(t);
}

int main()
{
   long i,j,n;
   struct case2 t;
   double a,b,c,d,x,y,r,x1,y1,x2,y2,x3,y3,k1,b1,k2,b2,tmp,drt,turn=2.398476;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&x3,&y3);
      C(&x1,&y1,turn);
      C(&x2,&y2,turn);
      C(&x3,&y3,turn);
      if (zero(y2-y1))
      {
         p[i].x=(x2*x2-x1*x1+y2*y2-y1*y1)/2/(x2-x1);
         p[i].y=(x3*x3-x1*x1+y3*y3-y1*y1-2*(x3-x1)*p[i].x)/2/(y3-y1);
      }
      else if (zero(y3-y1))
      {
         p[i].x=(x3*x3-x1*x1+y3*y3-y1*y1)/2/(x3-x1);
         p[i].y=(x2*x2-x1*x1+y2*y2-y1*y1-2*(x2-x1)*p[i].x)/2/(y2-y1);
      }
      else
      {
         k1=(x2-x1)/(y1-y2);
         b1=(x2*x2-x1*x1+y2*y2-y1*y1)/2/(y2-y1);
         k2=(x3-x1)/(y1-y3);
         b2=(x3*x3-x1*x1+y3*y3-y1*y1)/2/(y3-y1);
         p[i].x=(b2-b1)/(k1-k2);
         p[i].y=k1*p[i].x+b1;
      }
      p[i].r=dis(p[i].x,p[i].y,x1,y1);
      a=D(x1-p[i].x,y1-p[i].y);
      b=D(x2-p[i].x,y2-p[i].y);
      c=D(x3-p[i].x,y3-p[i].y);
      if (a>b)
      {
         d=a;
         a=b;
         b=d;
      }
      if (c>=a&&c<=b)
      {
         p[i].st=a;
         p[i].en=b;
      }
      else
      {
         p[i].st=b;
         p[i].en=a;
      }
   }
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         if (dis(p[i].x,p[i].y,p[j].x,p[j].y)<=p[i].r+p[j].r+eps&&dis(p[i].x,p[i].y,p[j].x,p[j].y)>=abb(p[i].r-p[j].r)-eps)
         {
            x=p[j].x-p[i].x;
            y=p[j].y-p[i].y;
            if (zero(x)&&zero(y))
            {
               if (zero(p[i].r-p[j].r)&&cross(p[i].x,p[i].y,p[i].r,p[i].st,p[i].en,p[j].st,p[j].en))
               {
                  printf("Infinity\n");
                  goto end;
               }
            }
            else
            {
               d=x*x+y*y;
               r=p[i].r*p[i].r-p[j].r*p[j].r;
               a=4*d;
               b=-4*x*(d+r);
               c=(d+r)*(d+r)-4*y*y*p[i].r*p[i].r;
               drt=max(b*b-4*a*c,1e-30);
               x1=(-b-sqrt(drt))/2/a;
               if (zero(y))
               {
                  tmp=max(p[i].r*p[i].r-x1*x1,1e-30);
                  y1=sqrt(tmp)+p[i].y;
               }
               else
                  y1=(d+r-2*x*x1)/2/y+p[i].y;
               x1+=p[i].x;
               k1=D(x1-p[i].x,y1-p[i].y);
               k2=D(x1-p[j].x,y1-p[j].y);
               if (in(k1,p[i].st,p[i].en)&&in(k2,p[j].st,p[j].en))
                  set(x1,y1);
               x1=(-b+sqrt(drt))/2/a;
               if (zero(y))
               {
                  tmp=max(p[i].r*p[i].r-x1*x1,1e-30);
                  y1=-sqrt(tmp)+p[i].y;
               }
               else
                  y1=(d+r-2*x*x1)/2/y+p[i].y;
               x1+=p[i].x;
               k1=D(x1-p[i].x,y1-p[i].y);
               k2=D(x1-p[j].x,y1-p[j].y);
               if (in(k1,p[i].st,p[i].en)&&in(k2,p[j].st,p[j].en))
                  set(x1,y1);
            }
         }
   printf("%ld\n",tot);
   for (i=1;i<=tot;i++)
      C(&rec[i].x,&rec[i].y,-turn);
   for (i=1;i<tot;i++)
      for (j=i+1;j<=tot;j++)
         if (rec[j].x<rec[i].x-eps||zero(rec[j].x-rec[i].x)&&rec[j].y<rec[i].y)
         {
            t=rec[i];
            rec[i]=rec[j];
            rec[j]=t;
         }
   for (i=1;i<=tot;i++)
      printf("%.3lf %.3lf\n",rec[i].x,rec[i].y);
   end:
   return 0;
}
