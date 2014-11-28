#include <stdio.h>

long link[401][201]={0},f[201]={0},ans[201][201]={0},p[201]={0},hash[201]={0},rec[201]={0};
long n,flag=0;

long match(long now)
{
   long i;
   for (i=1;i<=n;i++)
      if (link[now][i]&&hash[i]!=flag)
      {
         hash[i]=flag;
         if (!f[i]||match(f[i]))
         {
            f[i]=now;
            return 1;
         }
      }
   return 0;
}

int main()
{
   long i,j,k,a,b;
   scanf("%ld%ld",&n,&k);
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&a);
      for (j=1;j<=a;j++)
      {
         scanf("%ld",&b);
         rec[i]=b;
         link[b][i]=link[b+k][i]=1;
      }
   }
   for (i=1;i<=2*k;i++)
   {
      flag++;
      if (!match(i))
         break;
   }
   if (i<=2*k)
      printf("NO\n");
   else
   {
      printf("YES\n");
      for (i=1;i<=n;i++)
      {
         if (!f[i])
            f[i]=rec[i];
         ans[(f[i]-1)%k+1][++p[(f[i]-1)%k+1]]=i;
      }
      for (i=1;i<=k;i++)
      {
         printf("%ld",p[i]);
         for (j=1;j<=p[i];j++)
            printf(" %ld",ans[i][j]);
         printf("\n");
      }
   }
   return 0;
}
