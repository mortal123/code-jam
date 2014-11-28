#include <stdio.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   long head,h,l,r;
}h[300001]={0,0,0,0};
struct case2
{
   long h,e,v,l,r;
}h2[1000001]={0,0,0,0,0};
struct case3
{
   long long v;
   long num;
}heap[300001]={0,0};
long head3[10001]={0},e3[50001]={0},next3[50001]={0},v3[50001]={0},head2[10001]={0},e2[50001]={0},next2[50001]={0},v2[50001]={0},head[300001]={0},e[2000001]={0},next[2000001]={0},v[2000001]={0},root[10001]={0},dis[10001]={0},d[2000001]={0},hash[10001]={0};
long totm=0,tot2=0,tot;

void add(long a,long b,long c,long head[],long e[],long next[],long v[])
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   v[totm]=c;
}

void dfs(long now)
{
   long i;
   hash[now]=1;
   for (i=head3[now];i;i=next3[i])
      if (!hash[e3[i]]&&dis[e3[i]]==dis[now]+v3[i])
      {
         add(now,e3[i],0,head2,e2,next2,v2);
         dfs(e3[i]);
      }
      else
         add(e3[i],now,v3[i],head2,e2,next2,v2);
}

void swap(long a,long b)
{
   h2[a].e^=h2[b].e;
   h2[b].e^=h2[a].e;
   h2[a].e^=h2[b].e;
   h2[a].v^=h2[b].v;
   h2[b].v^=h2[a].v;
   h2[a].v^=h2[b].v;
}

void ins2(long *now,long v,long tar)
{
   if (!(*now))
      h2[*now=++tot2]=(struct case2){0,v,tar,0,0};
   else if (h2[h2[*now].l].h<h2[h2[*now].r].h)
   {
      ins2(&h2[*now].l,v,tar);
      if (h2[h2[*now].l].e<h2[*now].e)
         swap(h2[*now].l,*now);
   }
   else
   {
      ins2(&h2[*now].r,v,tar);
      if (h2[h2[*now].r].e<h2[*now].e)
         swap(h2[*now].r,*now);
   }
   h2[*now].h=min(h2[h2[*now].l].h,h2[h2[*now].r].h)+1;
}

void ins(long now,long v)
{
   long pos;
   h[pos=++tot]=h[now];
   if (h[pos].head)
   {
      h2[++tot2]=h2[h[pos].head];
      h[pos].head=tot2;
   }
   if (h[h[pos].l].h<h[h[pos].r].h)
   {
      if (h[h[pos].l].h)
      {
         ins(h[pos].l,v);
         h[pos].l=pos+1;
      }
      else
         h[pos].l=v;
      if (h2[h[h[pos].l].head].e<h2[h[pos].head].e)
      {
         h[h[pos].l].head^=h[pos].head;
         h[pos].head^=h[h[pos].l].head;
         h[h[pos].l].head^=h[pos].head;
      }
   }
   else
   {
      if (h[h[pos].r].h)
      {
         ins(h[pos].r,v);
         h[pos].r=pos+1;
      }
      else
         h[pos].r=v;
      if (h2[h[h[pos].r].head].e<h2[h[pos].head].e)
      {
         h[h[pos].r].head^=h[pos].head;
         h[pos].head^=h[h[pos].r].head;
         h[h[pos].r].head^=h[pos].head;
      }
   }
   h[pos].h=min(h[h[pos].l].h,h[h[pos].r].h)+1;
}

void build(long now,long last)
{
   long i;
   h[now].h=1;
   for (i=head2[now];i;i=next2[i])
      if (v2[i])
         ins2(&h[now].head,dis[e2[i]]+v2[i]-dis[now],e2[i]);
   if (last)
   {
      root[now]=tot+1;
      ins(last,now);
   }
   else
      root[now]=now;
   for (i=head2[now];i;i=next2[i])
      if (!v2[i])
         build(e2[i],root[now]);
}

void down(long x)
{
   long y;
   struct case3 t=heap[x];
   while ((y=(x<<1))<=tot)
   {
      if (y<tot&&heap[y+1].v<heap[y].v)
         y++;
      if (t.v>heap[y].v)
      {
         heap[x]=heap[y];
         x=y;
      }
      else
         break;
   }
   heap[x]=t;
}

void up(long x)
{
   struct case3 t=heap[x];
   while (x>1)
      if (t.v<heap[x>>1].v)
      {
         heap[x]=heap[x>>1];
         x>>=1;
      }
      else
         break;
   heap[x]=t;
}

int main()
{
   long i,j,n,m,k,s,t,now,a,b,c,fa,fb,st=500000,en=500000;
   struct case3 tmp;
   scanf("%ld%ld%ld%ld%ld",&n,&m,&k,&s,&t);
   h2[0].e=oo;
   tot=n;
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld",&a,&b,&c);
      add(b,a,c,head3,e3,next3,v3);
   }
   for (i=1;i<=n;i++)
      dis[i]=oo;
   d[st]=t;
   dis[t]=0;
   while (st<=en)
   {
      now=d[st++];
      hash[now]=0;
      for (i=head3[now];i;i=next3[i])
         if (dis[e3[i]]>dis[now]+v3[i])
         {
            dis[e3[i]]=dis[now]+v3[i];
            if (!hash[e3[i]])
            {
               hash[e3[i]]=1;
               if (dis[e3[i]]<=dis[d[st]])
                  d[--st]=e3[i];
               else
                  d[++en]=e3[i];
            }
         }
   }
   if (dis[s]==oo)
   {
      for (i=1;i<=k;i++)
         puts("NO");
      goto end;
   }
   totm=0;
   dfs(t);
   build(t,0);
   totm=0;
   for (i=1;i<=tot;i++)
      if (h[i].head)
      {
         if (h[h[i].l].head)
            add(h[i].head,h[h[i].l].head,h2[h[h[i].l].head].e-h2[h[i].head].e,head,e,next,v);
         if (h[h[i].r].head)
            add(h[i].head,h[h[i].r].head,h2[h[h[i].r].head].e-h2[h[i].head].e,head,e,next,v);
      }
   for (i=1;i<=tot2;i++)
   {
      if (h2[i].l)
         add(i,h2[i].l,h2[h2[i].l].e-h2[i].e,head,e,next,v);
      if (h2[i].r)
         add(i,h2[i].r,h2[h2[i].r].e-h2[i].e,head,e,next,v);
      if (h[root[h2[i].v]].head)
         add(i,h[root[h2[i].v]].head,h2[h[root[h2[i].v]].head].e,head,e,next,v);
   }
   printf("%ld\n",dis[s]);
   heap[tot=1]=(struct case3){h2[h[root[s]].head].e,h[root[s]].head};
   for (i=2;i<=k&&tot;i++)
   {
      if (i==2&&heap[1].v>=oo)
         break;
      printf("%I64d\n",heap[1].v+dis[s]);
      tmp=heap[1];
      heap[1]=heap[tot--];
      down(1);
      for (j=head[tmp.num];j;j=next[j])
      {
         heap[++tot]=(struct case3){tmp.v+v[j],e[j]};
         up(tot);
      }
   }
   for (;i<=k;i++)
      puts("NO");
   end:
   return 0;
}
