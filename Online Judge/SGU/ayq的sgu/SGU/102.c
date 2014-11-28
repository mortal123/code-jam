#include<stdio.h>

long gcd(long a,long b)
{
   return b?gcd(b,a%b):a;
}

int main()
{
   long i,n,ans=1;
   scanf("%ld",&n);
   for (i=2;i<=n;i++)
      if (gcd(i,n)==1)
         ans++;
   printf("%ld\n",ans);
   return 0;
}
