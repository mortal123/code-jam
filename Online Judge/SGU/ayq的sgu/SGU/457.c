#include <stdio.h>
#include <string.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))

long rec[500003]={0},link[101][101]={0},gap[103]={0},dis[103]={0},head[103]={0},du[103]={0},last[103]={0},laste[103]={0},e[20001]={0},next[20001]={0},r[20001]={0};
long s,n,totm=1,tot=0;

void add(long a,long b,long c)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   r[totm]=c;
   e[++totm]=a;
   next[totm]=head[b];
   head[b]=totm;
}

long sap(long s,long t,long n)
{
   long i,j,min,flow=0;
   memset(gap,0,sizeof(gap));
   memset(dis,0,sizeof(dis));
   gap[0]=n;
   for (i=s;dis[s]<n;)
   {
      for (j=head[i];j;j=next[j])
         if (e[j]<=n&&r[j]&&dis[e[j]]==dis[i]-1)
         {
            last[e[j]]=i;
            laste[e[j]]=j;
            i=e[j];
            break;
         }
      if (i==t)
      {
         for (min=oo;i!=s;i=last[i])
            min=min(min,r[laste[i]]);
         flow+=min;
         for (i=t;i!=s;i=last[i])
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
            if (e[j]<=n&&r[j])
               min=min(min,dis[e[j]]);
         min=min(min+1,n);
         gap[dis[i]]--;
         dis[i]=min;
         gap[dis[i]]++;
         if (i!=s)
            i=last[i];
      }
   }
   return flow;
}

void dfs(long now)
{
   long i;
   for (i=1;i<=n;i++)
      if (link[now][i])
      {
         link[now][i]--;
         dfs(i);
      }
   rec[++tot]=now;
}

int main()
{
   long i,j,m,t,a,b,c,d,sum=0,ans=0;
   scanf("%ld%ld%ld%ld",&n,&m,&s,&t);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld%ld",&a,&b,&c,&d);
      if (d)
      {
         du[a]-=c;
         du[b]+=c;
         link[a][b]+=c;
      }
      else
         add(a,b,c);
   }
   for (i=1;i<=n;i++)
      if (du[i]>0)
      {
         add(n+1,i,du[i]);
         sum+=du[i];
      }
      else if (du[i]<0)
         add(i,n+2,-du[i]);
   add(t,s,oo);
   if (sap(n+1,n+2,n+2)!=sum)
      puts("0");
   else
   {
      head[s]=next[head[s]];
      head[t]=next[head[t]];
      ans+=r[totm]+sap(s,t,n);
      printf("%ld",ans);
      if (ans)
      {
         for (i=1;i<=n;i++)
            for (j=head[i];j;j=next[j])
               if (e[j]<=n&&!(j&1))
                  link[i][e[j]]+=r[j+1];
         link[t][s]+=ans-1;
         dfs(s);
         sum=0;
         rec[tot+1]=t;
         for (i=tot;i>=1;i--)
         {
            if (rec[i]==s&&rec[i+1]==t)
               sum++;
            printf("%c%ld",(rec[i]==s&&rec[i+1]==t&&sum<=ans)?'\n':' ',rec[i]);
         }
      }
      puts("");
   }
   return 0;
}
