#include <stdio.h>
#define oo 1000000000
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   int w,t,s;
}p[11];
struct case2
{
   int c,D,d;
}l[1001];
int f[1001][1025],w[1025],s[1025],v[1025];
int n;

int value(int x)
{
   int i,s=0;
   for (i=1;i<=n;i++)
      if (x&(1<<i-1))
         s+=p[i].s;
   return s;
}

int slow(int x)
{
   int i,s=0;
   for (i=1;i<=n;i++)
      if (x&(1<<i-1))
         s=max(s,p[i].t);
   return s;
}

int weight(int x)
{
   int i,s=0;
   for (i=1;i<=n;i++)
      if (x&(1<<i-1))
         s+=p[i].w;
   return s;
}

int main()
{
   int i,j,k,m,x,y,ans=oo;
   scanf("%d%d",&n,&m);
   for (i=1;i<=n;i++)
      scanf("%d%d%d",&p[i].w,&p[i].t,&p[i].s);
   for (i=1;i<=m;i++)
      scanf("%d%d%d",&l[i].c,&l[i].D,&l[i].d);
   for (i=1;i<(1<<n);i++)
   {
      w[i]=weight(i);
      s[i]=slow(i);
      v[i]=value(i);
   }
   for (i=1;i<(1<<n);i++)
      f[0][i]=oo;
   for (i=1;i<=m;i++)
   {
      f[i][0]=oo;
      for (j=1;j<(1<<n);j++)
      {
         x=w[j];
         y=s[(1<<n)-1-j];
         f[i][j]=max(((x<=l[i].c)?l[i].d:l[i].D),y);
         y=oo;
         for (k=0;k<(1<<n);k++)
         {
            x=v[j^k]+f[i-1][k];
            y=min(y,x);
         }
         f[i][j]+=y;
      }
   }
   for (i=1;i<(1<<n);i++)
   {
      x=f[m][i]+v[i];
      ans=min(ans,x);
   }
   printf("%d\n",ans);
   return 0;
}
