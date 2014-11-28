#include <stdio.h>

short last[10001][1001]={0};
char f[10001][1001]={'\0'},hash[10001][1001]={'\0'};
long a[10001]={0},d[1001]={0},d2[1001]={0},num[10001]={0};

int main()
{
   long i,j,n,m,t,t2;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
      scanf("%ld",&a[i]);
   f[0][1]=d[1]=t=1;
   for (i=0;i<n;i++)
   {
      t2=0;
      for (j=1;j<=t;j++)
      {
         if (!f[i+1][d[j]*a[i+1]%m])
         {
            hash[i+1][d[j]*a[i+1]%m]=f[i+1][d[j]*a[i+1]%m]=1;
            last[i+1][d[j]*a[i+1]%m]=d[j];
            d2[++t2]=d[j]*a[i+1]%m;
         }
         if (!f[i+1][d[j]])
         {
            f[i+1][d[j]]=1;
            last[i+1][d[j]]=d[j];
            d2[++t2]=d[j];
         }
      }
      for (j=1;j<=t2;j++)
         d[j]=d2[j];
      t=t2;
   }
   t=0;
   for (i=m-1;!f[n][i];i--);
   printf("%ld\n",i);
   for (j=n;j>=1;j--)
   {
      if (hash[j][i])
         num[++t]=j;
      i=last[j][i];
   }
   for (i=t;i>=1;i--)
      printf("%ld%c",num[i],(i==1)?'\n':' ');
   return 0;
}
