#include <stdio.h>

unsigned long long f[20][10]={0};

int main()
{
   long i,j,k,q,last,t;
   unsigned long long n,s,ans;
   f[0][0]=1;
   for (i=1;i<=19;i++)
      for (j=0;j<=9;j++)
         for (k=0;k<=9;k++)
            if (j!=1||k!=3)
               f[i][j]+=f[i-1][k];
   scanf("%ld",&q);
   while (q--)
   {
      ans=0;
      scanf("%I64u",&n);
      last=0;
      s=1e18+1e-7;
      for (i=19;i>=1;i--)
      {
         t=0;
         for (j=0;n>=f[i][j]||last==1&&j==3;j++)
         {
            t++;
            ans+=s;
            if (last!=1||j!=3)
               n-=f[i][j];
         }
         last=t;
         s/=10;
      }
      printf("%I64u\n",ans);
   }
   return 0;
}
