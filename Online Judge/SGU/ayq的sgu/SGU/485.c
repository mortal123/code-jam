#include <stdio.h>
#include <string.h>
#define lowbit(a) ((a)&(-(a)))

long f[33554433]={0},a[76]={0};
char num[33554433]={0},s[33554433]={0};

int main()
{
   long i,j,n,q,p;
   scanf("%ld%ld",&q,&n);
   for (i=1;i<n;i++)
      s[1<<i]=i;
   while(q--)
   {
      memset(f,0,4<<n);
      for(i=1;i<=3*n;i++)
         scanf("%ld",&a[i]);
      for (i=1;i<3*n;i++)
         for (j=i+1;j<=3*n;j++)
            if (a[i]<a[j])
            {
               a[i]^=a[j];
               a[j]^=a[i];
               a[i]^=a[j];
            }
      for (i=0;i<(1<<n)-1;i++)
      {
         if (i)
            num[i]=num[i-lowbit(i)]+1;
         p=s[lowbit(~i)];
         for (j=n;!(i&(1<<j))&&j>p;j--)
            if (f[i]+(a[num[i]+p+1]-a[3*n-num[i]])*a[num[i]+j+1]>f[(i|(1<<j)|(1<<p))>>1])
               f[(i|(1<<j)|(1<<p))>>1]=f[i]+(a[num[i]+p+1]-a[3*n-num[i]])*a[num[i]+j+1];
      }
      printf("%ld\n",f[(1<<n)-1]);
   }
   return 0;
}
