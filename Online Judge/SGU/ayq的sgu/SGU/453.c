#include <stdio.h>

long long gcd(long long a,long long b)
{
   return b?gcd(b,a%b):a;
}

int main()
{
   long long l,v1,v2,t,ans,a,b,x;
   scanf("%I64d%I64d%I64d%I64d",&l,&v1,&v2,&t);
   if (v1<v2)
   {
      v1^=v2;
      v2^=v1;
      v1^=v2;
   }
   a=v1*t%(2*l);
   b=v2*t%(2*l);
   ans=v1*t/l+(a<l&&(b<l&&a+b>=l||b>=l&&a>=b-l)||a>=l&&(b>=l&&a+b>=3*l||b<l&&a-l>=b));
   a=v2/gcd(v1,v2);
   b=v1/gcd(v1,v2);
   if (!(b&1)&&(a&1))
      ans-=((v1*t)/(l*b)+1)/2;
   a=v1/gcd(v1,v2);
   b=v2/gcd(v1,v2);
   if (!(b&1)&&(a&1))
      ans-=((v2*t)/(l*b)+1)/2;
   printf("%I64d\n",ans);
   return 0;
}
