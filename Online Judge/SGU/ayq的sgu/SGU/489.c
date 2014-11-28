#include <stdio.h>

long f[2][10001]={0};

int main()
{
    long i,j,n,m,ans=0;
    scanf("%ld%ld",&n,&m);
    if(n==1)
       printf("%ld\n",1%m);
    else
    {
       f[1][2]=1;
       for(i=2;i<n;i++)
          for(j=1;j<=i+1;j++)
          {
             f[i&1][j]=f[i&1][j-1]+f[!(i&1)][i-j+2];
             if(f[i&1][j]>=m)
                f[i&1][j]-=m;
          }
       for(i=1;i<=n;i++)
          ans=(ans+f[!(n&1)][i])%m;
       printf("%ld\n",(ans<<1)%m);
   }
   return 0;
}
