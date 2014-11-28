#include<stdio.h>

long p[1000001]={0};

int main()
{
   long x,y,i=0;
   scanf("%ld%ld",&x,&y);
   while (x)
   {
      x%=y;
      if (!x)
      {
         printf("%ld 0\n",i);
         break;
      }
      else if (p[x])
      {
         printf("%ld %ld\n",p[x]-1,i-p[x]+1);
         break;
      }
      p[x]=++i;
      x*=10;
   }
   return 0;
}
