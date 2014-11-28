#include<stdio.h>

char hash1[202][10001]={'\0'},hash2[202][10001]={'\0'};
long v[201]={0},ans[201]={0};

int main()
{
   long i,j,n,x,tot=0;
   scanf("%ld%ld",&n,&x);
   hash1[0][0]=hash2[n+1][0]=1;
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&v[i]);
      for (j=0;j<=x;j++)
      {
         if (j>=v[i])
         {
            if (hash1[i-1][j-v[i]]|hash1[i-1][j])
               hash1[i][j]=1;
         }
         else
            hash1[i][j]=hash1[i-1][j];
      }
   }
   for (i=n;i>=1;i--)
      for (j=0;j<=x;j++)
      {
         if (j>=v[i])
         {
            if (hash2[i+1][j-v[i]]|hash2[i+1][j])
               hash2[i][j]=1;
         }
         else
            hash2[i][j]=hash2[i+1][j];
      }
   for (i=1;i<=n;i++)
   {
      for (j=0;j<=x&&!(hash1[i-1][j]&hash2[i+1][x-j]);j++);
      if (j>x)
         ans[++tot]=v[i];
   }
   printf("%ld\n",tot);
   if (tot)
   {
      for (i=1;i<tot;i++)
         printf("%ld ",ans[i]);
      printf("%ld\n",ans[tot]);
   }
   return 0;
}
