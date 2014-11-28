#include<stdio.h>

long mat[71][102]={0};

int main()
{
   long i,j,k,l,n=0,m;
   long long a,ans=0;
   scanf("%ld",&m);
   for (i=1;i<=m;i++)
   {
      scanf("%I64d",&a);
      j=0;
      while (a)
      {
         mat[++j][i]=(a&1);
         a>>=1;
      }
      if (j>n)
         n=j;
   }
   for (i=1;i<=n;i++)
      mat[i][m+1]=1;
   for (i=n;i>=1;i--)
   {
      for (j=1;j<=m&&!mat[i][j];j++);
      if (j<=m)
      {
         for (k=i-1;k>=1;k--)
            if (mat[k][j])
               for (l=1;l<=m+1;l++)
                  mat[k][l]^=mat[i][l];
         ans+=(1LL<<(i-1));
      }
      else if (!mat[i][m+1])
         ans+=(1LL<<(i-1));
   }
   printf("%I64d\n",ans);
   return 0;
}
