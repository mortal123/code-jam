#include <stdio.h>

long long f[25][10][2]={0};

int main()
{
   long i,j,k,n;
   long long ans=0;
   scanf("%ld",&n);
   f[0][0][0]=1;
   for (i=1;i<=n;i++)
      for (j=0;j<=9;j++)
      {
         for (k=0;k<=j;k++)
            f[i][j][0]+=f[i-1][k][0];
         for (k=j+1;k<=9;k++)
            f[i][j][1]+=f[i-1][k][0];
         for (k=j;k<=9;k++)
            f[i][j][1]+=f[i-1][k][1];
      }
   for (i=0;i<=9;i++)
      ans+=f[n][i][0]+f[n][i][1];
   printf("%I64d\n",ans);
   return 0;
}
