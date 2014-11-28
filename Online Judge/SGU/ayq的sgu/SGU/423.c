#include <stdio.h>
#define oo 1000000000
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

int hash[14],mi[14],p[14],tot[8193],g[2000001][2];
char link[14][14],f[2000001];
int n,sy=0,ans=-oo;

int dfs();

int find(int now,int left,int s,int t,int cur,int v,int flag)
{
   int i,j,y=0,x=0;
   if (now>n)
   {
      x=0;
      sy++;
      for (i=1;i<=n;i++)
         if (cur&(1<<i-1))
         {
            x-=p[i];
            y+=mi[i];
            for (j=1;j<=n;j++)
               if (link[i][j])
                  hash[j]=sy;
         }
      for (i=1;i<=n;i++)
         x+=(hash[i]==sy)*(!!(s&(1<<i-1))-!!(t&(1<<i-1)))*p[i];
      if (x>0)
      {
         if (!flag)
         {
            x=dfs(v+y,1);
            g[v][0]=max(g[v][0],x);
         }
         else
         {
            x=dfs(v+2*y,0);
            g[v][1]=min(g[v][1],x);
         }
         return 1;
      }
      return 0;
   }
   else
   {
      if (find(now+1,left,s,t,cur,v,flag))
         x=1;
      if ((left&(1<<now-1))&&find(now+1,left,s,t,cur+(1<<now-1),v,flag))
         x=1;
   }
   return x;
}

int dfs(int v,int flag)
{
   int i,a,b,x=v,s=0,t=0;
   for (i=1;i<=n;i++)
   {
      if (x%3==1)
         s+=(1<<i-1);
      else if (x%3==2)
         t+=(1<<i-1);
      x/=3;
   }
   if (f[v])
      return g[v][flag];
   f[v]=1;
   g[v][0]=-oo;
   g[v][1]=oo;
   a=find(1,(1<<n)-1-s-t,s,t,0,v,0);
   b=find(1,(1<<n)-1-s-t,t,s,0,v,1);
   if (!a&&!b)
      g[v][0]=g[v][1]=tot[s]-tot[t];
   else if (!a)
      g[v][0]=g[v][1];
   else if (!b)
      g[v][1]=g[v][0];
   else
   {
      a=g[v][0];
      b=g[v][1];
      g[v][0]=max(g[v][0],b);
      g[v][1]=min(g[v][1],a);
   }
   return g[v][flag];
}

int main()
{
   int i,j,s,t;
   scanf("%d%d%d",&n,&s,&t);
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
         scanf("%1d",&link[i][j]);
   mi[1]=1;
   for (i=1;i<=n;i++)
      scanf("%d",&p[i]);
   for (i=2;i<=n;i++)
      mi[i]=mi[i-1]*3;
   for (i=0;i<1<<n;i++)
      for (j=1;j<=n;j++)
         tot[i]+=!!(i&(1<<j-1))*p[j];
   printf("%d\n",dfs(mi[s]+2*mi[t],0));
   return 0;
}
