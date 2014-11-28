#include <stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   long pos,h;
}p[30001]={{0,0}};
long control[30001]={0},head[30001]={0},f[30001]={0},e[60001]={0},next[60001]={0},ans[30001]={0};
long k,totm=0;

void add(long a,long b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
}

void dfs(long now,long h)
{
   long i;
   p[now].pos=now;
   p[now].h=h;
   for (i=head[now];i;i=next[i])
      if (!f[e[i]])
      {
         f[e[i]]=now;
         dfs(e[i],h+1);
      }
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
      while (i<j&&p[j].h>t.h)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i].h<t.h)
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

long check(long now,long dis)
{
   if (control[now]>=dis)
      return 0;
   if (dis==k||!f[now])
      return now;
   return check(f[now],dis+1);
}

void paint(long now,long dis)
{
   control[now]=max(control[now],dis);
   if (f[now]&&dis)
      paint(f[now],dis-1);
}

int main()
{
   long i,n,a,b,t,tot=0;
   scanf("%ld%ld",&n,&k);
   for (i=1;i<n;i++)
   {
      scanf("%ld%ld",&a,&b);
      add(a,b);
      add(b,a);
   }
   dfs(1,1);
   qs(1,n);
   for (i=1;i<=n;i++)
      control[i]=-1;
   for (i=n;i>=1;i--)
      if (t=check(p[i].pos,0))
      {
         ans[++tot]=t;
         paint(t,k);
      }
   printf("%ld\n",tot);
   for (i=1;i<=tot;i++)
      printf("%ld\n",ans[i]);
   return 0;
}
