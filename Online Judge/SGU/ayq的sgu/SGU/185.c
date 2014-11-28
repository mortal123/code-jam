#include <stdio.h>
#define oo 1000000000

long head[401]={0},next[320002]={0},dis[401]={0},last[401]={0},laste[401]={0},ans[2][401]={0},tot[2]={0};
char r[320002]={'\0'},hash[401]={'\0'},str[41]={'\0'};
short e[320002]={0},d[500001]={0},v[320002]={0};
long n,totm=1,s=0,t;

void add(long a,long b,long c)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   v[totm]=c;
   r[totm]=1;
   e[++totm]=a;
   next[totm]=head[b];
   head[b]=totm;
   v[totm]=-c;
}

long spfa()
{
   long i,now,st=100000,en=100000;
   for(i=2;i<=n;i++)
      dis[i]=oo;
   d[st]=1;
   while (st<=en)
   {
      now=d[st++];
      hash[now]=0;
      for(i=head[now];i;i=next[i])
         if(r[i]&&dis[now]+v[i]<dis[e[i]])
         {
            dis[e[i]]=dis[now]+v[i];
            last[e[i]]=now;
            laste[e[i]]=i;
            if(!hash[e[i]]&&dis[e[i]]<dis[n])
            {
               hash[e[i]]=1;
               if(dis[e[i]]<=dis[d[st]])
                  d[--st]=e[i];
               else
                  d[++en]=e[i];
            }
         }
   }
   if(dis[n]>=oo)
      return 0;
   t=dis[n];
   s+=dis[n];
   for(i=n;last[i];i=last[i])
   {
      r[laste[i]]--;
      r[laste[i]^1]++;
   }
   return 1;
}

void dfs(long now,long t)
{
   long i;
   ans[t][++tot[t]]=now;
   if(now==n)
      return;
   for(i=head[now];i;i=next[i])
      if(!r[i]&&v[i]>0)
      {
         r[i]=1;
         dfs(e[i],t);
         break;
      }
}

int main()
{
   long m,i,j,a,b,c;
   scanf("%ld%ld\n",&n,&m);
   for(i=1;i<=m;i++)
   {
      gets(str);
      a=b=c=0;
      for (j=0;str[j]>='0'&&str[j]<='9';j++)
         a=a*10+str[j]-'0';
      for (j++;str[j]>='0'&&str[j]<='9';j++)
         b=b*10+str[j]-'0';
      for (j++;str[j]>='0'&&str[j]<='9';j++)
         c=c*10+str[j]-'0';
      add(a,b,c);
      add(b,a,c);
   }
   if (!spfa()||!spfa()||2*t!=s)
      printf("No solution\n");
   else
   {
      dfs(1,0);
      dfs(1,1);
      for (i=1;i<=tot[0];i++)
         printf("%ld%c",ans[0][i],(i==tot[0])?'\n':' ');
      for (i=1;i<=tot[1];i++)
         printf("%ld%c",ans[1][i],(i==tot[1])?'\n':' ');
   }
   return 0;
}
