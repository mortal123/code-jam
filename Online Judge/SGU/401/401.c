#include <stdio.h>
#include <math.h>
#define oo 10000000000000000.0

struct case1
{
   double w,v;
}p[51]={0,0};
long n;
double u;
double rec[51]={0};

double check(double mid)
{
   long i;
   double s=0;
   for (i=1;i<=n;i++)
      if (mid<=p[i].v)
         return oo;
      else
         s+=p[i].w/sqrt(u*u-(u*u/(mid-p[i].v))*(u*u/(mid-p[i].v)));
   return s;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
   long i;
   double l=0,r=oo,mid,t,s=0,ans1=0,ans2=0;
   scanf("%ld%lf%lf",&n,&u,&t);
   for (i=1;i<=n;i++)
   {
      scanf("%lf%lf",&p[i].w,&p[i].v);
      ans2+=p[i].w;
      s+=p[i].w/u;
   }
   if (s>t+1e-10)
      puts("-1");
   else
   {
      for (i=1;i<=10000;i++)
      {
         mid=(l+r)/2;
         double tmp = check(mid);
         if (tmp <= t)
            r=mid;
         else
            l=mid;
      }
      for (i=1;i<=n;i++)
      {
         rec[i]=p[i].w/sqrt(u*u-(u*u/(r-p[i].v))*(u*u/(r-p[i].v)));
         ans1+=rec[i]*(sqrt(u*u-p[i].w*p[i].w/rec[i]/rec[i])+p[i].v);
      }
      printf("%.10lf\n",sqrt(ans1*ans1+ans2*ans2));
      for (i=1;i<=n;i++)
         printf("%.10lf%c",rec[i],(i==n)?'\n':' ');
   }
   return 0;
}
