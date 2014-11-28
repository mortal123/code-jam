#include <stdio.h>

long a[10001]={0},s[10001]={0},num[210001]={0};
long long s2[10001]={0};

long gcd(long a,long b)
{
   return b?gcd(b,a%b):a;
}

int main()
{
   long i,j,n,la=1,ls=1;
   a[1]=1;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      num[gcd(i,n)]++;
   for (i=1;i<=n||num[i];i++)
   {
      for (j=1;j<=la+1;j++)
      {
         a[j]=(a[j]<<1);
         if (a[j-1]>=1000000000)
         {
            a[j]++;
            a[j-1]-=1000000000;
         }
      }
      if (a[la+1])
         la++;
      if (num[i]&1)
      {
         for (j=1;j<=la+1||j<=ls;j++)
         {
            s[j]+=a[j];
            if (s[j-1]>=1000000000)
            {
               s[j]++;
               s[j-1]-=1000000000;
            }
         }
         if (ls<la+1)
            ls=la+1;
         while (!s[ls])
            ls--;
      }
      num[i+1]+=num[i]/2;
   }
   for (j=ls;j>=0;j--)
   {
      s2[j]=s[j]+(long long)s2[j+1]%n*1000000000;
      s2[j+1]/=n;
   }
   while (!s2[ls])
      ls--;
   printf("%I64d",s2[ls]);
   for (i=ls-1;i>=1;i--)
      printf("%.9I64d",s2[i]);
   printf("\n");
   return 0;
}
