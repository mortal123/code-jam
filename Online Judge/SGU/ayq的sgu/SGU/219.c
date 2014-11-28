#include<stdio.h>
#include<stdlib.h>
#include<string.h>

long e[50001]={0},next[50001]={0},v[50001]={0},head[1001]={0},dfn[1001]={0},low[1001]={0},stack[1001]={0},c[1001]={0},du[1001]={0},d[1001]={0},e2[50001]={0},next2[50001]={0},head2[1001]={0};
char hash[1001]={'\0'},belong[1001]={'\0'};
long totm=0,tot=0,color=0,top=0;

void add(long a,long b,long x)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   v[totm]=x;
}

void add2(long a,long b)
{
   e2[++totm]=b;
   next2[totm]=head2[a];
   head2[a]=totm;
}

void search(long now)
{
   long i,s=1;
   belong[now]=0;
   for (i=head[now];i;i=next[i])
      if (belong[e[i]]&&!v[i])
      {
         du[e[i]]--;
         if (!du[e[i]])
            search(e[i]);
      }
}

void targan(long now)
{
   long i,j,p;
   stack[++top]=now;
   dfn[now]=low[now]=++tot;
   for (i=head[now];i;i=next[i])
   {
      if (!dfn[e[i]])
      {
         targan(e[i]);
         if (low[e[i]]<low[now])
            low[now]=low[e[i]];
      }
      else if (!c[e[i]]&&dfn[e[i]]<low[now])
         low[now]=dfn[e[i]];
   }
   if (low[now]==dfn[now])
   {
      memset(belong,'\0',sizeof(belong));
      color++;
      p=0;
      do
      {
         c[stack[top]]=color;
         belong[stack[top]]=1;
         d[++p]=stack[top];
         du[stack[top--]]=0;
      }while (stack[top+1]!=now);
      for (i=1;i<=p;i++)
         for (j=head[d[i]];j;j=next[j])
            if (!v[j]&&belong[e[j]])
               du[e[j]]++;
      for (i=1;i<=p;i++)
         if (!du[d[i]])
            search(d[i]);
      for (i=1;i<=p&&!du[d[i]];i++);
      hash[color]=(i>p);
   }
}

int main()
{
   long i,j,n,m,a,b,x,now,st=1,en=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld",&a,&b,&x);
      add(a,b,x);
   }
   for (i=1;i<=n;i++)
      if (!dfn[i])
         targan(i);
   totm=0;
   memset(du,0,sizeof(du));
   for (i=1;i<=n;i++)
      for (j=head[i];j;j=next[j])
         if (c[i]!=c[e[j]])
         {
            add2(c[i],c[e[j]]);
            du[c[e[j]]]++;
         }
   for (i=1;i<=color;i++)
      if (!du[i])
         d[++en]=i;
   while (st<=en)
   {
      now=d[st++];
      for (i=head2[now];i;i=next2[i])
      {
         du[e2[i]]--;
         if (!hash[now])
            hash[e2[i]]=0;
         if (!du[e2[i]])
            d[++en]=e2[i];
      }
   }
   for (i=1;i<=n;i++)
      printf("%ld\n",hash[c[i]]);
   return 0;
}
