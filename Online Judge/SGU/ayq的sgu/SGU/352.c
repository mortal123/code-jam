#include <stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   long v,l,r,h,s;
}p[200002]={0,0,0,0,0};
long f[4001][2]={0},h[4001]={0},head[4001]={0},e[200002]={0},next[200002]={0},dis[200002]={0},v[200002]={0},num[200002]={0};
char link[4001][4001]={0},hash[4001]={0};
long n,totm=1;

void add(long a,long b,long c,long d,long t)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   dis[totm]=c;
   v[totm]=d;
   num[totm]=t;
}

long merge(long a,long b)
{
   if (!a)
      return b;
   if (!b)
      return a;
   if (p[a].v>p[b].v)
   {
      a^=b;
      b^=a;
      a^=b;
   }
   p[a].r=merge(p[a].r,b);
   if (p[p[a].l].h<p[p[a].r].h)
   {
      p[a].l^=p[a].r;
      p[a].r^=p[a].l;
      p[a].l^=p[a].r;
   }
   p[a].h=min(p[p[a].l].h,p[p[a].r].h)+1;
   return a;
}

void dfs1(long now,long last)
{
   long i,j;
   link[now][now]=1;
   for (i=head[now];i;i=next[i])
      if (v[i]&&e[i]!=last)
      {
         f[e[i]][0]=f[now][0]+dis[i];
         dfs1(e[i],now);
         for (j=1;j<=n;j++)
            link[now][j]|=link[e[i]][j];
      }
}

void dfs2(long now)
{
   long i;
   for (i=head[now];i;i=next[i])
      if (link[now][e[i]]&&v[i])
      {
         dfs2(e[i]);
         h[now]=merge(h[now],h[e[i]]);
      }
   for (i=head[now];i;i=next[i])
      if (!v[i])
      {
         p[i]=(struct case1){f[now][0]+f[e[i]][0]+dis[i],0,0,1,now};
         h[now]=merge(h[now],i);
      }
   while (h[now])
      if (!link[now][e[h[now]]]||!link[now][p[h[now]].s])
      {
         f[now][1]=p[h[now]].v-f[now][0];
         break;
      }
      else
         h[now]=merge(p[h[now]].l,p[h[now]].r);
}

int main()
{
   long i,j,m,a,b,c,d;
   p[0].h=-1;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld%ld",&a,&b,&c,&d);
      add(a,b,c,d,i);
      add(b,a,c,d,i);
   }
   dfs1(1,0);
   dfs2(1);
   for (i=2;i<=n;i++)
      printf("%ld%c",f[i][1]?f[i][1]:-1,(i==n)?'\n':' ');
   return 0;
}
