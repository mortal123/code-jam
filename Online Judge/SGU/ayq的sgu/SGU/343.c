#include <stdio.h>
#include <math.h>

double tmp[11],v[11],w[11],m[11],s[11],S[11][11],ret[10001][11],price[10001][11];
int qua[11];

int main()
{
   int i,j,a,T,N;
   double sp=0,mp=0,vp=0,t=0;
   scanf("%d%d",&T,&N);
   for (i=1;i<=N;i++)
      scanf("%d",&qua[i]);
   for (i=0;i<=T;i++)
      for (j=1;j<=N;j++)
         scanf("%lf",&price[i][j]);
   for (i=1;i<=N;i++)
   {
      v[i]=price[0][i]*qua[i];
      vp+=v[i];
   }
   for (i=1;i<=N;i++)
      w[i]=v[i]/vp;
   for (i=1;i<=T;i++)
      for (j=1;j<=N;j++)
      {
         ret[i][j]=(price[i-1][j]-price[i][j])/price[i][j];
         m[j]+=ret[i][j];
      }
   for (i=1;i<=N;i++)
   {
      m[i]/=T;
      mp+=m[i]*w[i];
   }
   for (i=1;i<=N;i++)
      for (j=1;j<=N;j++)
      {
         for (a=1;a<=T;a++)
            S[i][j]+=(ret[a][i]-m[i])*(ret[a][j]-m[j]);
         S[i][j]/=T;
      }
   for (i=1;i<=N;i++)
      for (j=1;j<=N;j++)
         tmp[j]+=S[i][j]*w[i];
   for (i=1;i<=N;i++)
      sp+=tmp[i]*w[i];
   printf("%.2lf\n",-vp*(mp-1.644854*sqrt(sp)));
   return 0;
}
