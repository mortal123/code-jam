#include <stdio.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))

long a[4]={0},f[1000001]={0};

int main()
{
   long i,j,n,x;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%ld",&a[i]);
   scanf("%ld",&x);
   for (i=1;i<=x;i++)
      f[i]=oo;
   for (i=1;i<=n;i++)
      for (j=a[i];j<=x;j++)
         f[j]=min(f[j],f[j-a[i]]+1);
   printf("%ld\n",(f[x]==oo)?-1:f[x]);
   return 0;
}
