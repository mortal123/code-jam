#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi 3.1415926535897932384626433832795
#define abb(a) ((a)>0?(a):(-(a)))
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))
#define dj(x1,y1,x2,y2) ((x1)*(x2)+(y1)*(y2))
#define dis(x1,y1,x2,y2) sqrt(((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1)))

struct case1
{
   long long x,y;
}p[50001],q[50001],x[50001];
int d[50001],sp[50001],sq[50001];
long double ans1=pi,dis1,ans2=0,dis2;
long long r;

void qs(int x,int y,struct case1 v[])
{
   int i=x,j=y;
   struct case1 t=v[(x+y)>>1];
   if (x>=y)
      return;
   v[(x+y)>>1]=v[x];
   while (i<j)
   {
      while (i<j&&(v[j].x>t.x||v[j].x==t.x&&v[j].y>t.y))
         j--;
      if (i<j)
         v[i++]=v[j];
      while (i<j&&(v[i].x<t.x||v[i].x==t.x&&v[i].y<t.y))
         i++;
      if (i<j)
         v[j--]=v[i];
   }
   v[i]=t;
   qs(x,i-1,v);
   qs(i+1,y,v);
}

void renew1(long long x0,long long y0,long long x1,long long y1,long long x2,long long y2)
{
   long double dist,tmp;
   long long x3=x0-y0,y3=y0+x0;
   dist=cj(x1-x0,y1-y0,-x0,-y0)/dis(x0,y0,x1,y1);
   tmp=acos(dist/r);
   if (tmp<ans1)
   {
      ans1=tmp;
      dis1=abb(dist);
   }
   dist=cj(x2-x0,y2-y0,-x0,-y0)/dis(x0,y0,x2,y2);
   tmp=acos(dist/r);
   if (tmp<ans1)
   {
      ans1=tmp;
      dis1=abb(dist);
   }
   if (cj(x3-x0,y3-y0,x1-x0,y1-y0)>0&&cj(x3-x0,y3-y0,x2-x0,y2-y0)<0)
   {
      dist=cj(x3-x0,y3-y0,-x0,-y0)/dis(x0,y0,x3,y3);
      tmp=acos(dist/r);
      if (tmp<ans1)
      {
         ans1=tmp;
         dis1=abb(dist);
      }
   }
}

void renew2(long long x0,long long y0,long long x1,long long y1,long long x2,long long y2)
{
   long double dist,tmp;
   long long x3=x0-y0,y3=y0+x0;
   dist=cj(x1-x0,y1-y0,-x0,-y0)/dis(x0,y0,x1,y1);
   tmp=pi-acos(dist/r);
   if (tmp>ans2)
   {
      ans2=tmp;
      dis2=abb(dist);
   }
   dist=cj(x2-x0,y2-y0,-x0,-y0)/dis(x0,y0,x2,y2);
   tmp=pi-acos(dist/r);
   if (tmp>ans2)
   {
      ans2=tmp;
      dis2=abb(dist);
   }
   if (cj(x3-x0,y3-y0,x1-x0,y1-y0)>0&&cj(x3-x0,y3-y0,x2-x0,y2-y0)<0)
   {
      dist=cj(x3-x0,y3-y0,-x0,-y0)/dis(x0,y0,x3,y3);
      tmp=pi-acos(dist/r);
      if (tmp>ans2)
      {
         ans2=tmp;
         dis2=abb(dist);
      }
   }
}

