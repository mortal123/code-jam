#include <stdio.h>

double f[101][101][101]={0},g[101][101]={0};

double P(long n,long m)
{
   long i;
   double s=1;
   for (i=n-m+1;i<=n;i++)
      s*=i;
   return s;
}

int main()
{
   long i,j,k,l,n;
   double a=0,b=0;
   scanf("%ld",&n);
   for (i=2;i<=n;i++)
      for (j=2;j<=i;j++)
         for (k=1;k<=i/j;k++)
         {
            if (k>1)
               f[i][j][k]=f[i-j][j][k-1]*P(n-i+j,j)/j/k;
            else
            {
               for (l=2;l<j;l++)
                  f[i][j][k]+=g[i-j][l];
               f[i][j][k]=(f[i][j][k]+(i==j))*P(n-i+j,j)/j;
            }
            g[i][j]+=f[i][j][k];
         }
   for (j=2;j<=n;j++)
      for (k=1;k<=n;k++)
      {
         a+=j*k*f[n][j][k];
         b+=f[n][j][k];    
      }
   printf("%.10lf\n",a/b);
   return 0;
}  
