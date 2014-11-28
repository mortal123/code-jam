#include <stdio.h>

int main()
{
   int n,i=0;
   while (scanf("%d",&n)!=EOF)
   {
      printf("Case #%d: ",++i);
      if (n==1)
         puts("-1/1");
      else
      {
         n=(n/4*2+n%4-(n%4==3));
         if (n>2)
            putchar('-');
         printf("%d/%d\n",(n-2)/(1+!(n&1)),n/(1+!(n&1)));
      }
   }
   return 0;
}
