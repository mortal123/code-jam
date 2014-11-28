#include <stdio.h>
#include <math.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

long a[11]={0};
long n;
double p,ans=oo;

void dfs(long now,long x,long y,long z)
{
   if (now>n)
   {
      if (x>=0&&y>=0&&z>=0&&x+y>=z&&x+z>=y&&y+z>=x)
      {
         p=(x+y+z)/2.0;
         p=sqrt(max(p*(p-x)*(p-y)*(p-z),0));
         ans=min(ans,p);
      }
   }
   else
   {
      dfs(now+1,x+a[now],y,z);
      dfs(now+1,x,y+a[now],z);
      dfs(now+1,x,y,z+a[now]);
      dfs(now+1,x-a[now],y,z);
      dfs(now+1,x,y-a[now],z);
      dfs(now+1,x,y,z-a[now]);
   }
}

int main()
{
   long i;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%ld",&a[i]);
   dfs(1,0,0,0);
   printf("%.10lf\n",ans);
   return 0;
}
