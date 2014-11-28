#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define abb(a) ((a)>0?(a):(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))
#define oo 1000000000

struct case1
{
   long v,q,l,r;
}p[50001]={0,0,0,0};
long head[50001]={0},e[100001]={0},next[100001]={0},v[50001]={0},ans[50001]={0},h[50001]={0},size[50001]={0};
long n,m,tmp,totm=0;

void add(long a,long b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
}

void left(long *now)
{
   long son=p[*now].r;
   p[*now].r=p[son].l;
   p[son].l=*now;
   *now=son;
}

void right(long *now)
{
   long son=p[*now].l;
   p[*now].l=p[son].r;
   p[son].r=*now;
   *now=son;
}

void ins(long *now,long v)
{
   if (*now==0)
   {
      *now=v;
      p[v].l=p[v].r=0;
      return;
   }
   ans[tmp]=min(ans[tmp],abb(p[*now].v-p[v].v));
   if (p[*now].v>p[v].v)
   {
      ins(&p[*now].l,v);
      if (p[p[*now].l].q<p[*now].q)
         right(now);
   }
   else
   {
      ins(&p[*now].r,v);
      if (p[p[*now].r].q<p[*now].q)
         left(now);
   }
}

void work(long *h,long now)
{
   if (p[now].l)
      work(h,p[now].l);
   if (p[now].r)
      work(h,p[now].r);
   ins(h,now);
}

void dfs(long now,long last)
{
   long i,t=0,rec=oo;
   if (now>=n-m+1)
   {
      size[now]=1;
      h[now]=now-n+m;
      p[now-n+m]=(struct case1){v[now-n+m],rand(),0,0};
   }
   ans[now]=oo;
   for (i=head[now];i;i=next[i])
      if (e[i]!=last)
      {
         dfs(e[i],now);
         size[now]+=size[e[i]];
         ans[now]=min(ans[now],ans[e[i]]);
         if (!t||size[e[i]]>size[t])
            t=e[i];
      }
   if (now<=n-m)
   {
      tmp=now;
      for (i=head[now];i;i=next[i])
         if (e[i]!=last&&e[i]!=t)
            work(&h[t],h[e[i]]);
      h[now]=h[t];
   }
}

int main()
{
   long i,a;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<n;i++)
   {
      scanf("%ld",&a);
      add(a,i+1);
      add(i+1,a);
   }
   for (i=1;i<=m;i++)
      scanf("%ld",&v[i]);
   dfs(1,0);
   for (i=1;i<=n-m;i++)
      printf("%ld%c",(ans[i]==oo)?2147483647:ans[i],(i==n-m)?'\n':' ');
   return 0;
}
