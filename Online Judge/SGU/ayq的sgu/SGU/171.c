#include <stdio.h>

struct case1
{
   long v,r;
}q[101]={{0,0}};
struct case2
{
   long v,w,pos;
}p[16001]={{0,0,0}};
long ans[16001]={0};

void qs(long x,long y)
{
   long i=x,j=y;
   struct case2 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&p[j].w<t.w)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i].w>t.w)
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
   long i,j,k,p1,p2,n=0;
   scanf("%ld",&k);
   for (i=1;i<=k;i++)
   {
      scanf("%ld",&q[i].r);
      n+=q[i].r;
   }
   for (i=1;i<=k;i++)
      scanf("%ld",&q[i].v);
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&p[i].v);
      p[i].pos=i;
   }
   for (i=1;i<=n;i++)
      scanf("%ld",&p[i].w);
   qs(1,n);
   for (i=1;i<=n;i++)
   {
      p1=p2=0;
      for (j=1;j<=k;j++)
         if (q[j].r)
         {
            if (q[j].v<p[i].v&&(!p1||q[j].v>q[p1].v))
               p1=j;
            if (!p2||q[j].v>q[p2].v)
               p2=j;
         }
      if (!p1)
         p1=p2;
      ans[p[i].pos]=p1;
      q[p1].r--;
   }
   for (i=1;i<=n;i++)
      printf("%ld%c",ans[i],(i==n)?'\n':' ');
   return 0;
}