int main()
{
   int i,j,n,m,f1,f2,f3,t,t1,t2,tp=0,tq=0;
   long long x1,y1,x2,y2,x3,y3,x4,y4;
   scanf("%I64d%d",&r,&n);
   for (i=1;i<=n;i++)
      scanf("%I64d%I64d",&p[i].x,&p[i].y);
   qs(1,n,p);
   d[t=1]=1;
   for (i=2;i<n;i++)
      if (cj(p[n].x-p[d[t]].x,p[n].y-p[d[t]].y,p[i].x-p[d[t]].x,p[i].y-p[d[t]].y)>0)
      {
         while (t>1&&cj(p[d[t]].x-p[d[t-1]].x,p[d[t]].y-p[d[t-1]].y,p[i].x-p[d[t-1]].x,p[i].y-p[d[t-1]].y)>0)
            t--;
         d[++t]=i;
      }
   for (i=1;i<=t;i++)
      sp[++tp]=d[i];
   if (n>1)
   {
      d[t=1]=n;
      for (i=n-1;i>1;i--)
         if (cj(p[1].x-p[d[t]].x,p[1].y-p[d[t]].y,p[i].x-p[d[t]].x,p[i].y-p[d[t]].y)>0)
         {
            while (t>1&&cj(p[d[t]].x-p[d[t-1]].x,p[d[t]].y-p[d[t-1]].y,p[i].x-p[d[t-1]].x,p[i].y-p[d[t-1]].y)>0)
               t--;
            d[++t]=i;
         }
      for (i=1;i<=t;i++)
         sp[++tp]=d[i];
   }
   for (i=1;i<=n;i++)
      x[i]=p[i];
   for (i=0;i<tp;i++)
      p[i]=x[sp[i+1]];
   n=tp;
   scanf("%d",&m);
   for (i=1;i<=m;i++)
      scanf("%I64d%I64d",&q[i].x,&q[i].y);
   qs(1,m,q);
   d[t=1]=1;
   for (i=2;i<m;i++)
      if (cj(q[m].x-q[d[t]].x,q[m].y-q[d[t]].y,q[i].x-q[d[t]].x,q[i].y-q[d[t]].y)>0)
      {
         while (t>1&&cj(q[d[t]].x-q[d[t-1]].x,q[d[t]].y-q[d[t-1]].y,q[i].x-q[d[t-1]].x,q[i].y-q[d[t-1]].y)>=0)
            t--;
         d[++t]=i;
      }
   for (i=1;i<=t;i++)
      sq[++tq]=d[i];
   if (m>1)
   {
      d[t=1]=m;
      for (i=m-1;i>1;i--)
         if (cj(q[1].x-q[d[t]].x,q[1].y-q[d[t]].y,q[i].x-q[d[t]].x,q[i].y-q[d[t]].y)>0)
         {
            while (t>1&&cj(q[d[t]].x-q[d[t-1]].x,q[d[t]].y-q[d[t-1]].y,q[i].x-q[d[t-1]].x,q[i].y-q[d[t-1]].y)>=0)
               t--;
            d[++t]=i;
         }
      for (i=1;i<=t;i++)
         sq[++tq]=d[i];
   }
   for (i=1;i<=m;i++)
      x[i]=q[i];
   for (i=0;i<tq;i++)
      q[i]=x[sq[i+1]];
   m=tq;
   for (i=0;i<m;i++)
      if (!cj(q[i].x-p[0].x,q[i].y-p[0].y,q[(i+1)%m].x-p[0].x,q[(i+1)%m].y-p[0].y)&&dj(q[i].x-p[0].x,q[i].y-p[0].y,q[(i+1)%m].x-p[0].x,q[(i+1)%m].y-p[0].y)<0)
      {
         f1=f2=1;
         for (j=0;j<m;j++)
            if (cj(q[i].x-p[0].x,q[i].y-p[0].y,q[j].x-p[0].x,q[j].y-p[0].y))
               f2=0;
         for (j=0;j<n;j++)
            if (cj(p[j].x-p[0].x,p[j].y-p[0].y,q[i].x-p[0].x,q[i].y-p[0].y)>0)
               f2=0;
            else if (cj(p[j].x-p[0].x,p[j].y-p[0].y,q[i].x-p[0].x,q[i].y-p[0].y)<0)
               f1=0;
         if (f1)
            renew1(p[0].x,p[0].y,q[i].x,q[i].y,q[i].x,q[i].y);
         if (f2)
            renew1(p[0].x,p[0].y,q[(i+1)%m].x,q[(i+1)%m].y,q[(i+1)%m].x,q[(i+1)%m].y);
         goto out1;
      }
   t1=t2=0;
   for (i=0;i<n;i++)
   {
      while (cj(q[(t1+1)%m].x-p[i].x,q[(t1+1)%m].y-p[i].y,q[t1].x-p[i].x,q[t1].y-p[i].y)>0)
         t1=(t1+1)%m;
      while (cj(q[(t1+m-1)%m].x-p[i].x,q[(t1+m-1)%m].y-p[i].y,q[t1].x-p[i].x,q[t1].y-p[i].y)>0)
         t1=(t1+m-1)%m;
      while (cj(q[(t2+1)%m].x-p[i].x,q[(t2+1)%m].y-p[i].y,q[t2].x-p[i].x,q[t2].y-p[i].y)<0)
         t2=(t2+1)%m;
      while (cj(q[(t2+m-1)%m].x-p[i].x,q[(t2+m-1)%m].y-p[i].y,q[t2].x-p[i].x,q[t2].y-p[i].y)<0)
         t2=(t2+m-1)%m;
      x3=q[t1].x;
      y3=q[t1].y;
      x4=2*p[i].x-q[t2].x;
      y4=2*p[i].y-q[t2].y;
      if (n==1)
         renew1(p[i].x,p[i].y,x3,y3,x4,y4);
      else
      {
         x1=2*p[i].x-p[(i+n-1)%n].x;
         y1=2*p[i].y-p[(i+n-1)%n].y;
         x2=p[(i+1)%n].x;
         y2=p[(i+1)%n].y;
      }
      f1=(cj(x3-p[i].x,y3-p[i].y,x1-p[i].x,y1-p[i].y)>=0&&cj(x3-p[i].x,y3-p[i].y,x2-p[i].x,y2-p[i].y)<=0);
      f2=(cj(x4-p[i].x,y4-p[i].y,x1-p[i].x,y1-p[i].y)>=0&&cj(x4-p[i].x,y4-p[i].y,x2-p[i].x,y2-p[i].y)<=0);
      f3=(cj(x1-p[i].x,y1-p[i].y,x3-p[i].x,y3-p[i].y)>=0&&cj(x1-p[i].x,y1-p[i].y,x4-p[i].x,y4-p[i].y)<=0);
      if (f1&&f2)
      {
         if (!cj(x1-p[i].x,y1-p[i].y,x4-p[i].x,y4-p[i].y)&&dj(x1-p[i].x,y1-p[i].y,x4-p[i].x,y4-p[i].y)>0&&!cj(x2-p[i].x,y2-p[i].y,x3-p[i].x,y3-p[i].y)&&dj(x2-p[i].x,y2-p[i].y,x3-p[i].x,y3-p[i].y)>0)
         {
            renew1(p[i].x,p[i].y,x1,y1,x1,y1);
            renew1(p[i].x,p[i].y,x2,y2,x2,y2);
         }
         else
            renew1(p[i].x,p[i].y,x3,y3,x4,y4);
      }
      else if (f1)
         renew1(p[i].x,p[i].y,x3,y3,x2,y2);
      else if (f2)
         renew1(p[i].x,p[i].y,x1,y1,x4,y4);
      else if (f3)
         renew1(p[i].x,p[i].y,x1,y1,x2,y2);
   }
   out1:
   for (i=0;i<n;i++)
      if (!cj(p[i].x-q[0].x,p[i].y-q[0].y,p[(i+1)%n].x-q[0].x,p[(i+1)%n].y-q[0].y)&&dj(p[i].x-q[0].x,p[i].y-q[0].y,p[(i+1)%n].x-q[0].x,p[(i+1)%n].y-q[0].y)<0)
      {
         f1=f2=1;
         for (j=0;j<n;j++)
            if (cj(p[i].x-q[0].x,p[i].y-q[0].y,p[j].x-q[0].x,p[j].y-q[0].y))
               f2=0;
         for (j=0;j<m;j++)
            if (cj(q[j].x-q[0].x,q[j].y-q[0].y,p[i].x-q[0].x,p[i].y-q[0].y)>0)
               f2=0;
            else if (cj(q[j].x-q[0].x,q[j].y-q[0].y,p[i].x-q[0].x,p[i].y-q[0].y)<0)
               f1=0;
         if (f1)
            renew2(q[0].x,q[0].y,p[i].x,p[i].y,p[i].x,p[i].y);
         if (f2)
            renew2(q[0].x,q[0].y,p[(i+1)%n].x,p[(i+1)%n].y,p[(i+1)%n].x,p[(i+1)%n].y);
         goto out2;
      }
   t1=t2=0;
   for (i=0;i<m;i++)
   {
      while (cj(p[(t1+1)%n].x-q[i].x,p[(t1+1)%n].y-q[i].y,p[t1].x-q[i].x,p[t1].y-q[i].y)>0)
         t1=(t1+1)%n;
      while (cj(p[(t1+n-1)%n].x-q[i].x,p[(t1+n-1)%n].y-q[i].y,p[t1].x-q[i].x,p[t1].y-q[i].y)>0)
         t1=(t1+n-1)%n;
      while (cj(p[(t2+1)%n].x-q[i].x,p[(t2+1)%n].y-q[i].y,p[t2].x-q[i].x,p[t2].y-q[i].y)<0)
         t2=(t2+1)%n;
      while (cj(p[(t2+n-1)%n].x-q[i].x,p[(t2+n-1)%n].y-q[i].y,p[t2].x-q[i].x,p[t2].y-q[i].y)<0)
         t2=(t2+n-1)%n;
      x3=p[t1].x;
      y3=p[t1].y;
      x4=2*q[i].x-p[t2].x;
      y4=2*q[i].y-p[t2].y;
      if (m==1)
         renew2(q[i].x,q[i].y,x3,y3,x4,y4);
      else
      {
         x1=2*q[i].x-q[(i+m-1)%m].x;
         y1=2*q[i].y-q[(i+m-1)%m].y;
         x2=q[(i+1)%m].x;
         y2=q[(i+1)%m].y;
      }
      f1=(cj(x3-q[i].x,y3-q[i].y,x1-q[i].x,y1-q[i].y)>=0&&cj(x3-q[i].x,y3-q[i].y,x2-q[i].x,y2-q[i].y)<=0);
      f2=(cj(x4-q[i].x,y4-q[i].y,x1-q[i].x,y1-q[i].y)>=0&&cj(x4-q[i].x,y4-q[i].y,x2-q[i].x,y2-q[i].y)<=0);
      f3=(cj(x1-q[i].x,y1-q[i].y,x3-q[i].x,y3-q[i].y)>=0&&cj(x1-q[i].x,y1-q[i].y,x4-q[i].x,y4-q[i].y)<=0);
      if (f1&&f2)
      {
         if (!cj(x1-q[i].x,y1-q[i].y,x4-q[i].x,y4-q[i].y)&&dj(x1-q[i].x,y1-q[i].y,x4-q[i].x,y4-q[i].y)>0&&!cj(x2-q[i].x,y2-q[i].y,x3-q[i].x,y3-q[i].y)&&dj(x2-q[i].x,y2-q[i].y,x3-q[i].x,y3-q[i].y)>0)
         {
            renew2(q[i].x,q[i].y,x1,y1,x1,y1);
            renew2(q[i].x,q[i].y,x2,y2,x2,y2);
         }
         else
            renew2(q[i].x,q[i].y,x3,y3,x4,y4);
      }
      else if (f1)
         renew2(q[i].x,q[i].y,x3,y3,x2,y2);
      else if (f2)
         renew2(q[i].x,q[i].y,x1,y1,x4,y4);
      else if (f3)
         renew2(q[i].x,q[i].y,x1,y1,x2,y2);
   }
   out2:
   ans1=ans1*r*r+(1-2*(ans1*2<pi))*dis1*sqrt(r*r-dis1*dis1);
   printf("%I64d.",(long long)ans1);
   ans1-=(long long)ans1;
   for (i=1;i<=8;i++)
   {
      ans1*=10;
      printf("%I64d",(long long)ans1%10);
   }
   putchar(' ');
   ans2=ans2*r*r+(1-2*(ans2*2<pi))*dis2*sqrt(r*r-dis2*dis2);
   printf("%I64d.",(long long)ans2);
   ans2-=(long long)ans2;
   for (i=1;i<=8;i++)
   {
      ans2*=10;
      printf("%I64d",(long long)ans2%10);
   }
   puts("");
   return 0;
}
