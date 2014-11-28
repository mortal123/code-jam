#include <stdio.h>
#include <math.h>
#define abb(a) ((a)>0?(a):(-(a)))
#define zero(a) (abb(a)<=1e-7)
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))
#define dis(x1,y1,x2,y2) sqrt(((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1)))

struct case1
{
   double x,y;
}p[402]={{0,0}};
long n;

long cross(double a,double b,double c,double d,double e,double f,double g,double h)
{
   double minx1=min(a,c),maxx1=max(a,c),miny1=min(b,d),maxy1=max(b,d),minx2=min(e,g),maxx2=max(e,g),miny2=min(f,h),maxy2=max(f,h);
   if (minx1>maxx2+1e-8||minx2>maxx1+1e-8||miny1>maxy2+1e-8||miny2>maxy1+1e-8)
      return 0;
   if (cj(e-a,f-b,c-a,d-b)*cj(g-a,h-b,c-a,d-b)>1e-8)
      return 0;
   if (cj(a-e,b-f,g-e,h-f)*cj(c-e,d-f,g-e,h-f)>1e-8)
      return 0;
   return 1;
}

struct case1 solve(double a,double b,double c,double d,double e,double f,double g,double h)
{
   struct case1 t;
   double k1,b1,k2,b2;
   if (zero(a-c))
   {
      t.x=a;
      t.y=h+(f-h)*(a-g)/(e-g);
   }
   else if (zero(e-g))
   {
      t.x=e;
      t.y=d+(b-d)*(e-c)/(a-c);
   }
   else
   {
      k1=(d-b)/(c-a);
      k2=(h-f)/(g-e);
      b1=(b*c-a*d)/(c-a);
      b2=(f*g-e*h)/(g-e);
      t.x=(b2-b1)/(k1-k2);
      t.y=k1*t.x+b1;
   }
   return t;
}

long in(double x,double y)
{
   long i,s=0;
   for (i=1;i<=n;i++)
      if (zero(cj(p[i+1].x-p[i].x,p[i+1].y-p[i].y,x-p[i].x,y-p[i].y)))
         return 0;
   for (i=1;i<=n;i++)
      s+=cross(p[i].x,p[i].y,p[i+1].x,p[i+1].y,x,y,73826.321,85946.218);
   return s&1;
}

int main()
{
   long i,j,q,f1,f2;
   struct case1 t,t2;
   double x1,y1,x2,y2,k;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%lf%lf",&p[i].x,&p[i].y);
   for (i=2;i<n;i++)
      for (j=i+1;j<=n;j++)
         if (cj(p[j].x-p[1].x,p[j].y-p[1].y,p[i].x-p[1].x,p[i].y-p[1].y)<0)
         {
            t=p[i];
            p[i]=p[j];
            p[j]=t;
         }
   p[n+1]=p[1];
   scanf("%ld",&q);
   while (q--)
   {
      scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
      for (i=1;i<=n;i++)
         if (zero((p[i+1].x-p[i].x)*(y2-y1)-(p[i+1].y-p[i].y)*(x2-x1)))
            if (zero(p[i+1].x-p[i].x))
            {
               if (zero(p[i].x-x1))
                  break;
            }
            else
            {
               k=(p[i+1].y-p[i].y)/(p[i+1].x-p[i].x);
               if (zero((p[i].y-k*p[i].x)-(y1-k*x1)))
                  break;
            }
      if (i<=n)
      {
         printf("0.000000\n");
         continue;
      }
      f1=in(x1,y1);
      f2=in(x2,y2);
      if (f1&&f2)
         printf("%lf\n",dis(x1,y1,x2,y2));
      else if (f1)
      {
         for (i=1;!cross(x1,y1,x2,y2,p[i].x,p[i].y,p[i+1].x,p[i+1].y);i++);
         t=solve(x1,y1,x2,y2,p[i].x,p[i].y,p[i+1].x,p[i+1].y);
         printf("%lf\n",dis(t.x,t.y,x1,y1));
      }
      else if (f2)
      {
         for (i=1;!cross(x1,y1,x2,y2,p[i].x,p[i].y,p[i+1].x,p[i+1].y);i++);
         t=solve(x1,y1,x2,y2,p[i].x,p[i].y,p[i+1].x,p[i+1].y);
         printf("%lf\n",dis(t.x,t.y,x2,y2));
      }
      else
      {
         for (i=1;!cross(x1,y1,x2,y2,p[i].x,p[i].y,p[i+1].x,p[i+1].y)&&i<=n;i++);
         if (i>n)
            printf("0.000000\n");
         else
         {
            t=solve(x1,y1,x2,y2,p[i].x,p[i].y,p[i+1].x,p[i+1].y);
            while (1)
            {
               for (i++;!cross(x1,y1,x2,y2,p[i].x,p[i].y,p[i+1].x,p[i+1].y)&&i<=n;i++);
               if (i>n)
               {
                  t2=t;
                  break;
               }
               t2=solve(x1,y1,x2,y2,p[i].x,p[i].y,p[i+1].x,p[i+1].y);
               if (!zero(t.x-t2.x)||!zero(t.y-t2.y))
                  break;
            }
            printf("%lf\n",dis(t.x,t.y,t2.x,t2.y));
         }
      }
   }
   return 0;
}
