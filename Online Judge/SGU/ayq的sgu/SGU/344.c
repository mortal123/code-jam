#include <stdio.h>

struct case1
{
   long x,y;
}d[1000005]={{0,0}};
long l[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
char map[1005][1005]={'\0'};

int main()
{
   long i,j,s,n,m,x,y,st=1,en=0;
   struct case1 now;
   scanf("%ld%ld\n",&n,&m);
   for (i=1;i<=n;i++)
      gets(map[i]+1);
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         if (map[i][j]=='X')
            d[++en]=(struct case1){i,j};
   while (st<=en)
   {
      now=d[st++];
      for (i=0;i<4;i++)
      {
         x=now.x+l[i][0];
         y=now.y+l[i][1];
         if (map[x][y]=='.')
         {
            s=0;
            for (j=0;j<4;j++)
               s+=(map[x+l[j][0]][y+l[j][1]]=='X');
            if (s>1)
            {
               d[++en]=(struct case1){x,y};
               map[x][y]='X';
            }
         }
      }
   }
   printf("%ld\n",en);
   return 0;
}
