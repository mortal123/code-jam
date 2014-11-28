#include <stdio.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   long a,b,v;
}p[5001]={0,0,0};
long f[101][101]={0},fa[101]={0},v[101]={0};

long getf(long now)
{
   if (fa[now]==now)
      return now;
   return fa[now]=getf(fa[now]);
}

int main()
{
   long i,j,k,n,m,r,a,b,flag=0;
   double ans=oo,sum,t;
   scanf("%ld%ld%ld",&n,&m,&r);
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&v[i]);
      fa[i]=i;
      for (j=i+1;j<=n;j++)
         f[i][j]=f[j][i]=oo;
   }
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld",&p[i].a,&p[i].b,&p[i].v);
      f[p[i].a][p[i].b]=f[p[i].b][p[i].a]=p[i].v;
      fa[getf(p[i].a)]=getf(p[i].b);
      if (p[i].v>=2*r)
         flag=1;
   }
   for (i=1;i<n;i++)
      if (getf(i)!=getf(i+1))
         flag=0;
   if (!flag)
   {
      if (n==1&&!r)
         puts("0");
      else
         puts("-1");
   }
   else
   {
      for (k=1;k<=n;k++)
         for (i=1;i<=n;i++)
            for (j=1;j<=n;j++)
               f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
      for (i=1;i<=m;i++)
         if (p[i].v>=2*r)
         {
            sum=0;
            for (j=1;j<=n;j++)
               sum+=v[j]/10000.0*min(f[j][p[i].a]+r,f[j][p[i].b]+p[i].v-r);
            ans=min(ans,sum);
            sum=0;
            for (j=1;j<=n;j++)
               sum+=v[j]/10000.0*min(f[j][p[i].b]+r,f[j][p[i].a]+p[i].v-r);
            ans=min(ans,sum);
         }
      printf("%.10lf\n",ans);
   }
   return 0;
}
