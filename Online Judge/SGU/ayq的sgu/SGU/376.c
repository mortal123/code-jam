#include <stdio.h>

struct case1
{
   long r,p,pos;
   long long t;
}p[1001]={0,0,0,0};
long a[1001]={0},b[1001]={0},h[1001]={0};

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&(p[j].t>t.t||p[j].t==t.t&&p[j].p<t.p))
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&(p[i].t<t.t||p[i].t==t.t&&p[i].p>t.p))
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

void qs2(long x,long y)
{
   long i=x,j=y,t=h[(x+y)>>1];
   if (x>=y)
      return;
   h[(x+y)>>1]=h[x];
   while (i<j)
   {
      while (i<j&&h[j]<t)
         j--;
      if (i<j)
         h[i++]=h[j];
      while (i<j&&h[i]>t)
         i++;
      if (i<j)
         h[j--]=h[i];
   }
   h[i]=t;
   qs2(x,i-1);
   qs2(i+1,y);
}

int main()
{
   long i,j,n,k;
   scanf("%ld%ld",&n,&k);
   for (i=1;i<=n;i++)
   {
      scanf("%I64d%ld%ld",&p[i].t,&p[i].r,&p[i].p);
      p[i].t*=-1;
      p[i].pos=i;
   }
   qs(1,n);
   for (i=1;i<=k;i++)
      scanf("%ld",&a[i]);
   for (i=1;i<=n;i++)
      scanf("%ld",&b[i]);
   for (i=1;i<=k;i++)
   {
      for (j=1;j<=n;j++)
         h[j]=3*a[i]*a[i]+5*a[i]*b[j]+2*b[j]*b[j];
      qs2(1,n);
      for (j=1;j<=n;j++)
         p[j].t-=p[j].r+h[j];
      qs(1,n);
   }
   for (i=1;i<=n;i++)
      printf("%ld%c",p[i].pos,(i==n)?'\n':' ');
   return 0;
}
