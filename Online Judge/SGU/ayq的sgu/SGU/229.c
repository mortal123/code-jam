#include <stdio.h>

struct case1
{
   long x,y;
}p[401]={{0,0}};
long head[401]={0},e[801]={0},next[801]={0},f[401]={0},hash[401]={0},map[21][21]={0},link[401][401]={0};
char belong[401]={'\0'};
long totm,flag=0,s=0;

void add(long a,long b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   e[++totm]=a;
   next[totm]=head[b];
   head[b]=totm;
   link[a][b]=1;
   link[b][a]=0;
}

void dfs(long now,long c)
{
   long i;
   belong[now]=c;
   for (i=head[now];i;i=next[i])
      if (!belong[e[i]])
         dfs(e[i],3-c);
}

long match(long now)
{
   long i;
   for (i=head[now];i;i=next[i])
      if (belong[e[i]]==2&&hash[e[i]]!=flag)
      {
         hash[e[i]]=flag;
         if (!f[e[i]]||match(f[e[i]]))
         {
            f[e[i]]=now;
            return 1;
         }
      }
   return 0;
}

long check()
{
   long i;
   memset(f,0,sizeof(f));
   memset(belong,'\0',sizeof(belong));
   for (i=1;i<=s;i++)
      if (!belong[i])
         dfs(i,1);
   for (i=1;i<=s;i++)
      if (belong[i]==1)
      {
         flag++;
         if (!match(i))
            return 0;
      }
   return 1;
}

int main()
{
   long i,j,n,a,x,y;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
      {
         scanf("%1ld",&a);
         if (a)
         {
            p[++s]=(struct case1){i,j};
            map[i][j]=s;
         }
      }
   for (i=2;i<=s;i++)
   {
      totm=0;
      memset(head,0,sizeof(head));
      for (j=1;j<=s;j++)
         if (j!=i)
         {
            x=p[i].x+p[j].x-p[1].x;
            y=p[i].y+p[j].y-p[1].y;
            if (x>=1&&x<=n&&y>=1&&y<=n&&map[x][y]>1)
               add(j,map[x][y]);
         }
      if (check())
         break;
      totm=0;
      memset(head,0,sizeof(head));
      for (j=1;j<=s;j++)
         if (j!=i)
         {
            x=p[i].x-p[j].y+p[1].y;
            y=p[i].y+p[j].x-p[1].x;
            if (x>=1&&x<=n&&y>=1&&y<=n&&map[x][y]>1)
               add(j,map[x][y]);
         }
      if (check())
         break;
      totm=0;
      memset(head,0,sizeof(head));
      for (j=1;j<=s;j++)
         if (j!=i)
         {
            x=p[i].x+p[j].y-p[1].y;
            y=p[i].y-p[j].x+p[1].x;
            if (x>=1&&x<=n&&y>=1&&y<=n&&map[x][y]>1)
               add(j,map[x][y]);
         }
      if (check())
         break;
      totm=0;
      memset(head,0,sizeof(head));
      for (j=1;j<=s;j++)
         if (j!=i)
         {
            x=p[i].x-p[j].x+p[1].x;
            y=p[i].y-p[j].y+p[1].y;
            if (x>=1&&x<=n&&y>=1&&y<=n&&map[x][y]>1)
               add(j,map[x][y]);
         }
      if (check())
         break;
   }
   if (i<=s||!s)
   {
      out:
      printf("YES\n");
      for (i=1;i<=s;i++)
         if (belong[i]==2)
         {
            map[p[i].x][p[i].y]=link[f[i]][i];
            map[p[f[i]].x][p[f[i]].y]=link[i][f[i]];
         }
      for (i=1;i<=n;i++)
      {
         for (j=1;j<=n;j++)
            printf("%ld",map[i][j]);
         printf("\n");
      }
   }
   else
      printf("NO\n");
   return 0;
}
