#include <stdio.h>

struct case1
{
   long x,y,num;
}p[100001]={{0,0,0}};
long d[100001]={0},f[100001]={0},last[100001]={0};

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&p[j].x>t.x)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i].x<t.x)
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
   long i,j,k,n,l,r,m,rec,ans=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      p[i].num=i;
      scanf("%ld%ld",&p[i].x,&p[i].y);
   }
   qs(1,n);
   for (i=1;i<=n;i=j+1)
   {
      j=i;
      while (j<n&&p[j+1].x==p[j].x)
         j++;
      for (k=i;k<=j;k++)
      {
         l=0;
         r=ans+1;
         while (l<r-1)
         {
            m=(l+r)>>1;
            if (p[d[m]].y<p[k].y)
               l=m;
            else
               r=m;
         }
         f[k]=f[d[l]]+1;
         last[k]=d[l];
      }
      for (k=i;k<=j;k++)
      {
         if (!d[f[k]]||p[k].y<p[d[f[k]]].y)
            d[f[k]]=k;
         if (f[k]>ans)
         {
            ans=f[k];
            rec=k;
         }
      }
   }
   printf("%ld\n",ans);
   for (i=rec;i;i=last[i])
      printf("%ld%c",p[i].num,last[i]?' ':'\n');
   return 0;
}
