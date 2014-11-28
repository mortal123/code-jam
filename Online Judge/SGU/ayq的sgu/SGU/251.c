#include <stdio.h>

int main()
{
   long n,r1,r2,r3;
   scanf("%ld",&n);
   if (n==3)
   {
      scanf("%ld%ld",&r1,&r2);
      printf("YES\n0 %ld\n-1 0\n1 0\n",r1+2*r2);
   }
   else if (n==4)
   {
      scanf("%ld%ld%ld",&r1,&r2,&r3);
      if (r1==r2)
         printf("YES\n%.4lf %ld\n%.4lf %ld\n-1 0\n1 0\n",-1.0*(2*r1+r3)/(r1+2*r3),r1+2*r3,1.0*(2*r1+r3)/(r1+2*r3),r1+2*r3);
      else if (r1+r2==2*r3)
         printf("YES\n0 %ld\n0 %ld\n-1 0\n1 0\n",r1+2*r3,-r2-2*r3);
      else
         printf("NO\n");
   }
   else
      printf("NO\n");
  return 0;
}
