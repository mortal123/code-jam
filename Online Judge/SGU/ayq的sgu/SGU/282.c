#include <stdio.h>

long f[60]={0},c[60]={0},fc[60]={0},x[60]={0},g[60][60]={0};
long n,m,p,ans=0;

long gcd(long a,long b)
{
   return b?gcd(b,a%b):a;
}

long quick(long a,long b)
{
   long t;
   if(!b)
      return 1;
   t=quick(a,b>>1);
   t=(long long)t*t%p;
   if(b&1)
      t=(long long)t*a%p;
   return t;
}

void cal(long tot)
{
   long i,j,sum=0,add=1;
   for(i=1;i<=tot;i++)
   {
      sum+=i/2*x[i]+i*x[i]*(x[i]-1)/2;
      for(j=i+1;j<=tot;j++)
         sum+=x[i]*x[j]*g[i][j];
      for(j=1;j<=x[i];j++)
         add=(long long)add*f[i]%p;
      add=(long long)add*fc[x[i]]%p;
   }
   add=(long long)add*quick(m,sum)%p;
   ans=(ans+add)%p;
}

void dfs(long now,long sum)
{
   long i;
   if(sum==n)
      cal(now-1);
   else if (now<=n)
      for(i=0;i*now+sum<=n;i++)
      {
         x[now]=i;
         dfs(now+1,i*now+sum);
      }
}

int main()
{
   long i,j;
   scanf("%ld%ld%ld",&n,&m,&p);
   for(i=1;i<=n;i++)
      for(j=1;j<=n;j++)
         g[i][j]=gcd(i,j);
   c[0]=fc[0]=1;
   for(i=1;i<=n;i++)
   {
      f[i]=quick(i,p-2);
      c[i]=(long long)i*c[i-1]%p;
      fc[i]=quick(c[i],p-2);
   }
   dfs(1,0);
   printf("%ld\n",ans);
   return 0;
}
