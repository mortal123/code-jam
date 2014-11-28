#include<stdio.h>

long find(long tot,long k)
{
   if (tot==1)
      return 1;
   else if (k<=(tot>>1))
      return ((tot+1)>>1)+find(tot>>1,(tot>>1)-k+1);
   else
      return find(((tot+1)>>1),tot-k+1);
}

int main()
{
   long n,w;
   scanf("%ld%ld",&n,&w);
   printf("%ld",find(n,w));
   return 0;
}
