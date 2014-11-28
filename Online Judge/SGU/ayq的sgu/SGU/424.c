#include<stdio.h>

int main()
{
   long i,n;
   scanf("%ld",&n);
   if (n==1)
      printf("1 0\n");
   else if (n==2)
      printf("2 1\n1 2\n");
   else if (n==3)
      printf("3 3\n1 2\n2 3\n1 3\n");
   else
   {
      printf("%ld %ld\n",n,2*(n-2));
      for (i=2;i<n;i++)
         printf("%ld %ld\n%ld %ld\n",1,i,i,n);
   }
   return 0;
}
