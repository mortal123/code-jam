#include<stdio.h>

struct case1
{
   long x1,y1,x2,y2;
   char c;
}s[5001]={{0,0,0,0},{'\0'}};
struct case2
{
   long st,en,c,flag;
}p[40001]={{0,0,0,0}};
long ans=0;

void build(long now,long st,long en)
{
   long mid=(st+en)>>1;
   p[now].c=p[now].flag=0;
   p[now].st=st;
   p[now].en=en;
   if (st<en-1)
   {
      build(now<<1,st,mid);
      build((now<<1)+1,mid,en);
   }
}

void maintain(long now)
{
   if (p[now].flag)
   {
      p[now<<1].flag=p[(now<<1)+1].flag=p[now].flag;
      p[now<<1].c=p[(now<<1)+1].c=((p[now].flag)&1);
      p[now].flag=0;
   }
}

void ins(long now,long st,long en,long c)
{
   long mid=(p[now].st+p[now].en)>>1;
   if (p[now].st==st&&p[now].en==en)
   {
      p[now].c=c;
      p[now].flag=1+!c;
   }
   else
   {
      maintain(now);
      if (en<=mid)
         ins(now<<1,st,en,c);
      else if (st>=mid)
         ins((now<<1)+1,st,en,c);
      else
      {
         ins(now<<1,st,mid,c);
         ins((now<<1)+1,mid,en,c);
      }
   }
}

void dfs(long now)
{
   if (p[now].st==p[now].en-1)
      ans+=!(p[now].c);
   else
   {
      maintain(now);
      dfs(now<<1);
      dfs((now<<1)+1);
   }
}

int main()
{
   long i,j,n,m,t;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld%ld %c",&s[i].x1,&s[i].y1,&s[i].x2,&s[i].y2,&s[i].c);
      if (s[i].x1>s[i].x2)
      {
         t=s[i].x1;
         s[i].x1=s[i].x2;
         s[i].x2=t;
      }
      if (s[i].y1>s[i].y2)
      {
         t=s[i].y1;
         s[i].y1=s[i].y2;
         s[i].y2=t;
      }
   }
   for (i=1;i<=n;i++)
   {
      build(1,1,n+1);
      for (j=1;j<=m;j++)
         if (s[j].x1<=i&&s[j].x2>=i)
            ins(1,s[j].y1,s[j].y2+1,s[j].c=='b');
      dfs(1);
   }
   printf("%ld\n",ans);
   return 0;
}
