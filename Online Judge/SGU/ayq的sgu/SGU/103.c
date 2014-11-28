#include<stdio.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   long b,p,st;
}port[301]={0};
long e[28001]={0},next[28001]={0},dis[28001]={0},head[301]={0},f[301]={0},ans[301]={0},last[301]={0},d[200001]={0};
char hash[301]={'\0'};
long totm=0;

void add(long a,long b,long v)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   dis[totm]=v;
}

long wait(long st,long a,long b)
{
   long i,l1,l2,temp,t=st;
   for (i=1;i<=4;i++)
   {
      l1=((t+port[a].st)%(port[a].b+port[a].p)<port[a].b);
      l2=((t+port[b].st)%(port[b].b+port[b].p)<port[b].b);
      if (l1==l2)
         return t-st;
      temp=t+port[a].p+port[a].b-(t+port[a].st)%(port[a].b+port[a].p);
      if (l1)
         temp-=port[a].p;
      if (l2)
         temp=min(temp,t+port[b].b-(t+port[b].st)%(port[b].b+port[b].p));
      else
         temp=min(temp,t+port[b].p+port[b].b-(t+port[b].st)%(port[b].b+port[b].p));
      t=temp;
   }
   return oo;
}

int main()
{
   long i,s,t,n,m,a,b,v,w,now,p=0,st=50000,en=50000;
   char ch;
   scanf("%ld%ld%ld%ld\n",&s,&t,&n,&m);
   for (i=1;i<=n;i++)
   {
      scanf("%c%ld%ld%ld\n",&ch,&a,&port[i].b,&port[i].p);
      port[i].st=port[i].b+port[i].p-a;
      if (ch=='B')
         port[i].st-=port[i].p;
   }
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld",&a,&b,&v);
      add(a,b,v);
      add(b,a,v);
   }
   for (i=1;i<=n;i++)
      f[i]=oo;
   f[s]=0;
   d[st]=s;
   while (st<=en)
   {
      now=d[st++];
      hash[now]=0;
      for (i=head[now];i;i=next[i])
         if (f[e[i]]>f[now]+dis[i])
         {
            w=wait(f[now],now,e[i]);
            if (f[e[i]]>f[now]+dis[i]+w)
            {
               f[e[i]]=f[now]+dis[i]+w;
               last[e[i]]=now;
               if (!hash[e[i]])
               {
                  hash[e[i]]=1;
                  if (f[e[i]]<f[d[st]])
                     d[--st]=e[i];
                  else
                     d[++en]=e[i];
               }
            }
         }
   }
   if (f[t]<oo)
   {
      for (i=t;i;i=last[i])
         ans[++p]=i;
      printf("%ld\n%ld",f[t],ans[p]);
      for (p--;p>=1;p--)
         printf(" %ld",ans[p]);
   }
   else
      printf("0");
   printf("\n");
   return 0;
}
