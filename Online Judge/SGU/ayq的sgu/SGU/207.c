#include<stdio.h>
#define abb(a) ((a)>0?(a):(-(a)))

struct case1
{
   long pos;
   double v;
}p[1001]={{0},{0}};
long ans[1001]={0};

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&p[j].v>t.v)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i].v<t.v)
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

int main()
{
   long i,n,x,y,s=0;
   double t;
   scanf("%ld%ld%ld",&n,&x,&y);
   for (i=1;i<=n;i++)
   {
      scanf("%lf",&t);
      ans[i]=(long)(t*x/y+0.0000000001);
      s+=ans[i];
      p[i].pos=i;
      p[i].v=abb(1.0*(ans[i]+1)/x-t/y)-abb(1.0*ans[i]/x-t/y);
   }
   qs(1,n);
   for (i=1;i<=x-s;i++)
      ans[p[i].pos]++;
   for (i=1;i<n;i++)
      printf("%ld ",ans[i]);
   printf("%ld\n",ans[n]);
   return 0;
}
