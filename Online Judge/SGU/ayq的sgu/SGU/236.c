#include <stdio.h>
#define oo 100000000
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   long a,b;
   double x,y;
}p[2501]={{0,0},{0,0}};
double f[51][51]={0},g[51][51]={0};
long last[51][51]={0},ans[51]={0};
long n,m,ra,rb,rc,tot=0;

void dfs(long x,long y)
{
   if (last[x][y])
   {
      dfs(x,last[x][y]);
      ans[++tot]=last[x][y];
      dfs(last[x][y],y);
   }
}

long check(double mid)
{
   long i,j,k;
   for (i=1;i<=n;i++)
   {
      for (j=i+1;j<=n;j++)
      {
         f[i][j]=f[j][i]=g[i][j]=g[j][i]=-oo;
         last[i][j]=last[j][i]=0;
      }
      f[i][i]=g[i][i]=last[i][i]=0;
   }
   for (i=1;i<=m;i++)
      f[p[i].a][p[i].b]=g[p[i].a][p[i].b]=max(f[p[i].a][p[i].b],p[i].x-p[i].y*mid);
   for (i=1;i<=n;i++)
   {
      for (j=1;j<i;j++)
         for (k=1;k<i;k++)
            if (f[j][k]+g[k][i]+g[i][j]>=0)
            {
               ra=j;
               rb=k;
               rc=i;
               return 1;
            }
      for (j=1;j<=n;j++)
         if (j!=i)
            for (k=1;k<=n;k++)
               if (k!=i&&f[j][i]+f[i][k]>f[j][k])
               {
                  f[j][k]=f[j][i]+f[i][k];
                  last[j][k]=i;
               }
   }
   return 0;
}

int main()
{
   long i;
   double l=0,r=1e2,mid;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
      scanf("%ld%ld%lf%lf",&p[i].a,&p[i].b,&p[i].x,&p[i].y);
   while (l<r-1e-9)
   {
      mid=(l+r)/2;
      if (check(mid))
         l=mid;
      else
         r=mid;
   }
   if (l<1e-3)
      printf("0\n");
   else
   {
      check(l);
      ans[++tot]=rb;
      ans[++tot]=rc;
      if (ra!=rb)
      {
         ans[++tot]=ra;
         dfs(ra,rb);
      }
      printf("%ld\n",tot);
      for (i=1;i<=tot;i++)
         printf("%ld%c",ans[i],(i==tot)?'\n':' ');
   }
   return 0;
}
