#include <stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   long v,num;
}d[100001]={0,0};
long rec[1001]={0};
long tot=0;

void up(long x)
{
   struct case1 t;
   while (x>1)
      if (d[x>>1].v>d[x].v)
      {
         t=d[x>>1];
         d[x>>1]=d[x];
         d[x]=t;
         x>>=1;
      }
      else
         break;
}

void down(long x)
{
   struct case1 t;
   long y;
   while ((x<<1)<=tot)
   {
      y=x<<1;
      if (y<tot&&d[y+1].v<d[y].v)
         y++;
      if (d[y].v<d[x].v)
      {
         t=d[y];
         d[y]=d[x];
         d[x]=t;
         x=y;
      }
      else
         break;
   }
}

int main()
{
   long i,n,m=0,flag=0,ans=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
       scanf("%ld",&d[i].v);
       d[i].num=i;
       m=max(m,d[i].v);
       tot++;
       up(tot);
   }
   while (flag<m)
      if (((d[1].v-flag)<<1)<=m-flag)
      {
         ans++;
         if (ans<=1000)
            rec[ans]=d[1].num;
         d[1].v+=d[1].v-flag;
         down(1);
      }
      else
      {
         ans+=(d[1].v<<1)-flag-m;
         flag=(d[1].v<<1)-m;
      }
   printf("%ld\n",ans);
   if (ans<=1000)
      for (i=1;i<=ans;i++)
         if (rec[i])
            printf("science mission to the planet %ld\n",rec[i]);
         else
            printf("flying mission\n");
   return 0;
}
