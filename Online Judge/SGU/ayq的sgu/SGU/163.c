#include<stdio.h>

int main()
{
   long i,j,n,k,t,s,sum=0;
   scanf("%ld%ld",&n,&k);
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&t);
      for (s=j=1;j<=k;j++)
         s*=t;
      if (s>0)
         sum+=s;
   }
   printf("%ld\n",sum);
   return 0;
}
