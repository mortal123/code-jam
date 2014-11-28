#include<stdio.h>

char str[105]={'\0'};

int main()
{
   long i,n,m;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=(n-1)%m+1;i++)
      scanf("%s",str+1);
   printf("%s\n",str+1);
   return 0;
}
