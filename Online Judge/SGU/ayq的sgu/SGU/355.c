#include<stdio.h>
#include<math.h>

long p[10001]={0},ans[10001]={0};

int main()
{
   long i,j,n;
   scanf("%ld",&n);
   for (i=2;i<=n;i++)
      if (!p[i])
         for (j=1;i*j<=n;j++)
            p[i*j]=i;
   ans[1]=1;
   for (i=2;i<=n;i++)
      ans[i]=ans[i/p[i]]+1;
   printf("%ld\n1",(long)(log(n)/log(2)+0.0000001)+1);
   for (i=2;i<=n;i++)
      printf(" %ld",ans[i]);
   printf("\n");
   return 0;
}
