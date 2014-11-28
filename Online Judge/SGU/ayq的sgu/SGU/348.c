#include <stdio.h>
#define lowbit(a) ((a)&(-(a)))

long check(long long x)
{
   long long a=x,b=x;
   long s=0;
   while (a>1)
   {
      s++;
      a>>=1;
   }
   a=x;
   while (1)
   {
      b=(1LL<<s)+b/lowbit(b)/2;
      if (b<=a)
         break;
   }
   return b==a;
}

int main()
{
   long i;
   long long n;
   scanf("%I64d",&n);
   if (check(n))
      printf("%I64d\n",n);
   else
   {
      while (!check(n-1))
         n-=lowbit(n);
      printf("%I64d\n",n-1);
   }
   return 0;
}
