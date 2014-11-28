#include<stdio.h>

int main()
{
   long n;
   scanf("%ld",&n);
   if (n==1)
      printf("8\n");
   else if (n%6==1)
      printf("4\n");
   else if (n%3==1)
      printf("3\n");
   else
      printf("1\n");
   return 0;
}
