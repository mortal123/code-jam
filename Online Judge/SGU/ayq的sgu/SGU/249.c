#include<stdio.h>

long grey[1050001]={0};

int main()
{
   long i,j,n,m,a,b;
   scanf("%ld%ld",&n,&m);
   for (i=0;i<(1<<n)||i<(1<<m);i++)
      for (j=0;(1<<j)<=i;j++)
         if (!(i&(1<<j))^!(i&(1<<(j+1))))
            grey[i]+=(1<<j);
   for (i=0;i<(1<<n);i++)
   {
      for (j=0;j<(1<<m);j++)
      {
         printf("%ld",grey[j]+(grey[i]<<m));
         if (j<(1<<m)-1)
            printf(" ");
      }
      printf("\n");
   }
   return 0;
}
