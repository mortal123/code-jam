#include<stdio.h>

long a[401]={0},b[401]={0};

void cheng(long v[])
{
   long i;
   for (i=1;i<=400;i++)
   {
      v[i]=v[i]*2+v[i-1]/10;
      v[i-1]%=10;
   }
}

int main()
{
   long i,j=0,n,m;
   scanf("%ld%ld",&n,&m);
   a[1]=b[1]=1;
   for (i=1;i<=n;i++)
      cheng(a);
   for (i=1;i<=m;i++)
      cheng(b);
   a[1]+=b[1]-2;
   for (i=2;i<=400;i++)
   {
      a[i]=a[i]+b[i]+(a[i-1]+10)/10-1;
      a[i-1]=(a[i-1]+10)%10;
   }
   for (i=400;i>=1;i--)
   {
      if (a[i])
         j=1;
      if (j)
         printf("%ld",a[i]);
   }
   printf("\n");
   return 0;
}
