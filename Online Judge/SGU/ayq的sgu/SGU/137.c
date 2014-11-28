#include <stdio.h>

long a[1001]={0};

int main()
{
   long i,n,m,k;
   scanf("%ld%ld",&n,&m);
   for (k=1;(m%n)*k%n!=n-1;k++);
   for (i=1;i<=m%n;i++)
      a[i*k%n+1]++;
   for (i=1;i<=n;i++)
      printf("%ld%c",a[i]+m/n,(i==n)?'\n':' ');
   return 0;
}
