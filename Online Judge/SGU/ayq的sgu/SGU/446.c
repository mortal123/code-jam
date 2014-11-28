#include <math.h>
#include <stdio.h>
#define eps 1e-5
#define pi 3.14159265359
#define zero(a) (abb(a)<eps)
#define abb(a) ((a)>0?(a):(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))
#define dis(x1,y1,x2,y2) sqrt(((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1)))

struct case1
{
   double x,y;
}p[1001]={0,0},q[1001]={0,0},rec[1001]={0};

void qs(long x,long y,struct case1 a[])
{
   long i=x,j=y;
   struct case1 t=a[(x+y)>>1];
   if (x>=y)
      return;
   a[(x+y)>>1]=a[x];
   while (i<j)
   {
      while (i<j&&(a[j].x>t.x+eps||zero(a[j].x-t.x)&&a[j].y>t.y))
         j--;
      if (i<j)
         a[i++]=a[j];
      while (i<j&&(a[i].x<t.x-eps||zero(a[i].x-t.x)&&a[i].y<t.y))
         i++;
      if (i<j)
         a[j--]=a[i];
   }
   a[i]=t;
   qs(x,i-1,a);
   qs(i+1,y,a);
}

double D(double x,double y)
{
   if (x>eps&&y>=0)
      return atan(y/x);
   if (x<-eps)
      return pi+atan(y/x);
   if (x>eps)
      return 2*pi-atan(-y/x);
   if (y>0)
      return pi/2;
   return pi/2*3;
}

int main()
{
   long i,j,k,n;
   double d1,d2,s1,s2,d,dis,tmp,ans=pi;
   scanf("%ld",&n);
   if (!n)
      puts("0");
   else
   {
      for (i=1;i<=n;i++)
         scanf("%lf%lf",&p[i].x,&p[i].y);
      for (i=1;i<=n;i++)
         scanf("%lf%lf",&q[i].x,&q[i].y);
      qs(1,n,q);
      s1=dis(p[1].x,p[1].y,p[2].x,p[2].y);
      d1=D(p[2].x-p[1].x,p[2].y-p[1].y);
      for (i=1;i<=n;i++)
         for (j=1;j<=n;j++)
         {
            s2=dis(q[i].x,q[i].y,q[j].x,q[j].y);
            if (zero(s1-s2))
            {
               d2=D(q[j].x-q[i].x,q[j].y-q[i].y);
               tmp=d2-d1;
               if (tmp<0)
                  tmp+=2*pi;
               if (min(tmp,2*pi-tmp)<ans)
               {
                  for (k=1;k<=n;k++)
                  {
                     d=D(p[k].x-p[1].x,p[k].y-p[1].y)+tmp;
                     dis=dis(p[1].x,p[1].y,p[k].x,p[k].y);
                     rec[k]=(struct case1){q[i].x+dis*cos(d),q[i].y+dis*sin(d)};
                  }
                  qs(1,n,rec);
                  for (k=1;k<=n&&zero(q[k].x-rec[k].x)&&zero(q[k].y-rec[k].y);k++);
                  if (k==n+1)
                     ans=min(tmp,2*pi-tmp);
               }
            }
         }
      printf("%.10lf\n",ans);
   }
   return 0;
}
