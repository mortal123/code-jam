#include <stdio.h>

long mat[51][2]={0};

int main()
{
   long i,n;
   scanf("%ld",&n);
   for (i=1;i<=n/2;i++)
      mat[i][i&1]=i*2-1;
   for (i=n/2;i>=1;i--)
      mat[i][!(i&1)]=n-2*i+2;
   if (!(n&2))
      for (i=1;i<=n/4;i++)
      {
         mat[i][0]^=mat[i][1];
         mat[i][1]^=mat[i][0];
         mat[i][0]^=mat[i][1];
      }
   for (i=1;i<=n/2;i++)
      printf("%ld %ld%c",mat[i][0],mat[i][1],(i==n/2)?'\n':' ');
   return 0;
}
