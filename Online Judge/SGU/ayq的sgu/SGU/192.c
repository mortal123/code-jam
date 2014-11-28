#include <stdio.h>
#define abb(a) ((a)>0?(a):(-(a)))
#define zero(a) (abb(a)<=1e-7)
#define in(x) ((x)>x1&&(x)<x2)
#define F(x) ((x)*k+b)
#define F2(x) ((x)*p[now].k+p[now].b)

struct case1
{
   double b,k,x1,x2;
   char c;
}p[301]={{0,0,0,0},{'\0'}};
double ans[3]={0};

void cut(double k,double b,double x1,double x2,long now,long t)
{
   double px;
   if (!now)
   {
      if (p[t].c=='R')
         ans[0]+=x2-x1;
      else if (p[t].c=='G')
         ans[1]+=x2-x1;
      else
         ans[2]+=x2-x1;
   }
   else
   {
      if (t==now)
      {
         cut(k,b,x1,x2,now-1,t);
         return;
      }
      if (zero(k-p[now].k))
         goto loop;
      px=(p[now].b-b)/(k-p[now].k);
      if (px<x1-1e-8||px>x2+1e-8||px<p[now].x1-1e-8||px>p[now].x2+1e-8)
         goto loop;
      else if (p[now].k<k)
      {
         cut(k,b,x1,px,now-1,t);
         if (p[now].x2<x2-1e-8)
            cut(k,b,p[now].x2,x2,now-1,t);
      }
      else
      {
         cut(k,b,px,x2,now-1,t);
         if (p[now].x1>x1+1e-8)
            cut(k,b,x1,p[now].x1,now-1,t);
      }
      return;
      loop:
      if (in(p[now].x1)&&in(p[now].x2))
      {
         if (F(p[now].x1)<F2(p[now].x1))
            cut(k,b,x1,x2,now-1,t);
         else
         {
            cut(k,b,x1,p[now].x1,now-1,t);
            cut(k,b,p[now].x2,x2,now-1,t);
         }
      }
      else if (in(p[now].x1))
      {
         if (F(p[now].x1)<F2(p[now].x1))
            cut(k,b,x1,x2,now-1,t);
         else
            cut(k,b,x1,p[now].x1,now-1,t);
      }
      else if (in(p[now].x2))
      {
         if (F(p[now].x2)<F2(p[now].x2))
            cut(k,b,x1,x2,now-1,t);
         else
            cut(k,b,p[now].x2,x2,now-1,t);
      }
      else if (p[now].x1>=x2||p[now].x2<=x1||F((x1+x2)/2)<F2((x1+x2)/2))
         cut(k,b,x1,x2,now-1,t);
   }
}

int main()
{
   double t,y1,y2;
   long i,n;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%lf%lf%lf%lf %c",&p[i].x1,&y1,&p[i].x2,&y2,&p[i].c);
      if (zero(p[i].x1-p[i].x2))
      {
         n--;
         i--;
         continue;
      }
      p[i].k=(y2-y1)/(p[i].x2-p[i].x1);
      p[i].b=y1-p[i].x1*p[i].k;
      if (p[i].x2<p[i].x1)
      {
         t=p[i].x1;
         p[i].x1=p[i].x2;
         p[i].x2=t;
      }
   }
   for (i=1;i<=n;i++)
      cut(p[i].k,p[i].b,p[i].x1,p[i].x2,n,i);
   printf("R %lf\nG %lf\nB %lf\n",ans[0],ans[1],ans[2]);
   return 0;
}
