#include <stdio.h>
#include <math.h>
#define eps 1e-8
#define pi 3.14159265358
#define zero(a) (abb(a)<eps)
#define abb(a) ((a)>0?(a):(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))

struct case1
{
   double x,y;
}p[50002]={0,0};
struct case2
{
   double x1,y1,x2,y2,d;
   long pos;
}l[50001]={0,0,0,0,0,0};
double ans[50001]={0},s1[50001]={0},s2[50001]={0};

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
   struct case2 t=l[(x+y)>>1];
   if (x>=y)
      return;
   l[(x+y)>>1]=l[x];
   while (i<j)
   {
      while (i<j&&l[j].d>t.d)
         j--;
      if (i<j)
         l[i++]=l[j];
      while (i<j&&l[i].d<t.d)
         i++;
      if (i<j)
         l[j--]=l[i];
   }
   l[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

double dis(long a,long b)
{
   double A,B=1,C;
   if (zero(l[b].x1-l[b].x2))
      return l[b].x1-p[a].x;
   A=(l[b].y1-l[b].y2)/(l[b].x2-l[b].x1);
   C=-l[b].y1-A*l[b].x1;
   A=(A*p[a].x+B*p[a].y+C)/sqrt(A*A+B*B);
   if (cj(p[a].x-l[b].x1,p[a].y-l[b].y1,l[b].x2-l[b].x1,l[b].y2-l[b].y1)>=0)
      return abb(A);
   return -abb(A);
}

struct case1 solve(double a,double b,double c,double d,double e,double f,double g,double h)
{
   double k1,b1,k2,b2;
   struct case1 t;
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
   long i,n,m,left,right,mid,p1=0,p2=0,r1,r2;
   double s=0,tmp,d1,d2;
   struct case1 t1,t2;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%lf%lf",&p[i].x,&p[i].y);
   for (i=2;i<n;i++)
      s+=cj(p[i].x-p[1].x,p[i].y-p[1].y,p[i+1].x-p[1].x,p[i+1].y-p[1].y);
   if (s<0)
   {
      s=-s;
      for (i=2;i<=(n+1)/2;i++)
      {
         t1=p[n-i+2];
         p[n-i+2]=p[i];
         p[i]=t1;
      }
   }
   for (i=3;i<=n;i++)
      s1[i]=s1[i-1]+cj(p[i-1].x-p[1].x,p[i-1].y-p[1].y,p[i].x-p[1].x,p[i].y-p[1].y);
   for (i=n-1;i>1;i--)
      s2[i]=s2[i+1]+cj(p[i].x-p[1].x,p[i].y-p[1].y,p[i+1].x-p[1].x,p[i+1].y-p[1].y);
   scanf("%ld",&m);
   for (i=1;i<=m;i++)
   {
      scanf("%lf%lf%lf%lf",&l[i].x1,&l[i].y1,&l[i].x2,&l[i].y2);
      l[i].d=D(l[i].x1-l[i].x2,l[i].y1-l[i].y2);
      if (l[i].d>=pi)
      {
         l[i].d-=pi;
         tmp=l[i].x2;
         l[i].x2=l[i].x1;
         l[i].x1=tmp;
         tmp=l[i].y2;
         l[i].y2=l[i].y1;
         l[i].y1=tmp;
      }
      l[i].pos=i;
   }
   qs(1,m);
   for (i=1;i<=n;i++)
   {
      tmp=dis(i,1);
      if (!p1||tmp>d1)
      {
         d1=tmp;
         p1=i;
      }
      if (!p2||tmp<d2)
      {
         d2=tmp;
         p2=i;
      }
   }
   for (i=1;i<=m;i++)
   {
      while (dis(p1,i)<dis(p1%n+1,i))
         p1=p1%n+1;
      while (dis(p2,i)>dis(p2%n+1,i))
         p2=p2%n+1;
      d1=dis(p1,i);
      d2=dis(p2,i);
      if (zero(d1)||zero(d2)||(d1>0)==(d2>0))
         ans[l[i].pos]=0;
      else
      {
         left=0;
         right=((p2>=p1)?p2-p1:n-p1+p2)+1;
         while (left<right-1)
         {
            mid=(left+right)>>1;
            if (cj(p[(p1+mid-1)%n+1].x-l[i].x1,p[(p1+mid-1)%n+1].y-l[i].y1,l[i].x2-l[i].x1,l[i].y2-l[i].y1)>=0)
               left=mid;
            else
               right=mid;
         }
         r1=(p1+left-1)%n+1;
         left=0;
         right=((p2<=p1)?p1-p2:n-p2+p1)+1;
         while (left<right-1)
         {
            mid=(left+right)>>1;
            if (cj(p[(p1+n-mid-1)%n+1].x-l[i].x1,p[(p1+n-mid-1)%n+1].y-l[i].y1,l[i].x2-l[i].x1,l[i].y2-l[i].y1)>=0)
               left=mid;
            else
               right=mid;
         }
         r2=(p1+n-left-1)%n+1;
         t1=solve(l[i].x1,l[i].y1,l[i].x2,l[i].y2,p[r1].x,p[r1].y,p[r1%n+1].x,p[r1%n+1].y);
         t2=solve(l[i].x1,l[i].y1,l[i].x2,l[i].y2,p[r2].x,p[r2].y,p[(r2+n-2)%n+1].x,p[(r2+n-2)%n+1].y);
         ans[l[i].pos]=s1[r1]+s2[r2]+cj(p[r1].x-p[1].x,p[r1].y-p[1].y,t1.x-p[1].x,t1.y-p[1].y)+cj(t2.x-p[1].x,t2.y-p[1].y,p[r2].x-p[1].x,p[r2].y-p[1].y)+cj(t1.x-p[1].x,t1.y-p[1].y,t2.x-p[1].x,t2.y-p[1].y);
         if (ans[l[i].pos]>s)
            ans[l[i].pos]=2*s-ans[l[i].pos];
         ans[l[i].pos]=min(ans[l[i].pos],s-ans[l[i].pos])/2;
      }
   }
   for (i=1;i<=m;i++)
      printf("%.10lf\n",ans[i]);
   return 0;
}
