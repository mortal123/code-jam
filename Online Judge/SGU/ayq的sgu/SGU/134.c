#include<stdio.h>
#define oo 2100000000

long e[32001]={0},next[32001]={0},head[16001]={0},size[16001]={0},ans[16001]={0};
long totm=0,tot=0,min=oo,n;

void dfs(long now)
{
   long i,max=0;
   size[now]=1;
   for (i=head[now];i;i=next[i])
      if (!size[e[i]])
      {
         dfs(e[i]);
         size[now]+=size[e[i]];
         if (size[e[i]]>max)
            max=size[e[i]];
      }
   if (n-size[now]>max)
      max=n-size[now];
   if (max<min)
   {
      min=max;
      ans[tot=1]=now;
   }
   else if (max==min)
      ans[++tot]=now;
}

void add(long a,long b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
}

void qs(long x,long y)
{
   long i=x,j=y,t=ans[(x+y)>>1];
   if (x>=y)
      return;
   ans[(x+y)>>1]=ans[x];
   while (i<j)
   {
      while (i<j&&ans[j]>t)
         j--;
      if (i<j)
         ans[i++]=ans[j];
      while (i<j&&ans[i]<t)
         i++;
      if (i<j)
         ans[j--]=ans[i];
   }
   ans[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

int main()
{
   long i,a,b;
   scanf("%ld",&n);
   for (i=1;i<n;i++)
   {
      scanf("%ld%ld",&a,&b);
      add(a,b);
      add(b,a);
   }
   dfs(1);
   qs(1,tot);
   printf("%ld %ld\n",min,tot);
   for (i=1;i<tot;i++)
      printf("%ld ",ans[i]);
   printf("%ld\n",ans[tot]);
   return 0;
}
