#include<stdio.h>

int main()
{
   long i,j,k,n;
   scanf("%ld",&n);
   printf("%ld",n);
   for (i=3;i<=n;i++)
      for (j=n-i+3;j<=n;j++)
         printf(" %ld",(i-1)*n+j);
   printf("\n%ld",n+1+(n%2));
   for (i=2;i<=n;i++)
      printf(" %ld",(i-1)*n+n-i+2);
   printf("\n");
   for (i=1;i<=n-1;i++)
   {
      printf("%ld",n+2*(i+1)-(n%2==0));
      for (j=1;j<=n-i+1;j++)
         printf(" %ld",(j-1)*n+n-i-j+2);
      printf("\n");
   }
   return 0;
}
