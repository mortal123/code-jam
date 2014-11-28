#include<stdio.h>

int main()
{
   long n;
   scanf("%ld",&n);
   printf("%ld\n",n/3*2+(n%3==2));
   return 0;
}
