#include <stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

long a[100001]={0};

int main()
{
   long i,n,l=1,r,min1=0,max1=0,min2=0,max2=0;
   scanf("%ld",&n);
   r=n;
   for (i=1;i<=n;i++)
      scanf("%ld",&a[i]);
   while (l<r)
   {
      min1=min(min1,a[l+1]);
      max1=max(max1,a[l+1]);
      min2=min(min2,a[r-1]);
      max2=max(max2,a[r-1]);
      if (a[l+1]>=min2&&a[l+1]<=max2)
         l++;
      else if (a[r-1]>=min1&&a[r-1]<=max1)
         r--;
      else
         break;
   }
   puts((l==r)?"YES":"NO");
   return 0;
}
