#include<math.h>
#include<time.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define oo 1000000000
#define pi 3.14159265359
#define zero(a) (abb(a)<=1e-7)
#define lowbit(a) ((a)&(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abb(a) ((a)>0?(a):(-(a)))
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y2))
#define dj(x1,y1,x2,y2) ((x1)*(y1)+(y1)*(y2))
#define dis(x1,y1,x2,y2) sqrt(((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1)))

double pos[401]={0};

int main()
{
   long i,j,k,n,p1,p2;
   double t,d,ans=oo;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%lf",&pos[i]);
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
      {
         t=0;
         d=(pos[j]-pos[i])/(j-i);
         for (k=1;k<=n;k++)
            t+=abb(pos[k]-(pos[i]+(k-i)*d));
         if (t<ans)
         {
            ans=t;
            p1=i;
            p2=j;
         }
      }
   printf("%lf\n",ans);
   d=(pos[p2]-pos[p1])/(p2-p1);
   for (i=1;i<=n;i++)
      printf("%.7lf ",pos[p1]+(i-p1)*d);
   return 0;
}
