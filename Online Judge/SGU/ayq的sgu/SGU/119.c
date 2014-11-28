#include<stdio.h>

struct case1
{
   long a,b;
}p[10001]={{0,0}};

long gcd(long a,long b)
{
   return b?gcd(b,a%b):a;
}

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&(p[j].a>t.a||p[j].a==t.a&&p[j].b>t.b))
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&(p[i].a<t.a||p[i].a==t.a&&p[i].b<t.b))
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

int main()
{
   long i,num,n,a,b;
   scanf("%ld%ld%ld",&n,&a,&b);
   num=n/gcd(gcd(a,b),n);
   printf("%ld\n",num);
   for (i=0;i<num;i++)
   {
      p[i+1].a=i*a%n;
      p[i+1].b=i*b%n;
   }
   qs(1,num);
   for (i=1;i<=num;i++)
      printf("%ld %ld\n",p[i].a,p[i].b);
   return 0;
}
