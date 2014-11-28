#include <stdio.h>
#include <math.h>

struct case1
{
   long pos,v;
}q[32001]={{0,0}};
long prime[6401]={0},rec[101]={0},ans[1000001]={0};
char hash[32001]={'\0'};
long long x,y;
long p,sq,g=0;

long mi(long k)
{
   long t;
   if (!k)
      return 1;
   t=mi(k>>1);
   t=(long long)t*t%p;
   if (k&1)
      t=(long long)t*g%p;
   return t;
}

long gcd(long a,long b)
{
   return b?gcd(b,a%b):a;
}

void ex_gcd(long a,long b)
{
   if (!b)
   {
      x=1;
      y=0;
   }
   else
   {
      ex_gcd(b,a%b);
      x=y%b;
      y=(1-a*x)/b;
   }
}

void qs1(long x,long y)
{
   long i=x,j=y;
   struct case1 t=q[(x+y)>>1];
   if (x>=y)
      return;
   q[(x+y)>>1]=q[x];
   while (i<j)
   {
      while (i<j&&q[j].v>t.v)
         j--;
      if (i<j)
         q[i++]=q[j];
      while (i<j&&q[i].v<t.v)
         i++;
      if (i<j)
         q[j--]=q[i];
   }
   q[i]=t;
   qs1(x,i-1);
   qs1(i+1,y);
}

void qs2(long x,long y)
{
   long i=x,j=y,t=ans[(x+y)>>1];
   if (x>=y)
      return;
   ans[(x+y)>>1]=ans[x];
   while (i<j)
   {
      while (i<j&&ans[j]>t)
         j--;
      if (i<j)
         ans[i++]=ans[j];
      while (i<j&&ans[i]<t)
         i++;
      if (i<j)
         ans[j--]=ans[i];
   }
   ans[i]=t;
   qs2(x,i-1);
   qs2(i+1,y);
}

long solve(long c)
{
   long a,b=p,left,right,mid,i=0;
   while (1)
   {
      a=mi(i*sq);
      ex_gcd(a,b);
      x=(x*c%b+b)%b;
      left=0;
      right=sq;
      while (left<right-1)
      {
         mid=(left+right)>>1;
         if (q[mid].v>=x)
            right=mid;
         else
            left=mid;
      }
      if (q[right].v==x)
         return i*sq+q[right].pos;
      i++;
   }
}

int main()
{
   long i,j,k,z,t,a,b,c,s=0,tot=0;
   scanf("%ld%ld%ld",&p,&k,&z);
   if (!z)
   {
      tot++;
      goto end;
   }
   sq=sqrt(p);
   for (i=2;i<=sq;i++)
   {
      if (!hash[i])
         prime[++tot]=i;
      for (j=1;prime[j]*i<=sq;j++)
      {
         hash[prime[j]*i]=1;
         if (i%prime[j]==0)
            break;
      }
   }
   t=p-1;
   for (i=1;i<=tot;i++)
      if (t%prime[i]==0)
      {
         rec[++s]=prime[i];
         while (t%prime[i]==0)
            t/=prime[i];
      }
   if (t>1)
      rec[++s]=t;
   while (1)
   {
      g++;
      for (i=1;i<=s&&mi((p-1)/rec[i])!=1;i++);
      if (i>s)
         break;
   }
   q[1]=(struct case1){0,1};
   for (i=2;i<=sq;i++)
      q[i]=(struct case1){i-1,(long long)q[i-1].v*g%p};
   qs1(1,sq);
   a=k;
   b=p-1;
   c=solve(z);
   t=gcd(a,b);
   tot=0;
   if (c%t==0)
   {
      a/=t;
      b/=t;
      c/=t;
      ex_gcd(a,b);
      x=(x*c%b+b)%b;
      for (i=0;i*b+x<p-1;i++)
         ans[++tot]=mi(i*b+x);
   }
   qs2(1,tot);
   end:
   printf("%ld\n",tot);
   for (i=1;i<=tot;i++)
      printf("%ld%c",ans[i],(i==tot)?'\n':' ');
   return 0;
}
