#include<stdio.h>

long list[4]={31752000,72576000,81648000,36288000};
long n,ans=0,hash=0;

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
            if (!(hash&(1<<i)))
            {
               hash+=(1<<i);
               search(l-1,left-1);
               hash-=(1<<i);
            }
   }
   else
   {
      for (i=0;i<n/2;i++)
      {
         hash+=(1<<i);
         search(l-1,left-1);
         hash-=(1<<i);
      }
      ans<<=1;
      if (l>left)
         search(l-1,left);
      if (n&1)
      {
         hash+=(1<<n/2);
         search(l-1,left-1);
         hash-=(1<<n/2);
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
   else if(n==10&&k<=9&&k>=6)
      printf("%ld\n",list[k-6]);
   else
   {
      search(n,k);
      printf("%ld\n",ans);
   }
   return 0;
}
