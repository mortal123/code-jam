#include <stdio.h>
#define oo 1000000001
#define lowbit(a) ((a)&(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   int x,y;
}p[100001],tp[100001];
struct case2
{
   int st,en,s,flag;
}q[400001];
int tree[100001],hash[100001],h[100001],pos[100001],ST[21][100001];
long long ans=0;
int sx=0,flag=0;

void qs(int x,int y)
{
   int i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&(p[j].x>t.x||p[j].x==t.x&&p[j].y<t.y))
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&(p[i].x<t.x||p[i].x==t.x&&p[i].y>t.y))
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

int stmin(int st,int en)
{
   int t=1,tot=0;
   while (t<<1<en-st+1)
   {
      t<<=1;
      tot++;
   }
   return min(ST[tot][st],ST[tot][en-(1<<tot)+1]);
}

void add(int i,int v)
{
   for (;i<=sx;i+=lowbit(i))
      if (hash[i]!=flag||tree[i]<v)
      {
         hash[i]=flag;
         tree[i]=v;
      }
}

int que(int i)
{
   int s=0;
   for (;i;i-=lowbit(i))
      if (hash[i]==flag)
         s=max(s,tree[i]);
   return s;
}

void build(int now,int st,int en)
{
   int mid=(st+en)>>1;
   q[now].st=st;
   q[now].en=en;
   if (st<en-1)
   {
      build(now<<1,st,mid);
      build((now<<1)+1,mid,en);
   }
}

void maintain(int now)
{
   if (q[now].flag)
   {
      q[now<<1].flag=q[(now<<1)+1].flag=1;
      q[now<<1].s=q[(now<<1)+1].s=q[now].flag=0;
   }
}

void ins(int now,int st,int en,int add)
{
   int mid=(q[now].st+q[now].en)>>1;
   if (st>=en)
      return;
   if (q[now].st==st&&q[now].en==en)
   {
      q[now].flag=1;
      q[now].s=add;
   }
   else
   {
      maintain(now);
      if (en<=mid)
         ins(now<<1,st,en,add);
      else if (mid<=st)
         ins((now<<1)+1,st,en,add);
      else
      {
         ins(now<<1,st,mid,add);
         ins((now<<1)+1,mid,en,add);
      }
      q[now].s=q[now<<1].s+q[(now<<1)+1].s;
   }
}

int ask(int now,int st,int en)
{
   int mid=(q[now].st+q[now].en)>>1;
   if (st>=en)
      return;
   if (q[now].st==st&&q[now].en==en)
      return q[now].s;
   else
   {
      maintain(now);
      if (en<=mid)
         return ask(now<<1,st,en);
      else if (mid<=st)
         return ask((now<<1)+1,st,en);
      return ask(now<<1,st,mid)+ask((now<<1)+1,mid,en);
   }
}

void work(int st,int en)
{
   int i,j,t,tot=0,s=0,mid=(st+en)>>1;
   if (st==en)
      return;
   work(st,mid);
   work(mid+1,en);
   j=mid+1;
   for (i=st;i<=mid;i++)
   {
      while (j<=en&&p[j].y<=p[i].y)
      {
         pos[++s]=j;
         tp[s]=p[j++];
      }
      pos[++s]=i;
      tp[s]=p[i];
   }
   while (j<=en)
   {
      pos[++s]=j;
      tp[s]=p[j++];
   }
   s=0;
   for (i=1;i<=en-st+1;i++)
      h[pos[i]]=(s+=(i==1||tp[i].y>tp[i-1].y));
   t=1;
   while (t<<1<=s)
   {
      t<<=1;
      tot++;
   }
   for (i=1;i<=s;i++)
      ST[0][i]=oo;
   for (i=mid+1;i<=en;i++)
      ST[0][h[i]]=min(ST[0][h[i]],p[i].x);
   for (i=1;i<=tot;i++)
      for (j=1;j+(1<<i)-1<=s;j++)
         ST[i][j]=min(ST[i-1][j],ST[i-1][j+(1<<i-1)]);
   flag++;
   j=mid+1;
   q[1].flag=0;
   for (i=st;i<=mid;i++)
   {
      t=que(sx-p[i].x+1)+1;
      add(sx-p[i].x+1,h[i]);
      while (j<=en&&p[j].y<=p[i].y)
      {
         ins(1,p[j].x,sx+1,0);
         ins(1,p[j].x,p[j].x+1,1);
         j++;
      }
      if (h[i]>=t&&(t=stmin(t,h[i]))<=sx)
         ans+=ask(1,t,sx+1);
   }
   for (i=st;i<=en;i++)
      p[i]=tp[i-st+1];
}

int main()
{
   int i,t1,t2,n;
   scanf("%d",&n);
   for (i=1;i<=n;i++)
      scanf("%d%d",&p[i].x,&p[i].y);
   qs(1,n);
   for (i=1;i<=n;i++)
   {
      t1=(sx+=(i==1||p[i].x>t2));
      t2=p[i].x;
      p[i].x=t1;
   }
   build(1,1,sx+1);
   for (i=2;i<=n;i++)
      ans-=(p[i].x==p[i-1].x);
   work(1,n);
   for (i=1;i<=n;i++)
      p[i].y=-p[i].y;
   qs(1,n);
   work(1,n);
   for (i=2;i<=n;i++)
      ans-=(p[i].y==p[i-1].y);
   printf("%I64d\n",ans);
   return 0;
}
