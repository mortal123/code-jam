#include <stdio.h>

long h2[1000002]={0},when[1000002]={0},prime[1001]={0},rec[21]={0};
char hash[1001]={0};
long s,p;

long mi(long a,long b)
{
   long t;
   if (!b)
      return 1;
   t=mi(a,b>>1);
   t=(long long)t*t%p;
   if (b&1)
      t=(long long)t*a%p;
   return t;
}

long check(long g)
{
   long i;
   for (i=1;i<=s;i++)
      if (mi(g,(p-1)/rec[i])==1)
         return 0;
   return 1;
}

int main()
{
   long i,j,q,n,t,x,g,flag,tot=0;
   for (i=2;i<=1000;i++)
   {
      if (!hash[i])
         prime[++tot]=i;
      for (j=1;prime[j]*i<=1000;j++)
      {
         hash[prime[j]*i]=1;
         if (i%prime[j]==0)
            break;
      }
   }
   scanf("%ld",&q);
   while (q--)
   {
      scanf("%ld%ld",&n,&p);
      n%=p-1;
      s=0;
      t=p-1;
      for (i=1;i<=tot&&prime[i]*prime[i]<=t;i++)
         if (t%prime[i]==0)
         {
            rec[++s]=prime[i];
            while (t%prime[i]==0)
               t/=prime[i];
         }
      if (t!=1)
         rec[++s]=t;
      for (g=2;!check(g);g++);
      t=x=mi(g,n);
      flag++;
      s=1;
      while (h2[t]!=flag&&h2[t-1]!=flag&&h2[t+1]!=flag)
      {
         h2[t]=flag;
         when[t]=s++;
         t=(long long)t*x%p;
      }
      if (h2[t-1]==flag)
         printf("1 %ld %ld\n",mi(g,when[t-1]),mi(g,s));
      else if (h2[t+1]==flag)
         printf("1 %ld %ld\n",mi(g,s),mi(g,when[t+1]));
      else
         puts("-1");
   }
   return 0;
}
