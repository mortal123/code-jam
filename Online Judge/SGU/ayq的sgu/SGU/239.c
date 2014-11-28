#include <stdio.h>

long f[1002][2][2]={0};

int main()
{
   long i,j,k,a,n;
   scanf("%ld",&n);
   f[1][0][0]=f[1][1][0]=1;
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&a);
      for (j=0;j<=1;j++)
         for (k=0;k<=1;k++)
            if (a-j-k>=0&&a-j-k<=1)
               f[i+1][a-j-k][j]+=f[i][j][k];
   }
   printf("%ld\n",f[n+1][0][1]+f[n+1][0][0]);
   return 0;
}
