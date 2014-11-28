#include<stdio.h>
#define oo 2100000000

long v[16001]={0},f[16001]={0},e[32001]={0},next[32001]={0},head[16001]={0};
long ans=-oo,totm=0;
char hash[16001]={'\0'};

void add(long a,long b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
}

void dfs(long now)
{
   long i;
   f[now]=v[now];
   hash[now]=1;
   for (i=head[now];i;i=next[i])
      if (!hash[e[i]])
      {
         dfs(e[i]);
         if (f[e[i]]>0)
            f[now]+=f[e[i]];
      }
   if (f[now]>ans)
      ans=f[now];
}

int main()
{
   long i,n,a,b;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%ld",&v[i]);
   for (i=1;i<n;i++)
   {
      scanf("%ld%ld",&a,&b);
      add(a,b);
      add(b,a);
   }
   dfs(1);
   printf("%ld\n",ans);
   return 0;
}
