#include <stdio.h>

long mat[2006][2006]={0};

int main()
{
   long i,j,n,flag=0;
   scanf("%ld",&n);
   if (n==1)
   {
      printf("0\n0\n");
      goto end;
   }
   if (!(n&1))
   {
      n--;
      flag=1;
   }
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         mat[i][j]=mat[j][i]=(2*i+j-i-3)%n+1;
   if (flag)
      for (i=1;i<=n;i++)
         mat[i][n+1]=mat[n+1][i]=(n+2*i-3)%n+1;
   printf("%ld\n",n);
   for (i=1;i<=n+flag;i++)
      for (j=1;j<=n+flag;j++)
         printf("%ld%c",mat[i][j],(j==n+flag)?'\n':' ');
   end:
       system("pause");
   return 0;
}
