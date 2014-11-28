#include<stdio.h>

long f[42]={0};

int main()
{
   long i,n,s=0;
   f[1]=f[2]=1;
   for (i=3;i<=41;i++)
      f[i]=f[i-1]+f[i-2];
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      s+=f[i];
   printf("%ld\n",s);
   return 0;
}
