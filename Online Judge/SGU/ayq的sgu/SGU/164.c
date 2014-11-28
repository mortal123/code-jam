#include <stdio.h>
#define oo 1000000000

long f[201][201]={0};

int main()
{
   long i,j,k,n,m;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
      {
         scanf("%ld",&k);
         if (k)
            f[i][j]=((k<=m/2)?1:oo);
      }
   for (k=1;k<=n;k++)
      for (j=1;j<=n;j++)
         for (i=1;i<=n;i++)
            if (f[i][k]+f[k][j]<f[i][j])
               f[i][j]=f[i][k]+f[k][j];
   for (i=1;i<=n;i++)
   {
      for (j=1;j<=n&&f[i][j]<=3;j++);
      if (j<=n)
         break;
   }
   if (i<=n)
   {
      printf("%ld\n",(m+1)/2);
      for (i=m/2+1;i<=m;i++)
         printf("%ld%c",i,(i==m)?'\n':' ');
   }
   else
   {
      printf("%ld\n",m/2);
      for (i=1;i<=m/2;i++)
         printf("%ld%c",i,(i==m/2)?'\n':' ');
   }
   return 0;
}
