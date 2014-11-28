#include <stdio.h>

long double f[51][51]={0},s[51]={0};

long double dp(long a,long b,long x,long y)
{
   long i,j;
   for (i=0;i<=x;i++)
      for (j=0;j<=y;j++)
         if (i|j)
         {
            f[i][j]=0;
            if (i)
               f[i][j]+=(a-i+1.0)/(a+b-i-j+1)*f[i-1][j];
            if (j)
               f[i][j]+=(b-j+1.0)/(a+b-i-j+1)*f[i][j-1];
         }
   return f[x][y];
}

int main()
{
   long i,j,n,a,b,tmp,pst=0,pen=100;
   long double p,sum,x=0;
   scanf("%ld%ld%ld%ld",&n,&a,&b,&tmp);
   f[0][0]=1;
   p=tmp/100.0;
   for (i=a;i<=n-b;i++)
   {
      s[i]=dp(i,n-i,a,b);
      x+=s[i];
   }
   for (i=a;i<=n-b;i++)
      s[i]/=x;
   for (i=a;i<=n-b;i++)
   {
      sum=s[i];
      j=i;
      while (j<n-b&&sum<p-1e-15)
         sum+=s[++j];
      if (sum>=p-1e-15&&j-i<pen-pst)
      {
         pst=i;
         pen=j;
      }
   }
   if (tmp)
      printf("%ld %ld\n",pst,pen);
   else
      printf("0 0\n");
   return 0;
}
