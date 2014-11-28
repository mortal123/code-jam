#include <stdio.h>

long head[10001]={0},e[200001]={0},next[200001]={0},d[10001]={0},dis[10001]={0},da[10001]={0},db[10001]={0},last[10001]={0};
char hash[10001]={'\0'},visit[10001]={'\0'},mark[10001]={'\0'};
long totm=0,ans=0,flag=0;

void add(long a,long b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
}

long find(long root,long now,long h)
{
   long i;
   if (mark[now]==2&&now!=root||hash[now])
      return 0;
   hash[now]=1;
   if (h==1)
      return mark[now]==1;
   for (i=head[now];i;i=next[i])
      if (dis[e[i]]==h-1&&find(root,e[i],h-1))
      {
         last[e[i]]=now;
         return 1;
      }
   return 0;
}

int main()
{
   long i,j,n,m,a,b,now,st=1,en=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld",&a,&b);
      add(a,b);
      add(b,a);
   }
   scanf("%ld",&a);
   for (i=1;i<=a;i++)
   {
      scanf("%ld",&da[i]);
      d[++en]=da[i];
      dis[da[i]]=mark[da[i]]=1;
   }
   scanf("%ld",&b);
   for (i=1;i<=b;i++)
   {
      scanf("%ld",&db[i]);
      mark[db[i]]=2;
   }
   while (st<=en)
   {
      now=d[st++];
      visit[now]=1;
      if (!flag||dis[now]==flag-1)
         for (i=head[now];i;i=next[i])
            if (!dis[e[i]])
            {
               dis[e[i]]=dis[now]+1;
               if (mark[e[i]]==2)
                  flag=dis[e[i]];
               d[++en]=e[i];
            }
   }
   for (i=1;i<=b;i++)
      if (visit[db[i]])
         ans+=find(db[i],db[i],flag);
   printf("%ld %ld\n",ans,flag-1);
   for (i=1;i<=a;i++)
      if (last[da[i]])
         for (j=da[i];j;j=last[j])
            printf("%ld%c",j,(last[j])?' ':'\n');
   return 0;
}
