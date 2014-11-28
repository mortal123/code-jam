#include <stdio.h>

int main()
{
   long i,j;
   long long a,b,c,x,y;
   scanf("%I64d%I64d%I64d",&a,&b,&c);
   x=y=1;
   for (i=1;i<=2000000;i++)
   {
      x=(x*a+x%b)%c;
      y=(y*a+y%b)%c;
      y=(y*a+y%b)%c;
      if (x==y)
         break;
   }
   if (i==2000001)
      printf("-1");
   else
   {
      y=1;
      for (i=0;y!=x;i++)
      {
         x=(x*a+x%b)%c;
         y=(y*a+y%b)%c;
      }
      for (j=i+1,y=(x*a+x%b)%c;x!=y&&j<=2000000;j++)
         y=(y*a+y%b)%c;
      if (j<=2000000)
         printf("%ld\n",j);
      else
         printf("-1\n");
   }
   return 0;
}
