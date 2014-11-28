#include<stdio.h>
#define abb(a) ((a)>0?(a):(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

long long x,y;

long long GCD(long long a,long long b)
{
   return b?GCD(b,a%b):a;
}

void ex_gcd(long long a,long long b)
{
   long long t;
   if (!b)
   {
      x=1;
      y=0;
   }
   else
   {
      ex_gcd(b,a%b);
      t=x;
      x=y;
      y=t-a/b*y;
   }
}

int main()
{
   long long a,b,c,gcd,x1,x2,y1,y2;
   scanf("%I64d%I64d%I64d%I64d%I64d%I64d%I64d",&a,&b,&c,&x1,&x2,&y1,&y2);
   if (x1>x2||y1>y2)
      printf("0\n");
   else if (a==0&&b==0)
   {
      if (c==0)
         printf("%I64d\n",(x2-x1+1)*(y2-y1+1));
      else
         printf("0\n");
   }
   else if (a==0)
   {
      if (c%b==0&&-c/b>=y1&&-c/b<=y2)
         printf("%I64d\n",x2-x1+1);
      else
         printf("0\n");
   }
   else if (b==0)
   {
      if (c%a==0&&-c/a>=x1&&-c/a<=x2)
         printf("%I64d\n",y2-y1+1);
      else
         printf("0\n");
   }
   else
   {
      c=-c;
      if (c<0)
      {
         c=-c;
         a=-a;
         b=-b;
      }
      gcd=GCD(abb(a),abb(b));
      if (c%gcd!=0)
         printf("0\n");
      else
      {
         a/=gcd;
         b/=gcd;
         c/=gcd;
         ex_gcd(abb(a),abb(b));
         if (a<0)
            x=-x;
         if (b<0)
            y=-y;
         x*=c;
         y*=c;
         x1=x1+(x-x1+100000000*abb(b))%abb(b);
         x2=x2-abb(b)+1+(x-x2+100000000*abb(b)-1)%abb(b);
         y1=max(y1+(y-y1+100000000*abb(a))%abb(a),min((c-x2*a)/b,(c-x1*a)/b));
         y2=min(y2-abb(a)+1+(y-y2+100000000*abb(a)-1)%abb(a),max((c-x2*a)/b,(c-x1*a)/b));
         printf("%I64d\n",max((y2-y1)/abb(a)+1,0));
      }
   }
   return 0;
}
