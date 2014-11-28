#include<stdio.h>
#define lowbit(a) ((a)&(-(a)))

long gcd(long a,long b)
{
   return b?gcd(b,a%b):a;
}

int main()
{
   long a,b,s=0,t;
   scanf("%ld%ld",&a,&b);
   if (!a||!b)
      printf("0\n");
   else
   {
      t=gcd(a,b);
      a/=t;
      b/=t;
      if (lowbit(a+b)!=a+b)
         printf("-1");
      else
      {
         t=a+b;
         while (!(t&1))
         {
            s++;
            t>>=1;
         }
         t=a;
         while (!(t&1))
         {
            s--;
            t>>=1;
         }
         printf("%ld\n",s);
      }
   }
   return 0;
}
