#include<stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define oo 2100000000

long a[1001][1001]={0};
char str[10001]={'\0'};

int main()
{
   long i,j,k,n,m;
   scanf("%ld%ld\n",&n,&m);
   for (i=1;i<=n;i++)
   {
      gets(str+1);
      k=0;
      for (j=1;j<=m;j++)
      {
         if (str[++k]=='-')
         {
            for (k++;str[k]>='0'&&str[k]<='9';k++)
               a[i][j]=a[i][j]*10+str[k]-'0';
            a[i][j]=-a[i][j];
         }
         else
            for (;str[k]>='0'&&str[k]<='9';k++)
               a[i][j]=a[i][j]*10+str[k]-'0';
      }
   }
   for (j=m;j>=1;j--)
      for (i=n;i>=1;i--)
      {
         if (j<m)
            a[i][j]=min(a[i][j],a[max(i-1,1)][j+1]);
         if (i<n)
            a[i][j]=min(a[i][j],a[i+1][j]);
      }
   for (i=1;i<=n;i++)
   {
      for (j=1;j<m;j++)
         printf("%ld ",a[i][j]);
      printf("%ld\n",a[i][m]);
   }
   return 0;
}
