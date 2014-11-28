#include<stdio.h>

char hash[1000001]={'\0'};
long prime[150001]={0};

int main()
{
   long i,j,n,ans=0,tot=0;
   scanf("%ld",&n);
   for (i=2;i<=n;i++)
   {
      if (!hash[i])
         prime[++tot]=i;
      for (j=1;prime[j]*i<=n;j++)
      {
         hash[prime[j]*i]=1;
         if (i%prime[j]==0)
            break;
      }
   }
   for (i=3;i<=n-2;i++)
      if (!hash[i]&&!hash[i+2])
         ans++;
   printf("%ld\n",ans);
   for (i=3;i<=n-2;i++)
      if (!hash[i]&&!hash[i+2])
         printf("%ld %ld\n",2,i);
   return 0;
}
