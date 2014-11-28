#include<stdio.h>

int main()
{
   long i,n,a=1,b=1,ans=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      if (i&1)
         a++;
      else
         b++;
      ans+=a*b;
   }
   printf("%ld.000\n",ans-(n!=0));
   return 0;
}
