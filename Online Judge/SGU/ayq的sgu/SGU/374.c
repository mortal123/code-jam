#include<stdio.h>

long yh[25][25]={0},ans[101]={0},t[101]={0};

void cheng(long x)
{
   long i;
   for (i=1;i<=100;i++)
   {
      t[i]=t[i]*x+t[i-1]/10;
      t[i-1]%=10;
   }
}

void chu(long x)
{
   long i,l=0,temp;
   for (i=100;i>=1;i--)
   {
      temp=l*10+t[i];
      t[i]=temp/x;
      l=temp%x;
   }
}

void add()
{
   long i;
   for (i=1;i<=100;i++)
   {
      ans[i]=ans[i]+t[i]+ans[i-1]/10;
      ans[i-1]%=10;
   }
}

void print()
{
   long i,flag=0;
   for (i=100;i>=1;i--)
   {
      if (ans[i])
         flag=1;
      if (flag)
         printf("%ld",ans[i]);
   }
   printf("\n");
}

int main()
{
   
   long i,j,a,b,k;
   scanf("%ld%ld%ld",&a,&b,&k);
   yh[0][1]=1;
   for (i=1;i<=k;i++)
      for (j=1;j<=i+1;j++)
         yh[i][j]=yh[i-1][j]+yh[i-1][j-1];
   t[1]=1;
   for (i=1;i<=k;i++)
      cheng(a);
   for (i=1;i<=k+1;i++)
   {
      cheng(yh[k][i]);
      add();
      chu(yh[k][i]);
      chu(a);
      cheng(b);
   }
   print();
   return 0;
}
