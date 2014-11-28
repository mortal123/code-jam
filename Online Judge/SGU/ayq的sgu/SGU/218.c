#include<stdio.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

long link[501][501]={0},f[501]={0},hash[501]={0};
long n,flag=0;

long match(long now,long limit)
{
   long i;
   for (i=1;i<=n;i++)
      if (link[now][i]<=limit&&hash[i]!=flag)
      {
         hash[i]=flag;
         if (!f[i]||match(f[i],limit))
         {
            f[i]=now;
            return 1;
         }
      }
   return 0;
}

long check(long now)
{
   long i;
   memset(f,0,sizeof(f));
   for (i=1;i<=n;i++)
   {
      flag++;
      if (!match(i,now))
         return 0;
   }
   return 1;
}

int main()
{
   long i,j,m,l=oo,r=-oo;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
      {
         scanf("%ld",&link[i][j]);
         r=max(r,link[i][j]);
         l=min(l,link[i][j]);
      }
   l--;
   while (l<r-1)
   {
      m=(l+r)>>1;
      if (check(m))
         r=m;
      else
         l=m;
   }
   printf("%ld\n",r);
   check(r);
   for (i=1;i<=n;i++)
      printf("%ld %ld\n",f[i],i);
   return 0;
}
