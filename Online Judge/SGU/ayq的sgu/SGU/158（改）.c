#include <stdio.h>
#define oo 1000000000

long pas[305]={0},door[305]={0};
double f[305]={0};
long n,m;

double check(double s)
{
   long i,j=1;
   double sum=0;
   for (i=1;i<=m;i++)
   {
      while (j<=n&&door[j]+s-1e-7<pas[i])
         j++;
      f[i]=pas[i]-door[j-1]-s;
   }
   j=n;
   for (i=m;i>=1;i--)
   {
      while (j>=1&&door[j]+s+1e-7>pas[i])
         j--;
      if (f[i]>door[j+1]+s-pas[i])
         f[i]=door[j+1]+s-pas[i];
      sum+=f[i];
   }
   return sum;
}

int main()
{
   long i,l;
   double s,p,t,ans=-oo;
   scanf("%ld%ld",&l,&m);
   for (i=1;i<=m;i++)
      scanf("%ld",&pas[i]);
   scanf("%ld",&n);
   for (i=2;i<=n;i++)
      scanf("%ld",&door[i]);
   door[0]=-oo;
   door[n+1]=oo;
   for (s=0;s<l-door[n]+1e-7;s+=0.25)
   {
      t=check(s);
      if (t>ans)
      {
         ans=t;
         p=s;
      }
   }
   printf("%.1lf %.1lf\n",p,ans);
   return 0;
}
