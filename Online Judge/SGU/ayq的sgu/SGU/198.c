#include <stdio.h>
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))

struct case1
{
   double x,y,r;
}p[301]={{0,0,0}};
struct case2
{
   long a,b,v;
   char choose;
}l[90001]={{0,0,0},{'\0'}};
long link[301][301]={0},v[301][301]={0},w[301][301]={0},hash[301]={0},f[301]={0};
long n,flag=0;

long getf(long now)
{
   if (f[now]==now)
      return now;
   return f[now]=getf(f[now]);
}

void dfs(long st,long now)
{
   long i;
   hash[now]=flag;
   for (i=1;i<=n;i++)
      if (hash[i]!=flag&&link[now][i])
      {
         w[st][i]=(w[st][now]^v[now][i]);
         dfs(st,i);
      }
}

int main()
{
   long i,j,fa,fb,tot=0;
   double x,y,r,px=387268372.3235,py=298264733.3359;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%lf%lf%lf",&p[i].x,&p[i].y,&p[i].r);
      f[i]=i;
   }
   scanf("%lf%lf%lf",&x,&y,&r);
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         if ((p[i].x-p[j].x)*(p[i].x-p[j].x)+(p[i].y-p[j].y)*(p[i].y-p[j].y)<(p[i].r+p[j].r+2*r)*(p[i].r+p[j].r+2*r))
         {
            l[++tot].a=i;
            l[tot].b=j;
         }
   for (i=1;i<=tot;i++)
   {
      if (cj(px-x,py-y,p[l[i].a].x-x,p[l[i].a].y-y)*cj(px-x,py-y,p[l[i].b].x-x,p[l[i].b].y-y)<0&&cj(p[l[i].a].x-p[l[i].b].x,p[l[i].a].y-p[l[i].b].y,px-p[l[i].b].x,py-p[l[i].b].y)*cj(p[l[i].a].x-p[l[i].b].x,p[l[i].a].y-p[l[i].b].y,x-p[l[i].b].x,y-p[l[i].b].y)<0)
         l[i].v=1;
      fa=getf(l[i].a);
      fb=getf(l[i].b);
      if (fa!=fb)
      {
         f[fa]=fb;
         link[l[i].a][l[i].b]=link[l[i].b][l[i].a]=1;
         v[l[i].a][l[i].b]=v[l[i].b][l[i].a]=l[i].v;
         l[i].choose=1;
      }
   }
   for (i=1;i<=n;i++)
   {
      flag++;
      dfs(i,i);
   }
   for (i=1;i<=tot&&(l[i].choose||!(w[l[i].a][l[i].b]^l[i].v));i++);
   if (i<=tot)
      printf("NO\n");
   else
      printf("YES\n");
   return 0;
}
