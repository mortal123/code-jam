#include<stdio.h>

struct case1
{
   long b,pos;
}p[101]={{0,0}};
long s[101]={0};

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&p[j].b<t.b)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i].b>t.b)
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
   long i,n,ans=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%ld",&s[i]);
   for (i=1;i<=n;i++)
   {
      p[i].pos=i;
      scanf("%ld",&p[i].b);
   }
   qs(1,n);
   for (i=2;i<=n;i++)
      s[p[i].pos]+=s[p[i-1].pos];
   for (i=1;i<=n;i++)
      if (p[i].b+s[p[i].pos]>ans)
         ans=p[i].b+s[p[i].pos];
   printf("%ld\n",ans);
   return 0;
}
