#include <stdio.h>
#include <math.h>
#define oo 1000000000
#define pi acos(-1)
#define zero(a) (abb(a)<=1e-8)
#define abb(a) ((a)>0?(a):(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   double v;
   long pos;
}rec[400001]={0,0};
struct case2
{
   long st,en;
}p[100001]={0,0};
long sum[800002]={0},next[800002]={0};
char hash[100001]={0};

double D(long x,long y)
{
   if (x==0)
      return pi/2;
   if (x>0)
      return atan(1.0*y/x);
   return pi+atan(1.0*y/x);
}

void qs1(long x,long y)
{
   long i=x,j=y;
   struct case1 t=rec[(x+y)>>1];
   if (x>=y)
      return;
   rec[(x+y)>>1]=rec[x];
   while (i<j)
   {
      while (i<j&&rec[j].v>t.v)
         j--;
      if (i<j)
         rec[i++]=rec[j];
      while (i<j&&rec[i].v<t.v)
         i++;
      if (i<j)
         rec[j--]=rec[i];
   }
   rec[i]=t;
   qs1(x,i-1);
   qs1(i+1,y);
}

void qs2(long x,long y)
{
   long i=x,j=y;
   struct case2 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&(p[j].st>t.st||p[j].st==t.st&&p[j].en<t.en))
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&(p[i].st<t.st||p[i].st==t.st&&p[i].en>t.en))
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs2(x,i-1);
   qs2(i+1,y);
}

int main()
{
   long i,n,m,a,b,c,d,t=oo,tot=0,s=0,ans=0;
   double x,y;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld%ld%ld",&a,&b,&c,&d);
      x=D(a,b);
      y=D(c,d);
      rec[++tot]=(struct case1){min(x,y),i};
      rec[++tot]=(struct case1){max(x,y),i+n};
   }
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld%ld",&a,&b,&c,&d);
      x=D(a,b);
      y=D(c,d);
      rec[++tot]=(struct case1){min(x,y),i+n+n};
      rec[++tot]=(struct case1){max(x,y),i+n+n+m};
   }
   qs1(1,tot);
   for (i=1;i<=tot;i++)
   {
      if (i==1||!zero(rec[i].v-rec[i-1].v))
         s++;
      if (rec[i].pos<=n)
         p[rec[i].pos].st=s*2-1;
      else if (rec[i].pos<=n+n)
         p[rec[i].pos-n].en=s*2-1;
      else if (rec[i].pos<=n+n+m)
         sum[s*2-1]++;
      else
         sum[s*2]--;
   }
   s=s*2-1;
   for (i=1;i<=s;i++)
   {
      sum[i]+=sum[i-1];
      if (sum[i])
         next[i]=next[i-1];
      else
         next[i]=i;
   }
   qs2(1,n);
   for (i=n;i>=1;i--)
      if (p[i].en>=t)
         hash[i]=1;
      else
         t=p[i].en;
   s=0;
   for (i=1;i<=n;i++)
      if (!hash[i])
         p[++s]=p[i];
   n=s;
   for (i=1;i<=n;i=s+1)
   {
      if (next[p[i].en]<p[i].st)
         break;
      s=i;
      while (s<n&&p[s+1].st<=next[p[i].en])
         s++;
      i=s;
      ans++;
   }
   if (i<=n)
      puts("No solution");
   else
      printf("%ld\n",ans);
   return 0;
}
