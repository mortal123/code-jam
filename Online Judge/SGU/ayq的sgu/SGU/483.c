#include <stdio.h>

long l[100001]={0};

int main()
{
   long i,n,k,st=50000,en=50000;
   scanf("%ld%ld",&n,&k);
   l[50000]=(k+1)*(k+1);
   if (l[50000]+k+1<=n)
   {
      l[49999]=l[50000]+k+1;
      st=49999;
      i=k*2+3;
      while (l[st]+i<=n)
      {
         l[st-1]=l[st]+i;
         st--;
         i+=2;
      }
   }
   i=k*2+2;
   while (l[en]+i<=n)
   {
      l[en+1]=l[en]+i;
      en++;
      i+=2;
   }
   for (i=st;i<=en;i++)
      printf("%ld%c",l[i],(i==en)?'\n':' ');
   return 0;
}
