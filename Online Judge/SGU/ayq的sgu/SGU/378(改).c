#include <stdio.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   int x,y;
}d[250001];
int l[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}},l2[5][2]={{0,0},{-1,0},{1,0},{0,1},{0,-1}},dis[501][501],f[5][8]={{2,2,2,2,0,0,0,0},{0,1,0,0,0,0,2,2},{1,0,0,0,2,2,0,0},{0,0,1,0,2,0,2,0},{0,0,0,1,0,2,0,2}};
char map[505][505];

int main()
{
   int i,n,m,x,y,x1,y1,x2,y2,st,en,v=0;
   struct case1 now;
   double ans=oo;
   scanf("%d%d\n",&n,&m);
   for (i=1;i<=n;i++)
      gets(map[i]+1);
   scanf("%d%d%d%d",&d[1].y,&d[1].x,&y2,&x2);
   if (d[1].x==x2&&d[1].y==y2)
   {
      puts("0.00");
      goto end;
   }
   st=en=dis[d[1].x][d[1].y]=1;
   while (st<=en)
   {
      now=d[st++];
      for (i=0;i<8;i++)
         if (f[map[now.x][now.y]-'0'][i])
         {
            x=now.x+l[i][0];
            y=now.y+l[i][1];
            if (!x||!y||x>n||y>m)
               ans=min(ans,(dis[now.x][now.y]+f[map[now.x][now.y]-'0'][i]/2.0-1)/2.0);
            else if (!dis[x][y]||dis[x][y]>dis[now.x][now.y]+f[map[now.x][now.y]-'0'][i])
            {
               dis[x][y]=dis[now.x][now.y]+f[map[now.x][now.y]-'0'][i];
               d[++en]=(struct case1){x,y};
            }
         }
   }
   for (i=1;i<=n*m;i++)
   {
      x1=x2+l2[map[x2][y2]-'0'][0];
      y1=y2+l2[map[x2][y2]-'0'][1];
      if (!x1||!y1||x1>n||y1>m)
         break;
      if (dis[x1][y1]&&dis[x1][y1]-1<=2*i)
         if (x1+l2[map[x1][y1]-'0'][0]==x2&&y1+l2[map[x1][y1]-'0'][1]==y2)
         {
            if (dis[x1][y1]+1>=2*i)
               ans=min(ans,i-(2*i-dis[x1][y1]+1)/(2.0+!!(map[x2][y2]-'0')));
         }
         else if (!l2[map[x1][y1]-'0'][0]&&!l2[map[x1][y1]-'0'][1])
         {
            if (map[x2][y2]-'0'&&dis[x1][y1]+2>=2*i)
               ans=min(ans,i-(2*i-dis[x1][y1]+1)/4.0);
         }
         else
            ans=min(ans,i);
      x2=x1;
      y2=y1;
   }
   if (ans<oo/2)
      printf("%.2lf\n",ans);
   else
      puts("SOS");
   end:
   return 0;
}
