#include <stdio.h>

long work(long a,long least)
{
   long i,s=0;
   if (!a)
      return 1;
   for (i=least;i<=a;i++)
      s+=work(a-i,i);
   return s;
}

int main()
{
   long long n,ans=1;
   long i,sq,s=0;
   scanf("%I64d",&n);
   sq=sqrt(n+1e-8);
   for (i=2;i<=sq;i++)
      if (n%i==0)
      {
         s=0;
         while (n%i==0)
         {
            s++;
            n/=i;
         }
         ans*=work(s,1);
      }
   printf("%I64d\n",ans);
   return 0;
}
