#include <stdio.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

long a[10001]={0},f[10001][101]={0};

int main()
{
   long i,j,n,m,ans=oo;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&a[i]);
      f[i][0]=oo;
      for (j=1;j<m;j++)
      {
         f[i][j]=f[i][j-1];
         if (j<=i)
            f[i][j]=min(f[i][j],f[i-j][m-j]+a[i]);
      }
   }
   for (i=n;i>=n-m+2;i--)
      ans=min(ans,f[i][m+i-n-1]);
   printf("%ld\n",ans);
   return 0;
}
