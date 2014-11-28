#include<stdio.h>

long mid(long a,long b,long c)
{
   if (b>=a&&c<=a||b<=a&&c>=a)
      return a;
   if (a>=b&&c<=b||a<=b&&c>=b)
      return b;
   return c;
}

int main()
{
   long a,b,c,x,y,z;
   scanf("%ld%ld%ld",&a,&b,&c);
   x=mid(a,b,c);
   scanf("%ld%ld%ld",&a,&b,&c);
   y=mid(a,b,c);
   scanf("%ld%ld%ld",&a,&b,&c);
   z=mid(a,b,c);
   printf("%ld\n",mid(x,y,z));
   return 0;
}
