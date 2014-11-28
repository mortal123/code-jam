#include<stdio.h>

long n,ans=0,hash1=0,hash2=0,hash3=0;

void search(long l,long left)
{
   long i;
   if (!l)
   {
     ans++;
     return;
   }
   if (l<n)
   {
      if (l>left)
         search(l-1,left);
      if (left)
         for (i=0;i<n;i++)
            if (!(hash1&(1<<i))&&!(hash2&(1<<(l+i-1)))&&!(hash3&(1<<(l+n-i-2))))
            {
               hash1+=(1<<i);
               hash2+=(1<<(l+i-1));
               hash3+=(1<<(l+n-i-2));
               search(l-1,left-1);
               hash1-=(1<<i);
               hash2-=(1<<(l+i-1));
               hash3-=(1<<(l+n-i-2));
            }
   }
   else
   {
      for (i=0;i<n/2;i++)
      {
         hash1+=(1<<i);
         hash2+=(1<<(l+i-1));
         hash3+=(1<<(l+n-i-2));
         search(l-1,left-1);
         hash1-=(1<<i);
         hash2-=(1<<(l+i-1));
         hash3-=(1<<(l+n-i-2));
      }
      ans<<=1;
      if (l>left)
         search(l-1,left);
      if (n&1)
      {
         hash1+=(1<<n/2);
         hash2+=(1<<(l+n/2-1));
         hash3+=(1<<(l+n/2-1));
         search(l-1,left-1);
         hash1-=(1<<n/2);
         hash2-=(1<<(l+n/2-1));
         hash3-=(1<<(l+n/2-1));
     }
   }
}

int main()
{
   long k;
   scanf("%ld%ld",&n,&k);
   if (k>n)
      printf("0\n");
   else if(!k)
      printf("1\n");
   else
   {
      search(n,k);
      printf("%ld\n",ans);
   }
   return 0;
}
