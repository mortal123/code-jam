#include <stdio.h>
#define lowbit(a) ((a)&(-(a)))

int main()
{
   long long i,a,b,t,ra=0,rb=0;
   scanf("%I64d%I64d",&a,&b);
   for (i=2;i*i<=a&&a%i;i++);
   if (i*i>a)
   {
      printf("Impossible\n");
      goto end;
   }
   for (i=2;i*i<=b&&b%i;i++);
   if (i*i>b)
   {
      printf("Impossible\n");
      goto end;
   }
   if (a&1)
   {
      for (i=3;i*i<=a&&a%i;i+=2);
      ra=i;
      a+=i;
   }
   if (b&1)
   {
      for (i=3;i*i<=b&&b%i;i+=2);
      rb=i;
      b-=i;
   }
   if (a>b)
   {
      printf("Impossible\n");
      goto end;
   }
   if (ra)
      printf("%I64d\n",a-ra);
   while (a!=b)
   {
      printf("%I64d\n",a);
      t=lowbit(a);
      if (t==a)
         t>>=1;
      while (a+t>b)
         t>>=1;
      a+=t;
   }
   printf("%I64d\n",a);
   if (rb)
      printf("%I64d\n",b+rb);
   end:
   return 0;
}
