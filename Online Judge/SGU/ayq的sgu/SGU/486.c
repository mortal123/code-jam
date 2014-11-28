#include<stdio.h>

char hash1[10]={'\0'},hash2[10]={'\0'};

int main()
{
   long i,n,m,ans1=0,ans2=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=4;i++)
   {
      hash1[n%10]++;
      hash2[m%10]++;
      if (n%10==m%10)
         ans1++;
      n/=10;
      m/=10;
   }
   for (i=0;i<=9;i++)
      if (hash1[i]==hash2[i]&&hash1[i]>0)
         ans2++;
   printf("%ld %ld\n",ans1,ans2-ans1);
   return 0;
}
