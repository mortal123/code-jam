#include <stdio.h>

struct case1
{
   long x,y,c,t;
}d[1000001]={{0,0,0,0}};
long ans[22205]={0},l[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
char hash[1002][1002]={'\0'};

int main()
{
   long i,n,m,k,t,st=1,en;
   struct case1 now;
   scanf("%ld%ld%ld%ld",&n,&m,&k,&t);
   for (i=0;i<=m+1;i++)
      hash[0][i]=hash[n+1][i]=1;
   for (i=1;i<=n;i++)
      hash[i][0]=hash[i][m+1]=1;
   en=k;
   for (i=1;i<=k;i++)
   {
      scanf("%ld%ld",&d[i].x,&d[i].y);
      d[i].c=i;
      hash[d[i].x][d[i].y]=1;
   }
   while (st<=en)
   {
      now=d[st++];
      ans[now.c]++;
      if (now.t<t)
         for (i=0;i<4;i++)
            if (!hash[now.x+l[i][0]][now.y+l[i][1]])
            {
               d[++en]=(struct case1){now.x+l[i][0],now.y+l[i][1],now.c,now.t+1};
               hash[now.x+l[i][0]][now.y+l[i][1]]=1;
            }
   }
   for (i=1;i<=k;i++)
      printf("%ld\n",ans[i]);
   return 0;
}
