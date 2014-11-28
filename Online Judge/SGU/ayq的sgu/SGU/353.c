#include <stdio.h>

int main()
{
   long i,n,k1,k2,p1,p2,p3;
   scanf("%ld%ld%ld%ld%ld%ld",&n,&k1,&k2,&p1,&p2,&p3);
   if (n<p1)
      printf("0\n");
   else
   {
      for (i=1;n>0;i++)
         if (i==k1)
            n-=p1;
         else if (i<=k1+k2&&i>k1)
            n-=p2;
         else if (i>k1+k2)
            n-=p3;
      printf("%ld\n",i-1);
   }
   return 0;
}
