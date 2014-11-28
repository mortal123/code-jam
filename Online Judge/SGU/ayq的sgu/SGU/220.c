#include<stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))

long s1[21]={0},s2[21]={0};
long long f1[21][101]={0},f2[21][101]={0};

int main()
{
   long i,j,t,n,m,s=0,tot1=0,tot2=0;
   long long ans=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<2*n;i++)
   {
      s=0;
      for (j=1;j<=n;j++)
         if (i-j+1>=1&&i-j+1<=n)
            s++;
      if (i&1)
         s1[++tot1]=s;
      else
         s2[++tot2]=s;
   }
   for (i=1;i<tot1;i++)
      for (j=i+1;j<=tot1;j++)
         if (s1[j]<s1[i])
         {
            t=s1[j];
            s1[j]=s1[i];
            s1[i]=t;
         }
   for (i=1;i<tot2;i++)
      for (j=i+1;j<=tot2;j++)
         if (s2[j]<s2[i])
         {
            t=s2[j];
            s2[j]=s2[i];
            s2[i]=t;
         }
   f1[0][0]=1;
   for (i=1;i<=tot1;i++)
   {
      f1[i][0]=1;
      for (j=1;j<=m;j++)
         f1[i][j]=f1[i-1][j]+f1[i-1][j-1]*max(s1[i]-j+1,0);
   }
   f2[0][0]=1;
   for (i=1;i<=tot2;i++)
   {
      f2[i][0]=1;
      for (j=1;j<=m;j++)
         f2[i][j]=f2[i-1][j]+f2[i-1][j-1]*max(s2[i]-j+1,0);
   }
   for (i=0;i<=m;i++)
      ans+=f1[tot1][i]*f2[tot2][m-i];
   printf("%I64d\n",ans);
   return 0;
}
