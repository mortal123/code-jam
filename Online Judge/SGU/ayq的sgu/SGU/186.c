#include<stdio.h>

long a[101]={0};

int main()
{
   long i,j,t,n,ans=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%ld",&a[i]);
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         if (a[i]>a[j])
         {
            t=a[i];
            a[i]=a[j];
            a[j]=t;
         }
   j=n-1;
   for (i=1;j-a[i]-1>=0;i++)
   {
      j-=a[i]+1;
      ans+=a[i];
   }
   printf("%ld\n",ans+j);
   return 0;
}
