#include<stdio.h>

long a[17]={0};

int main()
{
   long i,j,s=0;
   for (i=1;i<=16;i++)
   {
      scanf("%ld",&a[i]);
      if (a[i])
      {
         for (j=1;j<i;j++)
            if (a[j]>a[i])
               s^=1;
      }
      else
         s^=(3-(i-1)/4)&1;
   }
   if (s)
      printf("NO\n");
   else
      printf("YES\n");
   return 0;
}
