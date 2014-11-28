#include <stdio.h>

long gcd(long a,long b)
{
   return b?gcd(b,a%b):a;
}

int main()
{
   long n,num;
   scanf("%ld",&n);
   num=gcd(n,n/2+2);
   printf("%ld\n",n/num/2*num+1);
   return 0;
}
