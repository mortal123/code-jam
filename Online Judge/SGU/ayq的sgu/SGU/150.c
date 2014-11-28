#include <stdio.h>

int main()
{
   long i,x,y,x1,y1,x2,y2,n,px,py,add,last=0,f1=0,f2=0,s=0;
   scanf("%ld%ld%ld%ld%ld",&x1,&y1,&x2,&y2,&n);
   x=x2-x1;
   y=y2-y1;
   if (x<0)
   {
      f1=1;
      x=-x;
   }
   if (y<0)
   {
      f2=1;
      y=-y;
   }
   for (i=1;i<=x;i++)
   {
      add=1.0*i*y/x-1e-7-last+1;
      if (s+add>=n)
      {
         px=i-1;
         py=last+n-s-1;
         break;
      }
      s+=add;
      last=1.0*i*y/x+1e-7;
   }
   if (i>x)
      printf("no solution\n");
   else
   {
      if (f1)
         px=-px-1;
      if (f2)
         py=-py-1;
      printf("%ld %ld\n",px+x1,py+y1);
   }
   return 0;
}
