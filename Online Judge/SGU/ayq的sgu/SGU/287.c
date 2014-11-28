#include <stdio.h>

long long f[2200001]={0};

int main()
{
   long long n;
   long i,c;
   f[1]=1;
   scanf("%I64d%ld",&n,&c);
   for (i=2;f[i-1]<n;i++)
      f[i]+=f[i-1]+((i-c-1>0)?f[i-c-1]:0)+1;
   printf("%ld\n",i-1+c);
   return 0;
}
