#include <stdio.h>
#include <math.h>
#define zero(a) (abb(a)<eps)
#define abb(a) ((a)>0?(a):(-(a)))
#define max(a,b) ((a)>(b)?(a):(b))
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))

struct case1
{
   double x,y,r;
}p[100001];
struct case2
{
   double x1,y1,x2,y2;
};
struct case3
{
   double x,y;
};
double eps;

void qs(int x,int y)
{
   int i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&(p[j].x>t.x||zero(p[j].x-t.x)&&p[j].y>t.y||zero(p[j].x-t.x)&&zero(p[j].y-t.y)&&p[j].r>t.r))
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&(p[i].x<t.x||zero(p[i].x-t.x)&&p[i].y<t.y||zero(p[i].x-t.x)&&zero(p[i].y-t.y)&&p[i].r<t.r))
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

struct case3 solve2(double a,double b,double c,double d,double e,double f,double g,double h)
{
   struct case3 t;
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

struct case2 solve1(int x)
{
   double dis=sqrt((p[x].x-p[1].x)*(p[x].x-p[1].x)+(p[x].y-p[1].y)*(p[x].y-p[1].y)),pos=(p[1].r*p[1].r-p[x].r*p[x].r+dis*dis)/2/dis;
   struct case2 tmp;
   tmp.x1=p[1].x+(p[x].x-p[1].x)*pos/dis;
   tmp.y1=p[1].y+(p[x].y-p[1].y)*pos/dis;
   tmp.x2=tmp.x1+p[1].y-p[x].y;
   tmp.y2=tmp.y1+p[x].x-p[1].x;
   return tmp;
}

int main()
{
   int i,j,n,s=0;
   double r;
   struct case2 p1,p2;
   struct case3 t;
   scanf("%d",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%lf%lf%lf",&p[i].x,&p[i].y,&p[i].r);
      eps=max(eps,p[i].r/1e8);
   }
   qs(1,n);
   for (i=1;i<=n;i++)
      if (!s||!zero(p[i].x-p[s].x)||!zero(p[i].y-p[s].y)||!zero(p[i].r-p[s].r))
         p[++s]=p[i];
   if (s==1)
   {
      puts("-2");
      goto end;
   }
   for (i=1;i<s;i++)
      if (zero(p[i].x-p[i+1].x)&&zero(p[i].y-p[i+1].y))
      {
         puts("-1");
         goto end;
      }
   p1=solve1(2);
   for (i=3;i<=s;i++)
   {
      p2=solve1(i);
      if (zero(cj(p1.x1-p1.x2,p1.y1-p1.y2,p2.x1-p2.x2,p2.y1-p2.y2)))
      {
         if (!zero(cj(p1.x1-p2.x2,p1.y1-p2.y2,p2.x1-p2.x2,p2.y1-p2.y2)))
         {
            puts("-1");
            goto end;
         }
      }
      else
      {
         t=solve2(p1.x1,p1.y1,p1.x2,p1.y2,p2.x1,p2.y1,p2.x2,p2.y2);
         break;
      }
   }
   if (i>s)
   {
      puts("-2");
      goto end;
   }
   for (i=1;i<=s;i++)
      if ((t.x-p[i].x)*(t.x-p[i].x)+(t.y-p[i].y)*(t.y-p[i].y)<p[i].r*p[i].r+eps)
      {
         puts("-1");
         goto end;
      }
   r=sqrt((t.x-p[1].x)*(t.x-p[1].x)+(t.y-p[1].y)*(t.y-p[1].y)-p[1].r*p[1].r);
   for (i=2;i<=s&&zero(r-sqrt((t.x-p[i].x)*(t.x-p[i].x)+(t.y-p[i].y)*(t.y-p[i].y)-p[i].r*p[i].r));i++);
   if (i<=s)
      puts("-1");
   else
      printf("%.10lf %.10lf %.10lf\n",t.x,t.y,r);
   end:
   return 0;
}
