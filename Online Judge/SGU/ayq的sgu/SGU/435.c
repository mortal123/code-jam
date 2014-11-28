#include <stdio.h>
#include <math.h>
#define eps 1e-8
#define pi 3.14159265359
#define zero(a) (abb(a)<=eps)
#define abb(a) ((a)>0?(a):(-(a)))
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))

struct case1
{
   double x,y,r;
}p[101];
struct case2
{
   double x1,x2,s;
   char flag;
}h[201];
double rec[10201];

void qs(int x,int y)
{
   int i=x,j=y;
   double t=rec[(x+y)>>1];
   if (x>=y)
      return;
   rec[(x+y)>>1]=rec[x];
   while (i<j)
   {
      while (i<j&&rec[j]>t)
         j--;
      if (i<j)
         rec[i++]=rec[j];
      while (i<j&&rec[i]<t)
         i++;
      if (i<j)
         rec[j--]=rec[i];
   }
   rec[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

void qs2(int x,int y)
{
   int i=x,j=y;
   struct case2 t=h[(x+y)>>1];
   if (x>=y)
      return;
   h[(x+y)>>1]=h[x];
   while (i<j)
   {
      while (i<j&&(h[j].x1>t.x1+eps||zero(h[j].x1-t.x1)&&h[j].x2>t.x2+eps||zero(h[j].x1-t.x1)&&zero(h[j].x2-t.x2)&&h[j].flag*h[j].s<t.flag*t.s))
         j--;
      if (i<j)
         h[i++]=h[j];
      while (i<j&&(h[i].x1<t.x1-eps||zero(h[i].x1-t.x1)&&h[i].x2<t.x2-eps||zero(h[i].x1-t.x1)&&zero(h[i].x2-t.x2)&&h[i].flag*h[i].s>t.flag*t.s))
         i++;
      if (i<j)
         h[j--]=h[i];
   }
   h[i]=t;
   qs2(x,i-1);
   qs2(i+1,y);
}

double Du(double x,double y)
{
   if (x>eps&&y>-eps)
      return atan(y/x);
   if (x<-eps)
      return pi+atan(y/x);
   if (x>eps)
      return 2*pi-atan(-y/x);
   if (y>eps)
      return pi/2;
   return pi*3/2;
}

int main()
{
   int i,j,n,s,t,o=0;
   double dis,x0,y0,D,R,A,B,C,drt,ans1=0,ans2;
   scanf("%d",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%lf%lf%lf",&p[i].x,&p[i].y,&p[i].r);
      rec[++o]=p[i].x-p[i].r;
      rec[++o]=p[i].x+p[i].r;
   }
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
      {
         dis=(p[j].x-p[i].x)*(p[j].x-p[i].x)+(p[j].y-p[i].y)*(p[j].y-p[i].y);
         if (dis<(p[i].r+p[j].r)*(p[i].r+p[j].r)-eps&&dis>(p[i].r-p[j].r)*(p[i].r-p[j].r)+eps)
         {
            x0=p[j].x-p[i].x;
            y0=p[j].y-p[i].y;
            R=p[i].r*p[i].r-p[j].r*p[j].r;
            D=x0*x0+y0*y0;
            A=4*D;
            B=-4*x0*(D+R);
            C=(D+R)*(D+R)-4*y0*y0*p[i].r*p[i].r;
            drt=B*B-4*A*C;
            rec[++o]=(-B-sqrt(drt))/2/A+p[i].x;
            rec[++o]=(-B+sqrt(drt))/2/A+p[i].x;
         }
      }
   qs(1,o);
   for (i=2;i<=o;i++)
      if (rec[i]>rec[i-1]+eps)
      {
         s=0;
         for (j=1;j<=n;j++)
            if (p[j].x+p[j].r>rec[i-1]+eps&&p[j].x-p[j].r<rec[i]-eps)
            {
               A=sqrt(p[j].r*p[j].r-(p[j].x-rec[i-1])*(p[j].x-rec[i-1]));
               B=sqrt(p[j].r*p[j].r-(p[j].x-rec[i])*(p[j].x-rec[i]));
               D=Du(rec[i-1]-p[j].x,A)-Du(rec[i]-p[j].x,B);
               C=D*p[j].r*p[j].r/2-cj(rec[i]-p[j].x,B,rec[i-1]-p[j].x,A)/2;
               h[++s]=(struct case2){p[j].y-A,p[j].y-B,C,1};
               h[++s]=(struct case2){p[j].y+A,p[j].y+B,C,-1};
            }
         qs2(1,s);
         t=1;
         for (j=2;j<=s;j++)
         {
            if (t&1)
               ans1+=(h[j].x1-h[j-1].x1+h[j].x2-h[j-1].x2)*(rec[i]-rec[i-1])/2+h[j-1].flag*h[j-1].s-h[j].flag*h[j].s;
            else if (t)
               ans2+=(h[j].x1-h[j-1].x1+h[j].x2-h[j-1].x2)*(rec[i]-rec[i-1])/2+h[j-1].flag*h[j-1].s-h[j].flag*h[j].s;
            t+=h[j].flag;
         }
      }
   printf("%lf %lf\n",ans1,ans2);
   return 0;
}
