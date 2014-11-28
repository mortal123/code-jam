#include<stdio.h>

long ans[101]={0};

int main()
{
   long i,j,n,m,a,b,c,d;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld",&a,&b);
      for (j=1;j<=n;j++)
      {
         scanf("%ld%ld",&c,&d);
         if (a>b&&c>d||a==b&&c==d||a<b&&c<d)
            ans[j]+=2;
         if (a-b==c-d)
            ans[j]+=3;
         if (a==c)
            ans[j]++;
         if (b==d)
            ans[j]++;
      }
   }
   for (i=1;i<n;i++)
      printf("%ld ",ans[i]);
   printf("%ld\n",ans[n]);
   return 0;
}
