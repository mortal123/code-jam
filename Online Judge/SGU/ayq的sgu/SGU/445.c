#include <stdio.h>
#include <math.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))
#define dis(x1,y1,x2,y2) sqrt(((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1)))

long x[1001]={0},y[1001]={0};
double f[1001]={0};

int main()
{
   long i,j,n,va,vb,m;
   double t;
   scanf("%ld%ld%ld",&n,&va,&vb);
   for (i=1;i<=n;i++)
      scanf("%ld%ld",&x[i],&y[i]);
   for (i=2;i<=n;i++)
      f[i]=oo;
   for (i=1;i<n;i++)
   {
      t=dis(x[i],y[i],x[i+1],y[i+1])/va;
      f[i+1]=min(f[i+1],f[i]+t);
      if (y[i+1]>y[i])
      {
         m=y[i+1];
         for (j=i+2;j<=n&&m>y[i];j++)
         {
            if (y[j]>y[i]&&y[j]<m)
            {
               t=dis(x[i],y[i],x[i+1],y[i+1])*(y[j]-y[i])/(y[i+1]-y[i])/va+(1.0*(x[i+1]-x[i])*(y[i+1]-y[j])/(y[i+1]-y[i])+x[j]-x[i+1])/vb;
               f[j]=min(f[j],f[i]+t);
            }
            m=min(m,y[j]);
         }
         if (m<=y[i])
         {
            j--;
            t=dis(x[j-1],y[j-1],x[j],y[j])*(y[i]-y[j])/(y[j-1]-y[j])/va+(1.0*(x[j]-x[j-1])*(y[j-1]-y[i])/(y[j-1]-y[j])+x[j-1]-x[i])/vb;
            f[j]=min(f[j],f[i]+t);
         }
      }
   }
   printf("%.9lf\n",f[n]);
   return 0;
}
