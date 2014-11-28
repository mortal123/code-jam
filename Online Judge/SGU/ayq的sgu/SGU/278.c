#include <stdio.h>
#define abb(a) ((a)>0?(a):(-(a)))
#define zero(a) (abb(a)<=1e-8)
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   double b,c;
}d1[75001]={{0,0}},d2[75001]={{0,0}};

void qs(long x,long y,struct case1 p[])
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&p[j].c<t.c)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i].c>t.c)
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1,p);
   qs(i+1,y,p);
}

int main()
{
   long i,j,n,s1=0,s2=0;
   double a,b,x,y,t,ans=0;
   scanf("%ld%lf%lf",&n,&a,&b);
   for (i=1;i<=n;i++)
   {
      scanf("%lf%lf%lf",&t,&x,&y);
      x/=t;
      y/=t;
      ans=max(ans,y*min(a,b/x));
      if (!zero(x-b/a))
      {
         if (x>b/a)
            d1[++s1]=(struct case1){x,y};
         else
            d2[++s2]=(struct case1){x,y};
      }
   }
   qs(1,s1,d1);
   qs(1,s2,d2);
   for (i=1;i<=s1;i++)
      for (j=1;j<=s2&&(d1[i].c*a>ans||d2[j].c*a>ans);j++)
      {
         t=(b-d2[j].b*a)/(d1[i].b-d2[j].b);
         ans=max(ans,d1[i].c*t+d2[j].c*(a-t));
      }
   printf("%.10lf\n",ans);
   return 0;
}
