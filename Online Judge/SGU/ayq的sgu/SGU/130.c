#include<stdio.h>

long long f[31]={0};

int main()
{
   long long i,j,n;
   scanf("%I64d",&n);
   f[0]=f[1]=1;
   for (i=2;i<=n;i++)
      for (j=0;j<=i-1;j++)
         f[i]+=f[j]*f[i-j-1];
   printf("%I64d %I64d\n",f[n],n+1);
   return 0;
}
