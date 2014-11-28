#include <stdio.h>

double f[8193][7][7]={0},s[14]={0},ans[13]={0};
long count[8193][14]={0};

int main()
{
   long i,j,k,l,n;
   double t;
   scanf("%ld",&n);
   for (i=1;i<=12;i++)
      scanf("%lf",&s[i]);
   for (i=1;i<=n;i++)
   {
      scanf("%lf",&t);
      s[13]+=t;
   }
   s[13]/=n;
   for (i=0;i<=8191;i++)
      for (j=1;j<=13;j++)
         if (!(i&(1<<(j-1))))
         {
            k=(j+11)%13+1;
            count[i][j]=1;
            while (i&(1<<(k-1)))
            {
               count[i][j]++;
               k=(k+11)%13+1;
            }
         }
   f[0][0][0]=1;
   for (i=0;i<=8191;i++)
   {
      for (j=1;j<=13;j++)
         if (!(i&(1<<(j-1))))
            for (k=0;k<=5;k++)
               for (l=0;l<=5;l++)
               {
                  f[i|(1<<(j-1))][k+1][l]+=f[i][k][l]*count[i][j]/13*s[j];
                  f[i|(1<<(j-1))][k][l+1]+=f[i][k][l]*count[i][j]/13*(1-s[j]);
               }
      for (j=1;j<=6;j++)
         ans[j]+=f[i][6][j-1];
      for (j=1;j<=6;j++)
         ans[j+6]+=f[i][6-j][6];
   }
   for (i=1;i<=12;i++)
      printf("%lf\n",ans[i]);
   return 0;
}
