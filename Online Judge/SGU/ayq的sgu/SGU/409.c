#include<stdio.h>

long map[401][401]={0};

int main()
{
   long i,j,n,k,s;
   scanf("%ld%ld",&n,&k);
   for (i=1;i<=k;i++)
   {
      s=i;
      for (j=1;j<=n*n;j++)
      {
         map[j][s]=1;
         s=(s+n-1+(j%n==0))%(n*n)+1;
      }
   }
   for (i=1;i<=n*n;i++)
   {
      for (j=1;j<=n*n;j++)
      {
         if (map[i][j])
            printf("*");
         else
            printf(".");
      }
      printf("\n");
   }
   return 0;
}
