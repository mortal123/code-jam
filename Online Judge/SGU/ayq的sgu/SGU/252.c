#include <stdio.h>
#define oo 1000000000

long go[101]={0},head[203]={0},last[203]={0},laste[203]={0},dis[203]={0},e[2402]={0},next[2402]={0},r[2402]={0},v[2402]={0},d[100001]={0},rec[101][101]={0};
char hash[203]={'\0'};
long totm=1;

void add(long a,long b,long c)
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

int main()
{
   long i,j,k,n,m,a,b,c,st,en,now,tot=0,ans=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
   {
      add(1,i+1,0);
      add(i+n+1,2*n+2,0);
   }
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld",&a,&b,&c);
      add(a+1,b+n+1,c);
   }
   while (1)
   {
      for (i=2;i<=2*n+2;i++)
         dis[i]=oo;
      st=en=d[1]=1;
      while (st<=en)
      {
         now=d[st++];
         hash[now]=0;
         for (i=head[now];i;i=next[i])
            if (r[i]&&dis[e[i]]>dis[now]+v[i])
            {
               dis[e[i]]=dis[now]+v[i];
               last[e[i]]=now;
               laste[e[i]]=i;
               if (!hash[e[i]])
               {
                  d[++en]=e[i];
                  hash[e[i]]=1;
               }
            }
      }
      if (dis[2*n+2]==oo)
         break;
      ans+=dis[2*n+2];
      for (i=2*n+2;last[i];i=last[i])
      {
         r[laste[i]]--;
         r[laste[i]^1]++;
      }
   }
   for (i=1;i<=n;i++)
   {
      for (j=head[i+1];j&&(e[j]==1||r[j]);j=next[j]);
      if (j)
      {
         go[i]=e[j]-n-1;
         hash[e[j]-n-1]=1;
      }
   }
   for (i=1;i<=n;i++)
      if (!hash[i])
      {
         tot++;
         for (j=i;j;j=go[j])
            rec[tot][++rec[tot][0]]=j;
      }
   printf("%ld %ld\n",tot,ans);
   for (i=1;i<=tot;i++)
   {
      printf("%ld",rec[i][0]);
      for (j=1;j<=rec[i][0];j++)
         printf(" %ld",rec[i][j]);
      printf("\n");
   }
   return 0;
}
