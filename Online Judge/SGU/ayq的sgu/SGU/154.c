#include<stdio.h>

long long check(long long now)
{
   long long i,s=0;
   for (i=5;i<=now;i*=5)
      s+=now/i;
   return s;
}

long long work(long now)
{
   long long l=0,r,mid;
   if (!now)
      return 1;
   r=5*now;
   while (l<r-1)
   {
      mid=(l+r)>>1;
      if (check(mid)>=now)
         r=mid;
      else
         l=mid;
   }
   return r;
}

int main()
{
   long long q,ans;
   scanf("%I64d",&q);
   ans=work(q);
   if (ans!=work(q+1))
      printf("%I64d\n",ans);
   else
      printf("No solution\n");
   return 0;
}
