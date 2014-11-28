#include<stdio.h>
#define lowbit(a) ((a)&(-(a)))

struct case1
{
   long pos,num;
}p[65538]={{0,0}};
long a[65538]={0},tree[65538]={0};
long tot=0;

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&p[j].num<t.num)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i].num>t.num)
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

void insert(long now)
{
   for (;now<=tot;now+=lowbit(now))
      tree[now]++;
}

long sum(long now)
{
   long s=0;
   for (;now;now-=lowbit(now))
      s+=tree[now];
   return s;
}

int main()
{
   long i,n;
   long long ans=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&p[i].num);
      p[i].pos=i;
   }
   qs(1,n);
   for (i=1;i<=n;i++)
   {
      if (p[i].num!=p[i-1].num||i==1)
         a[p[i].pos]=++tot;
      else
         a[p[i].pos]=a[p[i-1].pos];
   }
   for (i=1;i<=n;i++)
   {
      insert(a[i]);
      ans+=sum(a[i]-1);
   }
   printf("%I64d\n",ans);
   return 0;
}
