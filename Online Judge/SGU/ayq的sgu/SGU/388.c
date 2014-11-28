#include <stdio.h>

int sy[201],d[1000001],in[201],last[201],laste[201],dis[201],head[201],next[40202],e[40202],v[40202],r[40202],c[101],q1[10001][2],q2[10001][2];
char hash[201],link[101][101];
int n,totm=1;

void add(int a,int b,int c)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   r[totm]=1;
   v[totm]=c;
   e[++totm]=a;
   next[totm]=head[b];
   head[b]=totm;
   v[totm]=-c;
}

void dfs(int now,int v)
{
   int i;
   c[now]=v;
   for (i=1;i<=n;i++)
      if (link[now][i]&&!c[i])
         dfs(i,3-v);
}

int main()
{
   int i,j,m1,m2,st,en,now,flag,s1=0,s2=0,ans=0;
   scanf("%d%d%d",&n,&m1,&m2);
   for (i=1;i<=m1;i++)
   {
      scanf("%d%d",&q1[i][0],&q1[i][1]);
      link[q1[i][0]][q1[i][1]]=link[q1[i][1]][q1[i][0]]=1;
   }
   for (i=1;i<=m2;i++)
   {
      scanf("%d%d",&q2[i][0],&q2[i][1]);
      link[q2[i][0]][q2[i][1]]=link[q2[i][1]][q2[i][0]]=1;
   }
   for (i=1;i<=n;i++)
   {
      if (!c[i])
         dfs(i,1);
      add(i,i+n,0);
   }
   for (i=1;i<=m1;i++)
      if (c[q1[i][0]]==1)
         add(q1[i][0]+n,q1[i][1],1);
      else
         add(q1[i][1]+n,q1[i][0],1);
   for (i=1;i<=m2;i++)
      if (c[q2[i][0]]==1)
         add(q2[i][1]+n,q2[i][0],1);
      else
         add(q2[i][0]+n,q2[i][1],1);
   while (1)
   {
      st=300001;
      en=300000;
      for (i=1;i<=2*n;i++)
      {
         dis[i]=last[i]=0;
         hash[i]=in[i]=1;
         d[++en]=i;
      }
      while (st<=en)
      {
         now=d[st++];
         hash[now]=0;
         for (i=head[now];i;i=next[i])
            if (r[i]&&dis[now]+v[i]>dis[e[i]])
            {
               last[e[i]]=now;
               laste[e[i]]=i;
               dis[e[i]]=dis[now]+v[i];
               if (!hash[e[i]])
               {
                  in[e[i]]++;
                  if (in[e[i]]>2*n)
                     goto out;
                  hash[e[i]]=1;
                  if (dis[e[i]]>dis[d[st]])
                     d[--st]=e[i];
                  else
                     d[++en]=e[i];
               }
            }
      }
      break;
      out:
      flag=0;
      memset(sy,0,sizeof(sy));
      for (i=1;i<=2*n;i++)
         if (!sy[i])
         {
            flag++;
            for (j=i;j&&!sy[j];j=last[j])
               sy[j]=flag;
            if (sy[j]==flag)
            {
               now=j;
               break;
            }
         }
      ans+=v[laste[now]];
      r[laste[now]]=0;
      r[laste[now]^1]=1;
      for (i=last[now];i!=now;i=last[i])
      {
         ans+=v[laste[i]];
         r[laste[i]]=0;
         r[laste[i]^1]=1;
      }
   }
   printf("%d\n",ans>>1);
   for (i=n+1;i<=2*n;i++)
      for (j=head[i];j;j=next[j])
         if (!r[j]&&e[j]!=i-n)
            if (c[i-n]==1)
            {
               q1[++s1][0]=i-n;
               q1[s1][1]=e[j];
            }
            else
            {
               q2[++s2][0]=e[j];
               q2[s2][1]=i-n;
            }
   for (i=1;i<=ans>>1;i++)
      printf("%d %d\n",q1[i][0],q1[i][1]);
   for (i=1;i<=ans>>1;i++)
      printf("%d %d\n",q2[i][0],q2[i][1]);
   return 0;
}
