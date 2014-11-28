#include<stdio.h>
#include<math.h>
#define oo 1000000000
#define max(a,b) ((a)>0?(a):(-(a)))
#define dis(x1,y1,z1,x2,y2,z2) (((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1))+((z2)-(z1))*((z2)-(z1)))

struct case1
{
   double x,y,z,r;
}p[51]={{0,0,0,0}};

int main()
{
   long i,j,n,r;
   double min,x,y,z,x2,y2,z2,dx,dy,dz,rx,ry,rz,rdx,rdy,rdz,a,b,c,drt,t;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%lf%lf%lf%lf",&p[i].x,&p[i].y,&p[i].z,&p[i].r);
   scanf("%lf%lf%lf%lf%lf%lf",&x,&y,&z,&dx,&dy,&dz);
   dx-=x;
   dy-=y;
   dz-=z;
   for (i=1;i<=11;i++)
   {
      min=oo;
      for (j=1;j<=n;j++)
      {
         a=dx*dx+dy*dy+dz*dz;
         b=-2*((p[j].x-x)*dx+(p[j].y-y)*dy+(p[j].z-z)*dz);
         c=(p[j].x-x)*(p[j].x-x)+(p[j].y-y)*(p[j].y-y)+(p[j].z-z)*(p[j].z-z)-p[j].r*p[j].r;
         drt=b*b-4*a*c;
         if (drt>=-1e-7)
         {
            t=(-b-sqrt(max(drt,0)))/(2*a);
            if (t>1e-7)
            {
               x2=x+t*dx;
               y2=y+t*dy;
               z2=z+t*dz;
               if (dis(x,y,z,x2,y2,z2)<min)
               {
                  min=dis(x,y,z,x2,y2,z2);
                  r=j;
                  rx=x2;
                  ry=y2;
                  rz=z2;
                  t=-2*((x2-p[j].x)*(x2-x)+(y2-p[j].y)*(y2-y)+(z2-p[j].z)*(z2-z))/((x2-p[j].x)*(x2-p[j].x)+(y2-p[j].y)*(y2-p[j].y)+(z2-p[j].z)*(z2-p[j].z));
                  rdx=t*(x2-p[j].x)+(x2-x);
                  rdy=t*(y2-p[j].y)+(y2-y);
                  rdz=t*(z2-p[j].z)+(z2-z);
               }
            }
         }
      }
      if (min<oo-1)
      {
         if (i>1)
            printf(" ");
         if (i==11)
         {
            printf("etc.\n");
            break;
         }
         else
         {
            printf("%ld",r);
            x=rx;
            y=ry;
            z=rz;
            dx=rdx;
            dy=rdy;
            dz=rdz;
         }
      }
      else
         break;
   }
   return 0;
}
