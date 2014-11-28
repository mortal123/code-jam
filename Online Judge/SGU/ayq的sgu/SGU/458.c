#include <stdio.h>

long a[100001]={0},last[100001]={0},ans[100001]={0};

int main()
{
   long i,n,x,y,m1=0,r1=0,m2=0,r2=0,m3=0,r3=0;
   scanf("%ld",&n);
   a[0]=-2;
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&a[i]);
      if (a[r1]!=a[i]+1&&a[r1]!=a[i]-1)
      {
         x=m1+1;
         y=r1;
      }
      else if (a[r2]!=a[i]+1&&a[r2]!=a[i]-1)
      {
         x=m2+1;
         y=r2;
      }
      else
      {
         x=m3+1;
         y=r3;
      }
      last[i]=y;
      if (x>m1)
      {
         if (a[i]==a[r1])
         {
            r1=i;
            m1=x;
         }
         else if (a[i]==a[r2])
         {
            m2=m1;
            r2=r1;
            m1=x;
            r1=i;
         }
         else
         {
            m3=m2;
            r3=r2;
            m2=m1;
            r2=r1;
            m1=x;
            r1=i;
         }
      }
      else if (x>m2&&a[i]!=a[r1])
      {
         if (a[i]==a[r2])
         {
            r2=i;
            m2=x;
         }
         else
         {
            m3=m2;
            r3=r2;
            m2=x;
            r2=i;
         }
      }
      else if (x>m3&&a[i]!=a[r1]&&a[i]!=a[r2])
      {
         m3=x;
         r3=i;
      }
   }
   printf("%ld\n",n-m1);
   x=0;
   for (i=r1;i;i=last[i])
      ans[++x]=a[i];
   for (i=x;i>=1;i--)
      printf("%ld%c",ans[i],(i==1)?'\n':' ');
   return 0;
}
