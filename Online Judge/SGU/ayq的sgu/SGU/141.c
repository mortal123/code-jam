#include <stdio.h>
#define abb(a) ((a)>0?(a):(-(a)))

long x,y;

long GCD(long a,long b)
{
   return b?GCD(b,a%b):a;
}

void EX_GCD(long a,long b)
{
   long t;
   if (!b)
   {
      x=1;
      y=0;
   }
   else
   {
      EX_GCD(b,a%b);
      t=x;
      x=y;
      y=t-a/b*y;
   }
}

int main()
{
   long i,a,b,c,gcd,k,px,px2,py,py2,f=0;
   scanf("%ld%ld%ld%ld",&a,&b,&c,&k);
   if (c<0)
   {
      c=-c;
      f=1;
   }
   gcd=GCD(a,b);
   if (c%gcd)
   {
      printf("NO\n");
      goto end;
   }
   a/=gcd;
   b/=gcd;
   c/=gcd;
   EX_GCD(a,b);
   x=(x*c%b+b)%b;
   y=(c-a*x)/b;
   while (abb(x+b)+abb(y-a)<abb(x)+abb(y))
   {
      x+=b;
      y-=a;
   }
   while (abb(x-b)+abb(y+a)<abb(x)+abb(y))
   {
      x-=b;
      y+=a;
   }
   for (i=-10;i<=10;i++)
   {
      px=x+b*i;
      py=y-a*i;
      c=k-abb(px)-abb(py);
      if (c>=0&&!(c&1))
      {
         px2=py2=0;
         if (f)
         {
            px=-px;
            py=-py;
         }
         if (px<0)
         {
            px2=-px;
            px=0;
         }
         if (py<0)
         {
            py2=-py;
            py=0;
         }
         printf("YES\n%ld %ld %ld %ld\n",px+c/2,px2+c/2,py,py2);
         goto end;
      }
   }
   printf("NO\n");
   end:
   return 0;
}
