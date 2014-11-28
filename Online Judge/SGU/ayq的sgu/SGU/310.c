#include<stdio.h>
#define lowbit(a) ((a)&(-(a)))

long long f[61][32769]={0};
long num[32769]={0};

int main()
{
   long i,j,n,m,k;
   long long ans=0;
   scanf("%ld%ld%ld",&n,&m,&k);
   f[0][0]=1;
   for (i=0;i<(1<<m);i++)
      for (j=i;j;j-=lowbit(j))
         num[i]++;
   for (i=1;i<=n;i++)
      for (j=0;j<(1<<m);j++)
         if (num[j]>=k||i<m)
         {
            f[i][j]=f[i-1][(j>>1)+(1<<(m-1))];
            if (num[j]>k||!(j&1)||i<=m)
               f[i][j]+=f[i-1][j>>1];
         }
   for (i=0;i<(1<<m);i++)
      ans+=f[n][i];
   printf("%I64d\n",ans);
   return 0;
}
