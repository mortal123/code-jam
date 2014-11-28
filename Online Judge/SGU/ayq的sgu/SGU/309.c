#include <stdio.h>
#define oo 2000000000
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   long x,y,s;
}p[20001]={0,0,0};
long n;

long dfs(long now,long mid)
{
   long i;
   long long minx=oo,miny=oo,maxx=-oo,maxy=-oo;
   for (i=1;i<=n;i++)
      if (p[i].s==0)
      {
         minx=min(minx,p[i].x);
         miny=min(miny,p[i].y);
         maxx=max(maxx,p[i].x);
         maxy=max(maxy,p[i].y);
      }
   if (now==3)
      return maxx-minx<=mid&&maxy-miny<=mid;
   for (i=1;i<=n;i++)
      if (p[i].s==0&&p[i].x<=minx+mid&&p[i].y<=miny+mid)
         p[i].s=now;
   if (dfs(now+1,mid))
      return 1;
   for (i=1;i<=n;i++)
      if (p[i].s==now)
         p[i].s=0;
   for (i=1;i<=n;i++)
      if (p[i].s==0&&p[i].x<=minx+mid&&p[i].y>=maxy-mid)
         p[i].s=now;
   if (dfs(now+1,mid))
      return 1;
   for (i=1;i<=n;i++)
      if (p[i].s==now)
         p[i].s=0;
   for (i=1;i<=n;i++)
      if (p[i].s==0&&p[i].x>=maxx-mid&&p[i].y<=miny+mid)
         p[i].s=now;
   if (dfs(now+1,mid))
      return 1;
   for (i=1;i<=n;i++)
      if (p[i].s==now)
         p[i].s=0;
   for (i=1;i<=n;i++)
      if (p[i].s==0&&p[i].x>=maxx-mid&&p[i].y>=maxy-mid)
         p[i].s=now;
   if (dfs(now+1,mid))
      return 1;
   for (i=1;i<=n;i++)
      if (p[i].s==now)
         p[i].s=0;
   return 0;
}

long check(long mid)
{
   long i;
   for (i=1;i<=n;i++)
      p[i].s=0;
   return dfs(1,mid);
}

int main()
{
   long i,m;
   long long l=0,r=oo;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%ld%ld",&p[i].x,&p[i].y);
   while (l<r-1)
   {
      m=(l+r)>>1;
      if (check(m))
         r=m;
      else
         l=m;
   }
   printf("%I64d\n",r);
   return 0;
}
