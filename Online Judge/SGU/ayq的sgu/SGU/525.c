#include<math.h>
#include<time.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define oo 1000000000
#define pi 3.14159265359
#define zero(a) (abb(a)<=1e-7)
#define lowbit(a) ((a)&(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abb(a) ((a)>0?(a):(-(a)))
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y2))
#define dj(x1,y1,x2,y2) ((x1)*(y1)+(y1)*(y2))
#define dis(x1,y1,x2,y2) sqrt(((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1)))

long l[1001][1001]={0},head[1001]={0},dfn[1001]={0},low[1001]={0},stack[1001]={0},c[1001]={0},v[1001]={0},num[20001]={0},e[20001]={0},next[20001]={0},rec[20001]={0},d[20001][2]={0};
char go[1001][1001]={0},hash[1001][1001]={0},h2[20001]={0};
long totm=0,top=0,color=0,tot=0;

void add(long a,long b,long c)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   num[totm]=c;
}

void tarjan(long now)
{
   long i;
   stack[++top]=now;
   dfn[now]=low[now]=++tot;
   for (i=head[now];i;i=next[i])
   {
      if (!dfn[e[i]])
      {
         tarjan(e[i]);
         if (low[e[i]]<low[now])
            low[now]=low[e[i]];
      }
      else if (!c[e[i]]&&dfn[e[i]]<low[now])
         low[now]=dfn[e[i]];
   }
   if (dfn[now]==low[now])
   {
      color++;
      do
      {
         c[stack[top--]]=color;
         v[color]++;
      }
      while(stack[top+1]!=now);
   }
}

void dfs(long x,long y)
{
   long i;
   go[x][y]=1;
   for (i=1;i<=color;i++)
      if (l[y][i]&&!go[x][i])
         dfs(x,i);
}

int main()
{
   long i,j,k,n,m,a,b,s=0,ans=1;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld",&a,&b);
      add(a,b,i);
   }
   for (i=1;i<=n;i++)
      if (!dfn[i])
         tarjan(i);
   for (i=1;i<=n;i++)
      for (j=head[i];j;j=next[j])
         if (c[i]!=c[e[j]])
            l[c[i]][c[e[j]]]=1;
   if (color==1)
   {
      printf("%ld\n%ld\n",n,m);
      for (i=1;i<=m;i++)
         printf("%ld%c",i,(i==m)?'\n':' ');
   }
   else
   {
      for (i=1;i<=color;i++)
         dfs(i,i);
      for (i=1;i<=color;i++)
         for (j=1;j<=color;j++)
            if (l[i][j])
            {
               a=0;
               for (k=1;k<=color;k++)
                  if (go[i][k]&go[k][j])
                     a+=v[k];
               if (a>ans)
               {
                  ans=a;
                  s=0;
               }
               if (ans==a)
               {
                  d[++s][0]=i;
                  d[s][1]=j;
               }
            }
      for (i=1;i<=s;i++)
         hash[d[i][0]][d[i][1]]=1;
      for (i=1;i<=n;i++)
         for (j=head[i];j;j=next[j])
            if (hash[c[i]][c[e[j]]])
               h2[num[j]]=1;
      s=0;
      for (i=1;i<=m;i++)
         if (h2[i])
            rec[++s]=i;
      printf("%ld\n%ld\n",ans,s);
      for (i=1;i<=s;i++)
         printf("%ld%c",rec[i],(i==s)?'\n':' ');
   }
   return 0;
}
