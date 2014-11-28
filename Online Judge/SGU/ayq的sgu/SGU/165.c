#include<stdio.h>

long h[2][6001]={0},v[6001]={0},s[2]={0},t[2]={0};

int main()
{
   long i,n,sum=0;
   double x;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%lf",&x);
      v[i]=(x-2+1e-8)*1000000;
      if (v[i]<0)
         v[i]--;
      if (v[i]>=0)
         h[0][++s[0]]=i;
      else
         h[1][++s[1]]=i;
   }
   printf("yes\n");
   for (i=1;i<=n;i++)
      if (sum<=0)
      {
         sum+=v[h[0][++t[0]]];
         printf("%ld%c",h[0][t[0]],(i==n)?'\n':' ');
      }
      else
      {
         sum+=v[h[1][++t[1]]];
         printf("%ld%c",h[1][t[1]],(i==n)?'\n':' ');
      }
   return 0;
}
