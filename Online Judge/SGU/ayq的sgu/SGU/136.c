#include <stdio.h>
#define abb(a) ((a)>0?(a):(-(a)))
#define zero(a) (abb(a)<=1e-7)

struct case1
{
   double x,y;
}p[10001]={{0,0}};

int main()
{
   long i,n;
   double x=0,y=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%lf%lf",&p[i].x,&p[i].y);
      if (i&1)
      {
         x+=p[i].x;
         y+=p[i].y;
      }
      else
      {
         x-=p[i].x;
         y-=p[i].y;
      }
   }
   if ((n&1)||zero(x)&&zero(y))
   {
      printf("YES\n");
      for (i=1;i<=n;i++)
      {
         printf("%.3lf %.3lf\n",x,y);
         x=2*p[i].x-x;
         y=2*p[i].y-y;
      }
   }
   else
      printf("NO\n");
   return 0;
}
