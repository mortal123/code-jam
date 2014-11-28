#include <stdio.h>
#define oo 1000000000

struct case1
{
   long v,c;
}d[30001]={{0,0}};
struct case2
{
   long w,l,c;
}p[15001]={{0,0,0}};
long tot=0;

void up(long now)
{
   struct case1 t;
   while (now>1)
      if (d[now>>1].v>d[now].v)
      {
         t=d[now];
         d[now]=d[now>>1];
         d[now>>1]=t;
         now>>=1;
      }
      else
         break;
}

void down(long now)
{
   long x;
   struct case1 t;
   while ((now<<1)<=tot)
   {
      x=now<<1;
      if (x<tot&&d[x+1].v<d[x].v)
         x++;
      if (d[x].v<d[now].v)
      {
         t=d[x];
         d[x]=d[now];
         d[now]=t;
         now=x;
      }
      else
         break;
   }
}

int main()
{
   long i,j,n,rec,s=0,cost=0,ans=oo;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%ld%ld%ld",&p[i].w,&p[i].l,&p[i].c);
   for (i=n;i>=1;i--)
   {
      d[++tot].v=s+p[i].l;
      d[tot].c=p[i].c;
      cost+=p[i].c;
      up(tot);
      s+=p[i].w;
      while (tot&&d[1].v<s)
      {
         cost-=d[1].c;
         d[1]=d[tot--];
         down(1);
      }
      if (cost<ans)
      {
         ans=cost;
         rec=i;
      }
   }
   s=0;
   for (i=rec;i<=n;i++)
   {
      s+=p[i].w;
      if (s<=p[i].l)
         printf("%ld\n",i);
   }
   return 0;
}
