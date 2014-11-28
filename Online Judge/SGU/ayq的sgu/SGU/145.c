#include <stdio.h>
#define oo 1000000000

long head[101]={0},e[10001]={0},next[10001]={0},v[10001]={0},dis[101]={0},d[100001]={0},last[101]={0},ans[101]={0};
char hash[101]={'\0'};
long k,t,tot,totm=0;

void add(long a,long b,long c)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   v[totm]=c;
}

void find(long now,long limit)
{
   long i;
   if (now==t)
      tot++;
   else
   {
      hash[now]=1;
      for (i=head[now];i;i=next[i])
         if (!hash[e[i]]&&dis[e[i]]<=limit-v[i])
         {
            find(e[i],limit-v[i]);
            if (tot==k)
            {
               hash[now]=0;
               return;
            }
         }
      hash[now]=0;
   }
}

long dfs(long now,long left)
{
   long i;
   if (now==t)
      return !left;
   hash[now]=1;
   for (i=head[now];i;i=next[i])
      if (!hash[e[i]]&&left-v[i]>=dis[e[i]]&&dfs(e[i],left-v[i]))
      {
         last[e[i]]=now;
         return 1;
      }
   hash[now]=0;
   return 0;
}     

int main()
{
   long i,n,m,a,b,c,s,l,r=0,mid,now,st=1,en=1;
   scanf("%ld%ld%ld",&n,&m,&k);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld",&a,&b,&c);
      r+=c;
      add(a,b,c);
      add(b,a,c);
   }
   scanf("%ld%ld",&s,&t);
   for (i=1;i<=n;i++)
      dis[i]=oo;
   d[1]=t;
   dis[t]=0;
   while (st<=en)
   {
      now=d[st++];
      hash[now]=0;
      for (i=head[now];i;i=next[i])
         if (dis[e[i]]>dis[now]+v[i])
         {
            dis[e[i]]=dis[now]+v[i];
            if (!hash[e[i]])
            {
               hash[e[i]]=1;
               d[++en]=e[i];
            }
         }
   }
   l=dis[s]-1;
   while (l<r-1)
   {
      mid=(l+r)>>1;
      tot=0;
      find(s,mid);
      if (tot==k)
         r=mid;
      else
         l=mid;
   }
   dfs(s,r);
   tot=0;
   for (i=t;i;i=last[i])
      ans[++tot]=i;
   printf("%ld %ld\n",r,tot);
   for (i=tot;i>=1;i--)
      printf("%ld%c",ans[i],(i==1)?'\n':' ');
   return 0;
}
