#include <stdio.h>
#define oo 1000000000
#define dis(a,b) ((p[a].x-p[b].x)*(p[a].x-p[b].x)+(p[a].y-p[b].y)*(p[a].y-p[b].y))

struct case1
{
   long x,y,c;
}p[51]={0,0,0};
long dl[10005]={0},gap[10005]={0},last[10005]={0},laste[10005]={0},head[10005]={0},dis[10005]={0},e[2000001]={0},next[2000001]={0},r[2000001]={0},f[2000001]={0};
long n,m,d,w,totm=1;

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

long check(long now)
{
   long i,j,min,st=1,en=1,tot=2*n*(now-1)+2,ans=0;
   for (i=2;i<=totm;i++)
      f[i]=0;
   for (i=1;i<=n;i++)
   {
      add(i+(now-2)*2*n+2,i+n+(now-2)*2*n+2,p[i].c);
      if (p[i].y<=d)
         add(1,i+(now-2)*2*n+2,oo);
      if (p[i].y+d>=w)
         add(i+n+(now-2)*2*n+2,2,oo);
      if (now>2)
         for (j=1;j<=n;j++)
            if (dis(i,j)<=d*d)
               add(i+n+(now-3)*2*n+2,j+(now-2)*2*n+2,oo);
   }
   for (i=0;i<=tot;i++)
      gap[i]=dis[i]=0;
   dl[1]=2;
   while (st<=en)
   {
      gap[dis[dl[st]]]++;
      for (i=head[dl[st]];i;i=next[i])
         if (e[i]!=2&&!dis[e[i]])
         {
            dis[e[i]]=dis[dl[st]]+1;
            dl[++en]=e[i];
         }
      st++;
   }
   if (!dis[1])
      return 0;
   for (i=1;dis[1]<tot;)
   {
      for (j=head[i];j;j=next[j])
         if (r[j]-f[j]&&dis[e[j]]==dis[i]-1)
         {
            last[e[j]]=i;
            laste[e[j]]=j;
            i=e[j];
            break;
         }
      if (i==2)
      {
         for (min=oo;last[i];i=last[i])
            if (r[laste[i]]-f[laste[i]]<min)
               min=r[laste[i]]-f[laste[i]];
         ans+=min;
         if (ans>=m)
            return 1;
         for (i=2;last[i];i=last[i])
         {
            f[laste[i]]+=min;
            f[laste[i]^1]-=min;
         }
      }
      else if (!j)
      {
         if (gap[dis[i]]==1)
            break;
         min=oo;
         for (j=head[i];j;j=next[j])
            if (r[j]-f[j]&&dis[e[j]]<min)
               min=dis[e[j]];
         min++;
         if (min>tot)
            min=tot;
         gap[dis[i]]--;
         dis[i]=min;
         gap[dis[i]]++;
         if (i!=1)
            i=last[i];
      }
   }
   return 0;
}

int main()
{
   long i;
   scanf("%ld%ld%ld%ld",&n,&m,&d,&w);
   if (d>=w)
      puts("1");
   else
   {
      for (i=1;i<=n;i++)
      scanf("%ld%ld%ld",&p[i].x,&p[i].y,&p[i].c);
      for (i=2;!check(i)&&i<=n+m;i++);
      if (i<=n+m)
         printf("%ld\n",i);
      else
         puts("IMPOSSIBLE");
   }
   return 0;
}
