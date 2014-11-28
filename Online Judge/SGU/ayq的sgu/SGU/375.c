#include <stdio.h>

long l[101]={0};

int main()
{
   long i,n,tot=0;
   scanf("%ld",&n);
   if (n&1)
   {
      while (n>1)
      {
         if ((n+1)&2)
         {
            l[++tot]=1;
            n=((n+1)>>1);
         }
         else
         {
            l[++tot]=2;
            n>>=1;
         }
      }
      printf("%ld\n",tot);
      for (i=tot;i>=1;i--)
         printf("%ld%c",l[i],(i==1)?'\n':' ');
   }
   else
      printf("No solution\n");
   return 0;
}
