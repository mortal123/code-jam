#include <stdio.h>

struct case1
{
   long x,y,pos;
}p[200001]={0,0},q[200001]={0,0};
long hash[200001]={0},f[200001]={0},x[200001]={0},y[200001]={0};
long flag=0;

void qs1(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&p[j].y>t.y)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i].y<t.y)
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs1(x,i-1);
   qs1(i+1,y);
}

void qs2(long x,long y)
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
   qs2(x,i-1);
   qs2(i+1,y);
}

long getf(long now)
{
   if (f[now]==now)
      return now;
   return f[now]=getf(f[now]);
}

int main()
{
   long i,j,k,n,pos;
   long long ans=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld",&p[i].x,&p[i].y);
      f[i]=i;
      p[i].pos=i;
   }
   qs1(1,n);
   for (i=1;i<=n;i++)
      q[i]=p[i];
   qs2(1,n);
   for (i=1;i<=n;i=j+1)
   {
      pos=getf(p[j=i].pos);
      while (j<n&&p[j+1].x==p[i].x)
         f[getf(p[++j].pos)]=pos;
   }
   for (i=1;i<=n;i=j+1)
   {
      pos=getf(q[j=i].pos);
      while (j<n&&q[j+1].y==q[i].y)
         f[getf(q[++j].pos)]=pos;
   }
   for (i=1;i<=n;i=j)
   {
      flag++;
      for (j=i;j<=n&&p[j].x==p[i].x;j++)
      {
         pos=getf(p[j].pos);
         if (hash[pos]!=flag)
         {
            hash[pos]=flag;
            x[pos]++;
         }
      }
   }
   for (i=1;i<=n;i=j)
   {
      flag++;
      for (j=i;j<=n&&q[j].y==q[i].y;j++)
      {
         pos=getf(q[j].pos);
         if (hash[pos]!=flag)
         {
            hash[pos]=flag;
            y[pos]++;
         }
      }
   }
   for (i=1;i<=n;i++)
      ans+=(long long)x[i]*y[i];
   printf("%I64d\n",ans);
   return 0;
}
