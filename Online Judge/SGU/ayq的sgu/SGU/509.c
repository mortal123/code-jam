#include <stdio.h>

struct case1
{
   int p,c,w,pos;
}p[200001],ans[100001];

void qs(int x,int y)
{
   int i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&p[j].p>t.p)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i].p<t.p)
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
   int i,j=0,n,l,go,c,p1=0,p2=0,lc=0,s=0;
   long long t,me;
   scanf("%d%d",&n,&l);
   for (i=0;i<n;i++)
   {
      scanf("%d%d%d",&p[i].p,&p[i].c,&p[i].w);
      p1+=(p[i].w>0);
      p2+=(p[i].w<0);
      p[i].pos=i;
   }
   scanf("%I64d",&t);
   qs(0,n-1);
   me=2*t/l;
   go=2*t%l;
   for (i=0;i<n;i++)
   {
      p[i+n]=p[i];
      p[i+n].p+=l;
   }
   for (i=0;i<n;i++)
      if (p[i].w>0)
      {
         while (p[j].p-p[i].p<=go)
         {
            if (p[j].w<0)
               s++;
            j++;
         }
         ans[p[(i+me*p2+s)%n].pos]=(struct case1){(p[i].p+t)%l,p[i].c,1,0};
      }
      else
         s--;
   s=0;
   for (i=0;i<n&&p[i].w<0;i++);
   if (i<n)
      lc=p[i].c;
   for (i=j=2*n-1;i>n-1;i--)
      if (p[i].w<0)
      {
         while (p[i].p-p[j].p<=go)
         {
            if (p[j].w>0)
            {
               s++;
               c=p[j].c;
            }
            j--;
         }
         ans[p[(i-s-me*p1%n+n)%n].pos]=(struct case1){((p[i].p-t)%l+l)%l,s?c:((me&&lc)?lc:p[i].c),-1,0};
      }
      else
      {
         s--;
         lc=p[i].c;
      }
   for (i=0;i<n;i++)
      printf("%d %d %d\n",ans[i].p,ans[i].c,ans[i].w);
   return 0;
}
