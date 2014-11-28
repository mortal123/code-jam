#include<stdio.h>

struct case1
{
   double x;
   long n;
}p[15001]={{0},{0}};
long s[15001]={0};

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&p[j].x>t.x)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i].x<t.x)
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
   long i,n;
   scanf("%ld\n",&n);
   for (i=1;i<=n;i++)
      scanf("%lf%ld",&p[i].x,&p[i].n);
   qs(1,n);
   for (i=1;i<=n;i++)
      s[i]=s[i-1]+p[i].n;
   for (i=1;i+1<=n&&s[i]<s[n]/2;i++);
   printf("%.5lf\n",p[i].x);
   return 0;
}
