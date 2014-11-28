#include<stdio.h>

int main()
{
   long long i,k;
   scanf("%I64d",&k);
   for (i=0;(1LL<<(i+1))*(i+1)-1<k;i++);
   printf("%I64d\n",i);
   return 0;
}
