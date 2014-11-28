#include <stdio.h>
#include <string.h>
#define oo 100000
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   long x,y;
}d[226]={0,0},p[226][226]={0,0};
long l[4][2]={{1,0},{-1,0},{0,1},{0,-1}},dis[16][16][16][16]={0},out[16][16]={0},r[226]={0};
char map[17][17]={0},tmp[17][17]={0};
long n,m;

void bfs(long x,long y)
{
   long i,j,px,py,st=1,en=1;
   struct case1 now;
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         dis[x][y][i][j]=oo;
   dis[x][y][x][y]=0;
   d[1]=(struct case1){x,y};
   while (st<=en)
   {
      now=d[st++];
      for (i=0;i<4;i++)
      {
         px=now.x+l[i][0];
         py=now.y+l[i][1];
         if (px&&py&&px<=n&&py<=m&&dis[x][y][px][py]==oo&&map[px][py]!='X')
         {
            dis[x][y][px][py]=dis[x][y][now.x][now.y]+1;
            d[++en]=(struct case1){px,py};
         }
      }
   }
   out[x][y]=oo;
   for (i=1;i<=n;i++)
   {
      out[x][y]=min(out[x][y],dis[x][y][i][1]);
      out[x][y]=min(out[x][y],dis[x][y][i][m]);
   }
   for (i=2;i<m;i++)
   {
      out[x][y]=min(out[x][y],dis[x][y][1][i]);
      out[x][y]=min(out[x][y],dis[x][y][n][i]);
   }
}

void dfs(long x,long y,long c)
{
   long i,px,py;
   p[c][++r[c]]=(struct case1){x,y};
   map[x][y]='.';
   for (i=0;i<4;i++)
   {
      px=x+l[i][0];
      py=y+l[i][1];
      if (px&&py&&px<=n&&py<=m&&map[px][py]=='X')
         dfs(px,py,c);
   }
}

int main()
{
   long i,j,k,a,b,r1,r2,x,y,x2,y2,t1,t2,s=0,ans=oo;
   scanf("%ld%ld\n",&n,&m);
   for (i=1;i<=n;i++)
   {
      gets(map[i]+1);
      strcpy(tmp[i]+1,map[i]+1);
   }
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         bfs(i,j);
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         if (map[i][j]=='X')
            dfs(i,j,++s);
   for (i=1;i<s;i++)
      for (j=i+1;j<=s;j++)
      {
         t1=t2=oo;
         for (k=1;k<=r[i];k++)
            t1=min(t1,out[p[i][k].x][p[i][k].y]);
         for (k=1;k<=r[j];k++)
            t2=min(t2,out[p[j][k].x][p[j][k].y]);
         if (t1+t2<ans)
         {
            ans=t1+t2;
            r1=i;
            r2=j;
            x=y=0;
         }
         for (a=1;a<=n;a++)
            for (b=1;b<=m;b++)
               if (tmp[a][b]=='.')
               {
                  t1=t2=oo;
                  for (k=1;k<=r[i];k++)
                     t1=min(t1,dis[p[i][k].x][p[i][k].y][a][b]);
                  for (k=1;k<=r[j];k++)
                     t2=min(t2,dis[p[j][k].x][p[j][k].y][a][b]);
                  if (t1+t2+out[a][b]-1<ans)
                  {
                     ans=t1+t2+out[a][b]-1;
                     r1=i;
                     r2=j;
                     x=a;
                     y=b;
                  }
               }
      }
   if (!x&&!y)
   {
      x=1;
      for (i=2;i<=r[r1];i++)
         if (out[p[r1][i].x][p[r1][i].y]<out[p[r1][x].x][p[r1][x].y])
            x=i;
      y=p[r1][x].y;
      x=p[r1][x].x;
      while (1)
      {
         for (i=0;i<4;i++)
         {
            t1=x+l[i][0];
            t2=y+l[i][1];
            if (t1&&t2&&t1<=n&&t2<=m&&out[t1][t2]==out[x][y]-1&&tmp[t1][t2]!='X')
            {
               x=t1;
               y=t2;
               break;
            }
         }
         tmp[x][y]='*';
         if (!out[x][y])
            break;
      }
      x=1;
      for (i=2;i<=r[r2];i++)
         if (out[p[r2][i].x][p[r2][i].y]<out[p[r2][x].x][p[r2][x].y])
            x=i;
      y=p[r2][x].y;
      x=p[r2][x].x;
      while (1)
      {
         for (i=0;i<4;i++)
         {
            t1=x+l[i][0];
            t2=y+l[i][1];
            if (t1&&t2&&t1<=n&&t2<=m&&out[t1][t2]==out[x][y]-1&&tmp[t1][t2]!='X')
            {
               x=t1;
               y=t2;
               break;
            }
         }
         tmp[x][y]='*';
         if (!out[x][y])
            break;
      }
   }
   else
   {
      x2=x;
      y2=y;
      x=1;
      for (i=2;i<=r[r1];i++)
         if (dis[p[r1][i].x][p[r1][i].y][x2][y2]<dis[p[r1][x].x][p[r1][x].y][x2][y2])
            x=i;
      y=p[r1][x].y;
      x=p[r1][x].x;
      while (dis[x][y][x2][y2])
      {
         for (i=0;i<4;i++)
         {
            t1=x+l[i][0];
            t2=y+l[i][1];
            if (t1&&t2&&t1<=n&&t2<=m&&dis[t1][t2][x2][y2]==dis[x][y][x2][y2]-1&&tmp[t1][t2]!='X')
            {
               x=t1;
               y=t2;
               break;
            }
         }
         tmp[x][y]='*';
      }
      x=1;
      for (i=2;i<=r[r2];i++)
         if (dis[p[r2][i].x][p[r2][i].y][x2][y2]<dis[p[r2][x].x][p[r2][x].y][x2][y2])
            x=i;
      y=p[r2][x].y;
      x=p[r2][x].x;
      while (dis[x][y][x2][y2])
      {
         for (i=0;i<4;i++)
         {
            t1=x+l[i][0];
            t2=y+l[i][1];
            if (t1&&t2&&t1<=n&&t2<=m&&dis[t1][t2][x2][y2]==dis[x][y][x2][y2]-1&&tmp[t1][t2]!='X')
            {
               x=t1;
               y=t2;
               break;
            }
         }
         tmp[x][y]='*';
      }
      x=x2;
      y=y2;
      while (1)
      {
         for (i=0;i<4;i++)
         {
            t1=x+l[i][0];
            t2=y+l[i][1];
            if (t1&&t2&&t1<=n&&t2<=m&&out[t1][t2]==out[x][y]-1&&tmp[t1][t2]!='X')
            {
               x=t1;
               y=t2;
               break;
            }
         }
         tmp[x][y]='*';
         if (!out[x][y])
            break;
      }
   }
   for (i=1;i<=n;i++)
      puts(tmp[i]+1);
   return 0;
}
