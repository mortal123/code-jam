#include <stdio.h>
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))
#define check(a) cj(x-p[1].x,y-p[1].y,p[a].x-p[1].x,p[a].y-p[1].y)

struct case1
{
   long long x,y;
}p[100001]={{0,0}};

int main()
{
   long i,n,m,l,r,mid,k,ans=0;
   long long x,y;
   scanf("%ld%ld%ld",&n,&m,&k);
   for (i=1;i<=n;i++)
      scanf("%I64d%I64d",&p[i].x,&p[i].y);
   for (i=1;i<=m;i++)
   {
      scanf("%I64d%I64d",&x,&y);
      if (check(2)<=0&&check(n)>=0)
      {
         l=2;
         r=n;
         while (l<r-1)
         {
            mid=(l+r)>>1;
            if (check(mid)>=0)
               r=mid;
            else
               l=mid;
         }
         if (cj(x-p[r].x,y-p[r].y,p[r-1].x-p[r].x,p[r-1].y-p[r].y)>=0)
            ans++;
      }
   }
   if (ans<k)
      printf("NO\n");
   else
      printf("YES\n");
   return 0;
}
