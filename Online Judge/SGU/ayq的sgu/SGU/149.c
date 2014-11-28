#include<stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))

long e[10001]={0},next[10001]={0},head[10001]={0},f[10001]={0},v[10001]={0},f1[10001]={0},f2[10001]={0},f3[10001]={0};
long totm=0;

void add(long a,long b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
}

void dfs1(long now)
{
   long i;
   for (i=head[now];i;i=next[i])
   {
      dfs1(e[i]);
      if (f1[e[i]]+v[e[i]]>f1[now])
      {
         f2[now]=f1[now];
         f1[now]=f1[e[i]]+v[e[i]];
      }
      else if (f1[e[i]]+v[e[i]]>f2[now])
         f2[now]=f1[e[i]]+v[e[i]];
   }
}

void dfs2(long now)
{
   long i;
   for (i=head[now];i;i=next[i])
   {
      if (f1[e[i]]+v[e[i]]==f1[now])
         f3[e[i]]=v[e[i]]+max(f3[now],f2[now]);
      else
         f3[e[i]]=v[e[i]]+max(f3[now],f1[now]);
      dfs2(e[i]);
   }
}

int main()
{
   long i,n,a,q;
   scanf("%ld",&n);
   for (i=2;i<=n;i++)
   {
      scanf("%ld%ld",&a,&q);
      add(a,i);
      f[i]=a;
      v[i]=q;
   }
   dfs1(1);
   dfs2(1);
   for (i=1;i<=n;i++)
      printf("%ld\n",max(f1[i],f3[i]));
   return 0;
}
