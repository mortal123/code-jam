#include <stdio.h>

struct case1
{
   long x,y,t;
}d[180001]={{0,0,0}},rec[90001]={{0,0,0}};
long l[8][2]={{1,1},{-1,-1},{1,-1},{-1,1},{1,0},{-1,0},{0,1},{0,-1}};
char map[305][305]={'\0'},hash[301][301][2]={'\0'};

int main()
{
   long i,j,n,x,y,k,tot=0,ans=0,st=1,en=1;
   struct case1 now;
   scanf("%ld%ld\n",&n,&k);
   for (i=1;i<=n;i++)
   {
      gets(map[i]+1);
      for (j=1;j<=n;j++)
         if (map[i][j]=='Q')
         {
            d[1]=(struct case1){i,j};
            hash[i][j][0]=1;
            map[i][j]='.';
         }
   }
   for (i=0;i<=n+1;i++)
      map[i][0]=map[0][i]=map[i][n+1]=map[n+1][i]='W';
   if (k)
   {
      for (i=0;i<8&&map[d[1].x+l[i][0]][d[1].y+l[i][1]]=='W';i++);
      if (i==8)
         goto end;
   }
   while (st<=en||tot)
   {
      if (d[st].t>d[st-1].t||st>en)
         while (tot)
            d[++en]=rec[tot--];
      now=d[st++];
      if (now.t<k)
      {
         for (i=0;i<8;i++)
         {
            x=now.x+l[i][0];
            y=now.y+l[i][1];
            while (map[x][y]!='W')
            {
               if (!hash[x][y][(now.t+1)&1])
               {
                  hash[x][y][(now.t+1)&1]=1;
                  d[++en]=(struct case1){x,y,now.t+1};
               }
               if (map[x][y]=='B')
                  break;
               x+=l[i][0];
               y+=l[i][1];
            }
         }
         if (map[now.x][now.y]=='B'&&now.t<k-1)
            for (i=0;i<4;i++)
               if (map[now.x+l[i<<1][0]][now.y+l[i<<1][1]]!='W'&&map[now.x+l[(i<<1)+1][0]][now.y+l[(i<<1)+1][1]]!='W')
               {
                  x=now.x+l[i<<1][0];
                  y=now.y+l[i<<1][1];
                  while (map[x][y]!='W')
                  {
                     if (!hash[x][y][(now.t)&1])
                     {
                        hash[x][y][(now.t)&1]=1;
                        rec[++tot]=(struct case1){x,y,now.t+2};
                     }
                     if (map[x][y]=='B')
                        break;
                     x+=l[i<<1][0];
                     y+=l[i<<1][1];
                  }
                  x=now.x+l[(i<<1)+1][0];
                  y=now.y+l[(i<<1)+1][1];
                  while (map[x][y]!='W')
                  {
                     if (!hash[x][y][(now.t)&1])
                     {
                        hash[x][y][(now.t)&1]=1;
                        rec[++tot]=(struct case1){x,y,now.t+2};
                     }
                     if (map[x][y]=='B')
                        break;
                     x+=l[(i<<1)+1][0];
                     y+=l[(i<<1)+1][1];
                  }
               }
      }
   }
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
         ans+=hash[i][j][k&1];
   end:
   printf("%ld\n",ans);
   return 0;
}
