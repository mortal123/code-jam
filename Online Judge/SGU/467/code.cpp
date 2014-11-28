#include <stdio.h>

int main()
{
   long i=0,q,n;
   while (scanf("%ld",&n)!=EOF)
   {
      printf("Case #%ld: ",++i);
      if (!n)
         puts("0");
      else if (n<=78)
         puts("1");
      else if (n<=95)
         puts("2");
      else if (n<=99)
         puts("3");
      else
         puts("4");
   }
   return 0;
}
