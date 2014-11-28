#include<stdio.h>

long hash[1000001]={0};

int main()
{
   long i,j,n,m,t,max=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&t);
      if (t>max)
         max=t;
      hash[t]++;
   }
   for (i=max;i>=2;i--)
   {
      t=0;
      for (j=1;j*i<=max;j++)
         t+=hash[i*j];
      if (t>=2)
         break;
   }
   printf("%ld\n",i);
   return 0;
}
