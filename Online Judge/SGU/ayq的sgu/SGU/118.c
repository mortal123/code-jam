#include<stdio.h>

int main()
{
   long k,i,n,t,s,ans;
   scanf("%ld",&k);
   while (k--)
   {
      ans=0;
      s=1;
      scanf("%ld",&n);
      for (i=1;i<=n;i++)
      {
         scanf("%ld",&t);
         s=(t%9*s)%9;
         ans=(ans+s)%9;
      }
      printf("%ld\n",ans+9*(!ans));
   }
   return 0;
}
