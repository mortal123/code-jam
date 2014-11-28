#include <stdio.h>

long mat[202][202]={0},rec[202][202]={0};
char hash[201]={'\0'};
long n;

long work()
{
   long i,j,k,a,b,t,ans=0;
   for (i=1;i<=n;i++)
   {
      for (a=i;a<=n;a++)
         for (b=i;b<=n;b++)
            if (mat[a][b])
               goto out;
      out:;
      if (a>n)
         break;
      for (j=1;j<=n+1;j++)
      {
         t=mat[j][i];
         mat[j][i]=mat[j][b];
         mat[j][b]=t;
      }
      for (j=i;j<=n+1;j++)
      {
         t=mat[i][j];
         mat[i][j]=mat[a][j];
         mat[a][j]=t;
      }
      for (j=i+1;j<=n;j++)
         if (mat[j][i])
            for (k=i;k<=n+1;k++)
               mat[j][k]^=mat[i][k];
   }
   for (j=n;j>i&&!mat[j][n+1];j--);
   if (j>i)
      return 0;
   for (i--;i>=1;i--)
   {
      mat[0][i]=mat[i][n+1];
      for (j=n;j>i;j--)
         mat[0][i]^=mat[0][j]*mat[i][j];
   }
   for (i=1;i<=n;i++)
      if (mat[0][i])
      {
         hash[mat[n+1][i]]=1;
         ans++;
      }
   printf("%ld\n",ans);
   j=0;
   for (i=1;i<=n;i++)
      if (hash[i])
         printf("%ld%c",i,((++j)==ans)?'\n':' ');
   return 1;
}

int main()
{
   long i,j,a,b;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      mat[n+1][i]=i;
      scanf("%ld",&a);
      for (j=1;j<=a;j++)
      {
         scanf("%ld",&b);
         mat[b][i]=1;
      }
   }
   for (i=1;i<=n;i++)
      scanf("%ld",&mat[i][n+1]);
   for (i=1;i<=n+1;i++)
      for (j=1;j<=n+1;j++)
         rec[i][j]=mat[i][j];
   if (!work())
   {
      for (i=0;i<=n+1;i++)
      {
         for (j=1;j<=n+1;j++)
            mat[i][j]=rec[i][j];
         mat[i][n+1]^=1;
      }
      if (!work())
         printf("-1\n");
   }
   return 0;
}
