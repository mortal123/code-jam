#include<stdio.h>

long prime[26]={0},z[101]={0},time[101]={0};
char hash[101]={'\0'};

int main()
{
   long i,j,n,m,k,x,t,flag,p=0,tot=0,ans=0;
   for (i=2;i<=100;i++)
   {
      if (!hash[i])
         prime[++tot]=i;
      for (j=1;prime[j]*i<=100;j++)
      {
         hash[prime[j]*i]=1;
         if (i%prime[j]==0)
            break;
      }
   }
   scanf("%ld%ld%ld",&n,&m,&k);
   t=k;
   for (i=1;t>1&&i<=25&&prime[i]*prime[i]<=k;i++)
      if (t%prime[i]==0)
      {
         z[++p]=prime[i];
         while (t%prime[i]==0)
         {
            time[p]++;
            t/=prime[i];
         }
      }
   if (t>1)
   {
      z[++p]=t;
      time[p]=1;
   }
   while (n--)
   {
      scanf("%ld",&x);
      flag=1;
      for (i=1;i<=p;i++)
      {
         t=0;
         while (x%z[i]==0)
         {
            x/=z[i];
            t++;
         }
         if (t*m<time[i])
         {
            flag=0;
            break;
         }
      }
      ans+=flag;
   }
   printf("%ld\n",ans);
   return 0;
}
