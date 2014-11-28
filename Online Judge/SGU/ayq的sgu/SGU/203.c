#include<stdio.h>

long long d[500002]={0};
long tot;

void down(long now)
{
   long p;
   long long t;
   while ((now<<1)<=tot)
   {
      p=(now<<1);
      if (p+1<=tot&&d[p+1]<d[p])
         p++;
      if (d[p]<d[now])
      {
         t=d[p];
         d[p]=d[now];
         d[now]=t;
         now=p;
      }
      else
         break;
   }
}

int main()
{
   long i,n;
   long long ans=0;
   scanf("%ld",&n);
   tot=n;
   for (i=1;i<=n;i++)
      scanf("%I64d",&d[i]);
   for (i=1;i<n;i++)
   {
      if (d[2]<d[3]||i==n-1)
      {
         d[2]+=d[1];
         ans+=d[2];
         down(2);
      }
      else
      {
         d[3]+=d[1];
         ans+=d[3];
         down(3);
      }
      d[1]=d[tot];
      tot--;
      down(1);
   }
   printf("%I64d\n",ans);
   return 0;
}
