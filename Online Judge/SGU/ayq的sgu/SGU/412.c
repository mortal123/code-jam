#include <stdio.h>
#include <math.h>
#define eps 1e-12
#define zero(a) (abb(a)<=eps)
#define abb(a) ((a)>0?(a):(-(a)))
#define pi 3.1415926535897932384626433832795
#define dis(x1,y1,x2,y2) sqrt(((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1)))

struct case1
{
   double d;
   char s;
}q[400001]={0,0};
struct case2
{
   double x,y,d;
}p[100002]={0,0,0},p2[100001]={0,0,0};
struct case3
{
   double x,y;
   char s;
}rec[500001]={0,0,0};
struct case4
{
   double x,y;
};

double D(double x,double y)
{
   if (y>=0&&x>eps)
      return atan(y/x);
   if (x<-eps)
      return pi+atan(y/x);
   if (x>eps)
      return 2*pi-atan(-y/x);
   if (y>eps)
      return pi/2;
   return pi*3/2;
}

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=q[(x+y)>>1];
   if (x>=y)
      return;
   q[(x+y)>>1]=q[x];
   while (i<j)
   {
      while (i<j&&q[j].d>t.d)
         j--;
      if (i<j)
         q[i++]=q[j];
      while (i<j&&q[i].d<t.d)
         i++;
      if (i<j)
         q[j--]=q[i];
   }
   q[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

struct case4 solve(double a,double b,double c,double d,double e,double f,double g,double h)
{
   double k1,b1,k2,b2;
   struct case4 t;
   if (zero(a-c))
   {
      t.x=a;
      t.y=f+(a-e)/(g-e)*(h-f);
   }
   else if (zero(e-g))
   {
      t.x=e;
      t.y=b+(e-a)/(c-a)*(d-b);
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

int main()
{
   long i,j=1,n,m,tmp=0,s=0,tot=0;
   double x1,y1,x2,y2,d1,d2,ans=0;
   struct case4 t;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
   {
      scanf("%lf%lf",&p[i].x,&p[i].y);
      p[i].d=D(p[i].x,p[i].y);
      if (!tmp||p[i].d<p[tmp].d)
         tmp=i;
   }
   for (i=1;i<=n;i++)
      p2[i]=p[(tmp+i-2)%n+1];
   for (i=1;i<=n;i++)
      p[i]=p2[i];
   p[n+1]=p[1];
   p[0]=p[n];
   for (i=1;i<=m;i++)
   {
      scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
      d1=D(x1,y1);
      d2=D(x2,y2);
      if (d1>d2)
      {
         x1=d1;
         d1=d2;
         d2=x1;
      }
      if (d1>=d2-pi)
      {
         q[++s]=(struct case1){d1,-1};
         q[++s]=(struct case1){d2,1};
      }
      else
      {
         q[++s]=(struct case1){0,-1};
         q[++s]=(struct case1){d1,1};
         q[++s]=(struct case1){d2,-1};
         q[++s]=(struct case1){2*pi,1};
      }
   }
   qs(1,s);
   for (i=1;i<=s;i++)
   {
      while (j<=n&&p[j].d<q[i].d-eps)
      {
         rec[++tot].x=p[j].x;
         rec[tot].y=p[j++].y;
      }
      rec[++tot].s=q[i].s;
      t=solve(0,0,100*cos(q[i].d),100*sin(q[i].d),p[j-1].x,p[j-1].y,p[j].x,p[j].y);
      rec[tot].x=t.x;
      rec[tot].y=t.y;
   }
   s=0;
   for (i=1;i<=tot;i++)
   {
      if (s<0)
         ans+=dis(rec[i-1].x,rec[i-1].y,rec[i].x,rec[i].y);
      s+=rec[i].s;
   }
   printf("%.10lf\n",ans);
   return 0;
}
