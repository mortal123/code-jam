#include<stdio.h>

struct case1
{
   long st,en;
}p[16001]={0};

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&(p[j].st>t.st||p[j].st==t.st&&p[j].en<t.en))
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&(p[i].st<t.st||p[i].st==t.st&&p[i].en>t.en))
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
   long i,n,ans=0,max=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%ld%ld",&p[i].st,&p[i].en);
   qs(1,n);
   for (i=1;i<=n;i++)
   {
      if (p[i].en<=max)
         ans++;
      else
         max=p[i].en;
   }
   printf("%ld\n",ans);
   return 0;
}
