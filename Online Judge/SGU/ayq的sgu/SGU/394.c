#include <stdio.h>
#define lowbit(a) ((a)&(-(a)))

struct case1
{
   long long v;
   long s;
}p[300001]={0,0};
struct case2
{
   long long l,r,y;
   long num,s;
}q[300001]={0,0,0,0,0};
long tree[300001]={0},ans[100001]={0},w[100001]={0},rec[100001]={0};
long tot=0;

void qs1(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&p[j].v>t.v)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i].v<t.v)
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs1(x,i-1);
   qs1(i+1,y);
}

void qs2(long x,long y)
{
   long i=x,j=y;
   struct case2 t=q[(x+y)>>1];
   if (x>=y)
      return;
   q[(x+y)>>1]=q[x];
   while (i<j)
   {
      while (i<j&&(q[j].y>t.y||q[j].y==t.y&&q[j].s<t.s))
         j--;
      if (i<j)
         q[i++]=q[j];
      while (i<j&&(q[i].y<t.y||q[i].y==t.y&&q[i].s>t.s))
         i++;
      if (i<j)
         q[j--]=q[i];
   }
   q[i]=t;
   qs2(x,i-1);
   qs2(i+1,y);
}

void ins(long i,long add)
{
   for (;i<=tot;i+=lowbit(i))
      tree[i]+=add;
}

long sum(long i)
{
   long s=0;
   for (;i;i-=lowbit(i))
      s+=tree[i];
   return s;
}

int main()
{
   long i,n,k;
   long long x,y;
   scanf("%ld%ld",&n,&k);
   for (i=1;i<=n;i++)
   {
      scanf("%I64d%I64d%ld",&x,&y,&w[i]);
      q[i]=(struct case2){x+y,0,y-x,i,-1};
      q[i+n]=(struct case2){0,0,y-x-w[i],i,0};
      q[i+2*n]=(struct case2){0,0,y-x+w[i]+1,i,1};
      p[i*3-2]=(struct case1){q[i].l,i};
      p[i*3-1]=(struct case1){q[i].l-w[i],i+n};
      p[i*3]=(struct case1){q[i].l+w[i],i+2*n};
   }
   qs1(1,3*n);
   for (i=1;i<=3*n;i++)
   {
      if (i==1||p[i].v!=p[i-1].v)
         tot++;
      if (p[i].s<=n)
         q[p[i].s].l=tot;
      else if (p[i].s<=2*n)
         q[p[i].s].l=q[p[i].s+n].l=tot;
      else
         q[p[i].s].r=q[p[i].s-n].r=tot;
   }
   qs2(1,3*n);
   for (i=1;i<=3*n;i++)
      if (q[i].s==-1)
         ans[q[i].num]=sum(q[i].l);
      else if (q[i].s==0)
      {
         ins(q[i].l,1);
         ins(q[i].r+1,-1);
      }
      else
      {
         ins(q[i].l,-1);
         ins(q[i].r+1,1);
      }
   tot=0;
   for (i=1;i<=n;i++)
      if (ans[i]>=k+1)
         rec[++tot]=i;
   printf("%ld\n",tot);
   for (i=1;i<=tot;i++)
      printf("%ld%c",rec[i],(i==tot)?'\n':' ');
   return 0;
}
