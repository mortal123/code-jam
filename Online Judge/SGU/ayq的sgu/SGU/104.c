#include<stdio.h>

long f[101][101]={0},max[101][101]={0},p[101][101]={0},last[101][101]={0},mat[101][101]={0},ans[101]={0};

int main()
{
   long i,j,k,m,n,t=0;
   scanf("%ld%ld",&m,&n);
   for (i=1;i<=m;i++)
      for (j=1;j<=n;j++)
         scanf("%ld",&mat[i][j]);
   for (i=1;i<=n;i++)
      for (j=i;j<=n-m+i;j++)
      {
         f[i][j]=max[i-1][j-1]+mat[i][j];
         last[i][j]=p[i-1][j-1];
         if (max[i][j-1]>f[i][j]&&j!=i)
         {
            max[i][j]=max[i][j-1];
            p[i][j]=p[i][j-1];
         }
         else
         {
            max[i][j]=f[i][j];
            p[i][j]=j;
         }
      }
   for (i=m,j=p[m][n];i>=1;j=last[i][j],i--)
      ans[++t]=j;
   printf("%ld\n%ld",max[m][n],ans[t]);
   for (t--;t>=1;t--)
      printf(" %ld",ans[t]);
   printf("\n");
   return 0;
}
