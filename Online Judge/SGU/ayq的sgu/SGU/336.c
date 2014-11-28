#include <stdio.h>
#define lowbit(a) ((a)&(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   long x,y,s,num;
}p[1000001]={0,0,0,0};
struct case2
{
   long x,y,s;
}que[200001]={0,0,0};
long ans[200001]={0},tree[100001]={0},pos[100001]={0},l[200001]={0},r[200001]={0},head[200001]={0},e[200001]={0},next[200001]={0};
char hash[200001]={0},str[101]={0};
long n,totm=0,dfn=0;

void add(long a,long b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
}

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&(p[j].x>t.x||p[j].x==t.x&&p[j].y>t.y||p[j].x==t.x&&p[j].y==t.y&&p[j].s&&t.s==0))
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&(p[i].x<t.x||p[i].x==t.x&&p[i].y<t.y||p[i].x==t.x&&p[i].y==t.y&&t.s&&p[i].s==0))
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

void ins(long i)
{
   for (;i<=n;i+=lowbit(i))
      tree[i]++;
}

long sum(long i)
{
   long s=0;
   for (;i;i-=lowbit(i))
      s+=tree[i];
   return s;
}

void dfs(long now)
{
   long i;
   if (now<=n)
      pos[now]=++dfn;
   for (i=head[now];i;i=next[i])
      dfs(e[i]);
}

int main()
{
   long i,j,m,s,x,q=0,tot;
   scanf("%ld%ld\n",&n,&m);
   for (i=1;i<=m;i++)
   {
      gets(str+1);
      for (j=1;str[j]>='0'&&str[j]<='9';j++)
         p[i].x=p[i].x*10+str[j]-'0';
      for (j++;str[j]>='0'&&str[j]<='9';j++)
         p[i].y=p[i].y*10+str[j]-'0';
   }
   tot=n;
   s=m;
   scanf("%ld\n",&x);
   for (i=1;i<=x;i++)
   {
      gets(str+1);
      for (j=1;str[j]>='0'&&str[j]<='9';j++)
         que[i].s=que[i].s*10+str[j]-'0';
      for (j++;str[j]>='0'&&str[j]<='9';j++)
         que[i].x=que[i].x*10+str[j]-'0';
      for (j++;str[j]>='0'&&str[j]<='9';j++)
         que[i].y=que[i].y*10+str[j]-'0';
      if (que[i].s==2)
      {
         add(++tot,que[i].x);
         add(tot,que[i].y);
         hash[que[i].x]=hash[que[i].y]=1;
      }
   }
   for (i=1;i<=tot;i++)
      if (!hash[i])
         dfs(i);
   for (i=1;i<=m;i++)
   {
      p[i].x=pos[p[i].x];
      p[i].y=pos[p[i].y];
   }
   tot=n;
   for (i=1;i<=n;i++)
      l[i]=r[i]=pos[i];
   for (i=1;i<=x;i++)
      if (que[i].s==1)
      {
         p[++s]=(struct case1){r[que[i].x],r[que[i].y],1,++q};
         p[++s]=(struct case1){l[que[i].x]-1,l[que[i].y]-1,1,q};
         p[++s]=(struct case1){l[que[i].x]-1,r[que[i].y],-1,q};
         p[++s]=(struct case1){r[que[i].x],l[que[i].y]-1,-1,q};
      }
      else
      {
         l[++tot]=min(l[que[i].x],l[que[i].y]);
         r[tot]=max(r[que[i].x],r[que[i].y]);
      }
   qs(1,s);
   for (i=1;i<=s;i++)
      if (p[i].s==1)
         ans[p[i].num]+=sum(p[i].y);
      else if (p[i].s==-1)
         ans[p[i].num]-=sum(p[i].y);
      else
         ins(p[i].y);
   for (i=1;i<=q;i++)
      puts(ans[i]?"YES":"NO");
   return 0;
}
