#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define eps 1e-7
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   int x,y,z,r;
}p[11];
double rx,ry,rz,ans=-oo;
int n,a,b,c;

double check(double x,double y,double z)
{
   int i,j;
   double t,r=min(x,y);
   r=min(r,z);
   r=min(r,a-x);
   r=min(r,b-y);
   r=min(r,c-z);
   for (i=1;i<=n;i++)
   {
      t=sqrt((x-p[i].x)*(x-p[i].x)+(y-p[i].y)*(y-p[i].y)+(z-p[i].z)*(z-p[i].z))-p[i].r;
      r=min(r,t);
   }
   if (r>ans)
   {
      ans=r;
      rx=x;
      ry=y;
      rz=z;
   }
   return r;
}

int main()
{
   int i,s=0,sx=1,sy=1,sz=1;
   double t,px,py,pz,nx,ny,nz,last;
   srand(2222);
   scanf("%d%d%d%d",&a,&b,&c,&n);
   for (i=1;i<=n;i++)
      scanf("%d%d%d%d",&p[i].x,&p[i].y,&p[i].z,&p[i].r);
   px=a/2.0;
   py=b/2.0;
   pz=c/2.0;
   t=1;
   last=check(px,py,pz);
   while (t*a>eps||t*b>eps||t*c>eps)
   {
      do
         nx=px+(rand()%11112-5555.5)/5555.5*t*a;
      while (nx<0||nx>a);
      do
         ny=py+(rand()%11112-5555.5)/5555.5*t*b;
      while (ny<0||ny>b);
      do
         nz=pz+(rand()%11112-5555.5)/5555.5*t*c;
      while (nz<0||nz>c);
      t=check(nx,ny,nz);
      if (t>last)
      {
         last=t;
         px=nx;
         py=ny;
         pz=nz;
         s=0;
      }
      else
         s++;
      if (s>10000)
      {
         s=0;
         t*=0.5;
      }
   }
   printf("%lf %lf %lf\n",rx,ry,rz);
   return 0;
}
