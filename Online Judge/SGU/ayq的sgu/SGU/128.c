#include <stdio.h>
#define lowbit(a) ((a)&(-(a)))

struct case1
{
   long x,y,num;
}p[10001]={{0,0,0}};
struct case2
{
   long y1,y2,pos,sign;
}q[15001]={{0,0,0,0}};
long tree[20003]={0},f[10001]={0};

void qs1(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&(p[j].y>t.y||p[j].y==t.y&&p[j].x>t.x))
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&(p[i].y<t.y||p[i].y==t.y&&p[i].x<t.x))
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
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&(p[j].x>t.x||p[j].x==t.x&&p[j].y>t.y))
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&(p[i].x<t.x||p[i].x==t.x&&p[i].y<t.y))
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs2(x,i-1);
   qs2(i+1,y);
}

void qs3(long x,long y)
{
   long i=x,j=y;
   struct case2 t=q[(x+y)>>1];
   if (x>=y)
      return;
   q[(x+y)>>1]=q[x];
   while (i<j)
   {
      while (i<j&&q[j].pos>t.pos)
         j--;
      if (i<j)
         q[i++]=q[j];
      while (i<j&&q[i].pos<t.pos)
         i++;
      if (i<j)
         q[j--]=q[i];
   }
   q[i]=t;
   qs3(x,i-1);
   qs3(i+1,y);
}

void ins(long i,long add)
{
   for (;i<=20002;i+=lowbit(i))
      tree[i]+=add;
}

long que(long i)
{
   long s=0;
   for (;i;i-=lowbit(i))
      s+=tree[i];
   return s;
}

long getf(long now)
{
   if (f[now]==now)
      return now;
   return f[now]=getf(f[now]);
}

int main()
{
   long i,n,l,r,s=0,ans=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      p[i].num=f[i]=i;
      scanf("%ld%ld",&p[i].x,&p[i].y);
      p[i].x+=10001;
      p[i].y+=10001;
   }
   qs1(1,n);
   for (l=1;l<=n;l=r+1)
   {
      r=l;
      while (r<n&&p[r+1].y==p[r].y)
         r++;
      if (!((r-l)&1))
      {
         ans=0;
         goto end;
      }
      for (i=l;i<r;i+=2)
      {
         ans+=p[i+1].x-p[i].x;
         q[++s].y1=p[i].y;
         q[s].pos=p[i].x;
         q[++s].y1=p[i].y;
         q[s].pos=p[i+1].x;
         q[s].sign=1;
         f[getf(p[i].num)]=getf(p[i+1].num);
      }
   }
   qs2(1,n);
   for (l=1;l<=n;l=r+1)
   {
      r=l;
      while (r<n&&p[r+1].x==p[r].x)
         r++;
      if (!((r-l)&1))
      {
         ans=0;
         goto end;
      }
      for (i=l;i<r;i+=2)
      {
         ans+=p[i+1].y-p[i].y;
         q[++s].y1=p[i].y;
         q[s].y2=p[i+1].y;
         q[s].pos=p[i].x;
         q[s].sign=2;
         f[getf(p[i].num)]=getf(p[i+1].num);
      }
   }
   for (i=1;i<n;i++)
      if (getf(i)!=getf(i+1))
      {
         ans=0;
         goto end;
      }
   qs3(1,s);
   for (i=1;i<=s;i++)
      if (q[i].sign==0)
         ins(q[i].y1,1);
      else if (q[i].sign==1)
         ins(q[i].y1,-1);
      else if (que(q[i].y2-1)-que(q[i].y1)>0)
      {
         ans=0;
         goto end;
      }
   end:
   printf("%ld\n",ans);
   return 0;
}
