#include<stdio.h>

int main()
{
   long i,n;
   scanf("%ld",&n);
   if (n<=8)
      printf("0\n");
   else if (n==9)
      printf("8\n");
   else
   {
      printf("72");
      for (i=1;i<=n-10;i++)
         printf("0");
      printf("\n");
   }
   return 0;
}
