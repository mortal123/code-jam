#include <stdio.h>

struct case1
{
   long v,pos;
}q[60001]={0,0};
struct case2
{
   long a,b,r,v,pos;
}p[30001]={0,0,0,0,0};
long f[60001]={0};

void qs1(long x,long y)
{
   long i=x,j=y;
   struct case1 t=q[(x+y)>>1];
   if (x>=y)
      return;
   q[(x+y)>>1]=q[x];
   while (i<j)
   {
      while (i<j&&q[j].v>t.v)
         j--;
      if (i<j)
         q[i++]=q[j];
      while (i<j&&q[i].v<t.v)
         i++;
      if (i<j)
         q[j--]=q[i];
   }
   q[i]=t;
   qs1(x,i-1);
   qs1(i+1,y);
}

void qs2(long x,long y)
{
   long i=x,j=y;
   struct case2 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&(p[j].r>t.r||p[j].r==t.r&&p[j].v>t.v))
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&(p[i].r<t.r||p[i].r==t.r&&p[i].v<t.v))
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs2(x,i-1);
   qs2(i+1,y);
}

long getf(long now)
{
   if (f[now]==now)
      return now;
   return f[now]=getf(f[now]);
}

int main()
{
   long i,n,fa,fb,tot=0;
   long long ans=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld%ld%ld",&q[i].v,&q[i+n].v,&p[i].r,&p[i].v);
      p[i].pos=i;
      q[i].pos=i;
      q[i+n].pos=i+n;
   }
   qs1(1,2*n);
   for (i=1;i<=2*n;i++)
   {
      if (i==1||q[i].v>q[i-1].v)
         tot++;
      if (q[i].pos<=n)
         p[q[i].pos].a=tot;
      else
         p[q[i].pos-n].b=tot;
   }
   qs2(1,n);
   for (i=1;i<=tot;i++)
      f[i]=i;
   for (i=n;i;i--)
   {
      fa=getf(p[i].a);
      fb=getf(p[i].b);
      if (fa!=fb)
      {
         f[fa]=fb;
         ans+=p[i].v;
      }
   }
   printf("%I64d\n",ans);
   for (i=1;i<=n;i++)
      printf("%ld%c",p[i].pos,(i==n)?'\n':' ');
   return 0;
}
