#include<stdio.h>

long a[8001]={0};

void qs(long x,long y)
{
   long i=x,j=y,t=a[(x+y)>>1];
   if (x>=y)
      return;
   a[(x+y)>>1]=a[x];
   while (i<j)
   {
      while (i<j&&a[j]>t)
         j--;
      if (i<j)
         a[i++]=a[j];
      while (i<j&&a[i]<t)
         i++;
      if (i<j)
         a[j--]=a[i];
   }
   a[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

int main()
{
   long i,j,k,n,ans=0;
   scanf("%ld%ld",&k,&n);
   for (i=1;i<=n;i++)
      scanf("%ld",&a[i]);
   qs(1,n);
   j=k;
   for (i=1;i<=n;i++)
   {
      if (a[i]/1000>a[i-1]/1000||j>=k)
      {
         ans++;
         j=0;
      }
      j++;
   }
   printf("%ld\n",ans+2);
   return 0;
}
