#include<stdio.h>

long f[2][2][1526]={0};

void add(long a[],long x,long b[])
{
   long i;
   for (i=1;i<=1525;i++)
   {
      a[i]=a[i]+a[i-1]/100000+b[i]*x;
      a[i-1]%=100000;
   }
}

int main()
{
   long i,flag=0,n,m;
   f[0][0][1]=1;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      memset(f[i&1],0,sizeof(f[i&1]));
      add(f[i&1][0],n,f[!(i&1)][1]);
      add(f[i&1][1],2,f[!(i&1)][1]);
      add(f[i&1][1],1,f[!(i&1)][0]);
   }
   for (i=1525;i>=1;i--)
   {
      if (f[m&1][0][i]||flag)
         flag++;
      if (flag==1)
         printf("%ld",f[m&1][0][i]);
      else if (flag)
         printf("%.5ld",f[m&1][0][i]);
   }
   if (!flag)
      printf("0");
   printf("\n");
   return 0;
}
