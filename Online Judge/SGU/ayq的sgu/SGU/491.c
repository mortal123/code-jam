#include <stdio.h>

long mat[100001][301]={0},p[100001]={0},hash[100001]={0};

int main()
{
   long i,j,k,t,n,ans=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      for (j=1;j*j<=i;j++)
         if (!(i%j))
         {
            mat[i][++p[i]]=j;
            if (j*j!=i)
               mat[i][++p[i]]=i/j;
         }
   for (i=1;i<=((n-1)>>1);i++)
      for (j=1;i*j<=n;j++)
      {
         t=n-i*j;
         for (k=1;k<=p[t];k++)
            if (mat[t][k]>i&&hash[mat[t][k]]!=i)
            {
               ans++;
               hash[mat[t][k]]=i;
            }
      }
   printf("%ld\n",ans);
   return 0;
}
