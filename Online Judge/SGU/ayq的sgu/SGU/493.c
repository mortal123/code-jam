#include <stdio.h>

struct case1
{
   long l,r,h;
}p[1001]={0,0,0};

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&p[j].l>t.l)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i].l<t.l)
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
   long i,j,q,n,ans;
   scanf("%ld",&q);
   while (q--)
   {
      scanf("%ld",&n);
      for (i=1;i<=n;i++)
         scanf("%ld%ld%ld",&p[i].l,&p[i].r,&p[i].h);
      qs(1,n);
      ans=2;
      for (i=1;i<n;i++)
      {
         for (j=i-1;j>=1&&p[j].h*(p[i+1].l-p[i].r)<p[i].h*(p[i+1].l-p[j].r);j--);
         if (!j)
            ans++;
         else
         {
            for (j=i+2;j<=n&&p[j].h*(p[i+1].l-p[i].r)<p[i+1].h*(p[j].l-p[i].r);j++);
            if (j>n)
               ans++;
         }
      }
      printf("%ld\n",ans);
   }
   return 0;
}
