#include<stdio.h>

long a[11][11]={0},b[11]={0};
char hash[11][101]={'\0'};

int main()
{
   long i,j,k,n,m,l,ans=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&a[i][0]);
      for (j=1;j<=a[i][0];j++)
      {
         scanf("%ld",&a[i][j]);
         hash[i][a[i][j]]=1;
      }
   }
   for (i=1;i<=m;i++)
   {
      scanf("%ld",&l);
      for (j=1;j<=l;j++)
         scanf("%ld",&b[j]);
      ans=0;
      for (j=1;j<=n;j++)
      {
         for (k=1;k<=l;k++)
            if (b[k]>0&&!hash[j][b[k]]||b[k]<0&&hash[j][-b[k]])
               break;
         if (k>l)
            ans++;
      }
      printf("%ld\n",ans);
      for (j=1;j<=n;j++)
      {
         for (k=1;k<=l;k++)
            if (b[k]>0&&!hash[j][b[k]]||b[k]<0&&hash[j][-b[k]])
               break;
         if (k>l)
         {
            for (k=0;k<a[j][0];k++)
               printf("%ld ",a[j][k]);
            printf("%ld\n",a[j][a[j][0]]);
         }
      }
   }
   return 0;
}
