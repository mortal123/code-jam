#include <stdio.h>

long a[101]={0},b[101]={0};
long c;

long long check(long mid)
{
   long long s=0;
   long i,h,tmp;
   for (h=1;a[h]<mid;h++)
   {
      mid-=a[h];
      b[h]=a[h];
   }
   b[h]=mid;
   while (h)
      if (b[h]>c)
      {
         s+=(long long)b[h]/c*h;
         b[h]%=c;
         if (!b[h])
            h--;
      }
      else
      {
         s+=h;
         tmp=c;
         while (h&&b[h]<=tmp)
            tmp-=b[h--];
         b[h]-=tmp;
      }
   return s;
}

int main()
{
   long i,n,p,t,l=0,mid;
   long long r=1;
   scanf("%ld%ld%ld%ld",&n,&c,&p,&t);
   t/=2*p;
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&a[i]);
      r+=a[i];
   }
   while (l<r-1)
   {
      mid=(l+r)>>1;
      if (mid==500)
         mid=500;
      if (check(mid)<=t)
         l=mid;
      else
         r=mid;
   }
   printf("%ld\n",l);
   return 0;
}
