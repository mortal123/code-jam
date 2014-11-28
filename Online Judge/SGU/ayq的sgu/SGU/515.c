#include <stdio.h>
#define oo 1000000000

struct case1
{
   long pos,dis;
}p[100001]={0,0},d[100001]={0,0};
long ans[100001]={0},pos[100001]={0},head[100001]={0},e[200001]={0},next[200001]={0},v[200001]={0},num[200001]={0};
long k,n,totm=0,top=0,tot;
char hash[100001]={0};

void add(long a,long b,long c,long d)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   v[totm]=c;
   num[totm]=d;
}

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&p[j].dis>t.dis)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i].dis<t.dis)
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

void swap(long a,long b)
{
   struct case1 t=d[a];
   pos[d[a].pos]^=pos[d[b].pos];
   pos[d[b].pos]^=pos[d[a].pos];
   pos[d[a].pos]^=pos[d[b].pos];
   d[a]=d[b];
   d[b]=t;
}

void up(long i)
{
   while (i>1)
      if (d[i>>1].dis>d[i].dis)
      {
         swap(i,i>>1);
         i>>=1;
      }
      else
         break;
}

void down(long i)
{
   long a;
   while ((a=i*2)<=tot)
   {
      if (a<tot&&d[a+1].dis<d[a].dis)
         a++;
      if (d[a].dis<d[i].dis)
      {
         swap(i,a);
         i=a;
      }
      else
         break;
   }
}

void dijkstra(long now)
{
   long i;
   tot=n;
   for (i=1;i<=n;i++)
   {
      pos[i]=i;
      d[i]=(struct case1){i,oo};
   }
   d[now].dis=0;
   if (now!=1)
      swap(1,now);
   while (tot&&d[1].dis<oo)
   {
      if (tot>1)
         swap(1,tot);
      tot--;
      down(1);
      for (i=head[d[tot+1].pos];i;i=next[i])
         if (d[pos[e[i]]].dis>d[tot+1].dis+v[i])
         {
            d[pos[e[i]]].dis=d[tot+1].dis+v[i];
            up(pos[e[i]]);
         }
   }
   for (i=1;i<=k;i++)
      p[i].dis=d[pos[p[i].pos]].dis;
}

long dfs(long now,long h)
{
   long i;
   if (now==p[h].pos)
      return 1;
   for (i=head[now];i;i=next[i])
      if (!hash[e[i]]&&d[pos[e[i]]].dis==d[pos[now]].dis+v[i])
      {
         hash[e[i]]=1;
         if (dfs(e[i],h))
         {
            ans[++top]=num[i];
            return 1;
         }
      }
   return 0;
}

int main()
{
   long i,m,a,b,c,t=1;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld",&a,&b,&c);
      add(a,b,c,i);
      add(b,a,c,i);
   }
   scanf("%ld",&k);
   for (i=1;i<=k;i++)
      scanf("%ld",&p[i].pos);
   dijkstra(p[1].pos);
   for (i=2;i<=k;i++)
      if (p[t].dis<p[i].dis)
         t=i;
   dijkstra(p[t].pos);
   qs(1,k);
   for (i=k-1;i>=1;i--)
      dfs(p[i].pos,i+1);
   printf("%ld\n",top);
   for (i=1;i<=top;i++)
      printf("%ld%c",ans[i],(i==top)?'\n':' ');
   return 0;
}
