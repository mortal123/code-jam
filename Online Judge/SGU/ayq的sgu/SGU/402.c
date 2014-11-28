#include <stdio.h>
#include <string.h>
#define oo 1000000000

long head[51]={0},dis[51]={0},gap[51]={0},last[51]={0},laste[51]={0},h2[1001]={0},e[1002]={0},next[1002]={0},r[1002]={0},num[1002]={0};
char hash[51]={0};
long n,totm=1,ans=oo,flag=0;

void add(long a,long b,long c,long d)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   r[totm]=c;
   num[totm]=d;
}

void dfs(long now,long forbid)
{
   long i;
   hash[now]=1;
   for (i=head[now];i;i=next[i])
      if (!hash[e[i]]&&r[i]&&e[i]!=forbid)
         dfs(e[i],forbid);
}

void sap(long s,long t,long now)
{
   long i,j,min,f=0;
   memset(dis,0,sizeof(dis));
   memset(gap,0,sizeof(gap));
   memset(last,0,sizeof(last));
   for (i=2;i<=totm;i+=2)
      r[i]=r[i+1]=(r[i]+r[i+1])/2;
   gap[0]=n-1;
   for (i=s;dis[s]<n-1;)
   {
      for (j=head[i];j;j=next[j])
         if (e[j]!=now&&r[j]&&dis[e[j]]==dis[i]-1)
         {
            last[e[j]]=i;
            laste[e[j]]=j;
            i=e[j];
            break;
         }
      if (i==t)
      {
         for (min=oo;last[i];i=last[i])
            if (r[laste[i]]<min)
               min=r[laste[i]];
         f+=min;
         for (i=t;last[i];i=last[i])
         {
            r[laste[i]]-=min;
            r[laste[i]^1]+=min;
         }
      }
      else if (!j)
      {
         if (gap[dis[i]]==1)
            break;
         min=oo;
         for (j=head[i];j;j=next[j])
            if (e[j]!=now&&r[j]&&dis[e[j]]<min)
               min=dis[e[j]];
         min++;
         if (min>n-1)
            min=n-1;
         gap[dis[i]]--;
         dis[i]=min;
         gap[dis[i]]++;
         if (i!=s)
            i=last[i];
      }
   }
   if (f<ans)
   {
      ans=f;
      memset(hash,0,sizeof(hash));
      dfs(s,now);
      flag++;
      for (i=1;i<=n;i++)
         if (i!=now)
            for (j=head[i];j;j=next[j])
               if (e[j]!=now&&hash[i]&&!hash[e[j]])
                  h2[num[j]]=flag;
   }
}

int main()
{
   long i,j,m,a,b,c,tot=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld",&a,&b,&c);
      add(a,b,c,i);
      add(b,a,c,i);
   }
   for (i=1;i<=n;i++)
      for (j=2;j<=n;j++)
         if (j!=i&&1+(i==1)!=j)
            sap(1+(i==1),j,i);
   for (i=1;i<=m;i++)
      if (h2[i]==flag)
         tot++;
   printf("%ld\n%ld\n",ans,tot);
   for (i=1;i<=m;i++)
      if (h2[i]==flag)
         printf("%ld%c",i,(--tot)?' ':'\n');
   return 0;
}
