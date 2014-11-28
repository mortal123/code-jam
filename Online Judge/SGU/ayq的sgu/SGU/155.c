#include <stdio.h>

struct case1
{
   long t,h,num;
}p[50001]={{0,0,0}};
struct case2
{
   long v,l,r,f;
}q[50001]={{0,0,0,0}};

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&p[j].t>t.t)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i].t<t.t)
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
   long i,n,last=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      p[i].num=i;
      scanf("%ld%ld",&p[i].t,&p[i].h);
   }
   qs(1,n);
   for (i=1;i<=n;i++)
   {
      while (last&&q[last].v>p[i].h)
         last=q[last].f;
      q[p[i].num].l=q[last].r;
      q[p[i].num].v=p[i].h;
      q[q[last].r].f=p[i].num;
      q[last].r=p[i].num;
      q[p[i].num].f=last;
      last=p[i].num;
   }
   printf("YES\n");
   for (i=1;i<=n;i++)
      printf("%ld %ld %ld\n",q[i].f,q[i].l,q[i].r);
   return 0;
}
