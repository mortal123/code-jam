#include<stdio.h>

long p[101]={0};

int main()
{
   long a,b,n,i,sa=0,sb=0;
   scanf("%ld%ld%ld",&a,&b,&n);
   p[0]=b;
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&p[i]);
      if (p[i]>p[i-1])
         sa+=p[i]-p[i-1];
      else
         sb+=p[i-1]-p[i];
   }
   if (sa>a||sb>b)
      printf("ERROR\n");
   else
   {
      for (i=1;i<=n;i++)
      {
         if (p[i]>p[i-1])
            printf("%ld 0\n",p[i]-p[i-1]);
         else
            printf("0 %ld\n",p[i-1]-p[i]);
      }
   }
   return 0;
}
