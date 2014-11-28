#include <stdio.h>
#define oo 1000000000

long head[101]={0},dis[101]={0},last[101]={0},t[101]={0},ans[101]={0},e[20001]={0},next[20001]={0},v[20001]={0},pre[20001]={0},drt[20001]={0},d[300001]={0};
char hash[101]={'\0'};
long s,n,tot,totm=0;

void add(long a,long b,long c,long x,long y)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   v[totm]=c;
   pre[totm]=x;
   drt[totm]=y;
}

long check(long limit)
{
   long i,now,st=100000,en=100000;
   for (i=1;i<=n;i++)
      dis[i]=oo;
   dis[s]=0;
   d[st]=s;
   while (st<=en)
   {
      now=d[st++];
      hash[now]=0;
      for (i=head[now];i;i=next[i])
         if (dis[now]+v[i]<dis[e[i]]&&(dis[now]+v[i])*drt[i]+pre[i]<=limit)
         {
            dis[e[i]]=dis[now]+v[i];
            last[e[i]]=now;
            if (!hash[e[i]])
            {
               hash[e[i]]=1;
               if (dis[e[i]]<=dis[d[st]])
                  d[--st]=e[i];
               else
                  d[++en]=e[i];
            }
         }
   }
   for (i=1;i<=tot;i++)
      if (dis[t[i]]<oo)
         return t[i];
   return 0;
}

int main()
{
   long i,m,h,l=-1,r,mid,a,b,c,x,y;
   scanf("%ld%ld%ld%ld%ld",&n,&m,&h,&s,&tot);
   r=h+1;
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld%ld%ld",&a,&b,&c,&x,&y);
      add(a,b,c,x,y);
      add(b,a,c,x,y);
   }
   for (i=1;i<=tot;i++)
      scanf("%ld",&t[i]);
   while (l<r-1)
   {
      mid=(l+r)>>1;
      if (check(mid))
         r=mid;
      else
         l=mid;
   }
   if (r==h+1)
      printf("NO\n");
   else
   {
      printf("YES\n%ld\n",r);
      a=0;
      for (i=check(r);i;i=last[i])
         ans[++a]=i;
      printf("%ld",a);
      for (i=a;i>=1;i--)
         printf(" %ld",ans[i]);
      printf("\n");
   }
   return 0;
}
