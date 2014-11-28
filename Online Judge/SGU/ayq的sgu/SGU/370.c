#include<stdio.h>

long min[1000001]={0},l[21]={0};
long tot,m;
long long ans;

long count(long now,long sum,long sign)
{
   if (now>tot)
   {
      if (sign)
         ans+=(m-1)/sum;
      else
         ans-=(m-1)/sum;
   }
   else
   {
      count(now+1,sum*l[now],!sign);
      count(now+1,sum,sign);
   }
}

int main()
{
   long i,j,k,t,n;
   scanf("%ld%ld",&n,&m);
   if (n>m)
   {
      t=n;
      n=m;
      m=t;
   }
   ans=(n>1)+(m>1);
   min[1]=1;
   for (i=2;i<=n;i++)
      if (!min[i])
         for (j=1;i*j<=n;j++)
            if (!min[i*j])
               min[i*j]=i;
   for (i=2;i<=n;i++)
   {
      tot=0;
      for (j=i-1;min[j]!=1;j/=min[j])
      {
         for (k=1;k<=tot&&l[k]!=min[j];k++);
         if (k>tot)
            l[++tot]=min[j];
      }
      count(1,1,1);
   }
   printf("%I64d\n",ans);
   return 0;
}
