#include <stdio.h>
#define oo 100000000
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   long x,y;
}p[250001]={0,0};
struct case2
{
   long minx,maxx,miny,maxy;
}q[250001]={0,0,0,0};
long v[505][505]={0},v2[505][505]={0},l[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
char map[505][505]={0},hash[505][505]={0},ans[505][505]={0};
long n,m,num,flag=0;

void paint1(long x,long y,char c)
{
   long i,px,py;
   hash[x][y]=1;
   p[++num]=(struct case1){x,y};
   for (i=0;i<4;i++)
   {
      px=x+l[i][0];
      py=y+l[i][1];
      if (px&&py&&px<=n&&py<=m&&map[px][py]==c&&!hash[px][py])
         paint1(px,py,c);
   }
}

void paint2(long x,long y,struct case2 t)
{
   long i,px,py;
   v2[x][y]=flag;
   for (i=0;i<4;i++)
   {
      px=x+l[i][0];
      py=y+l[i][1];
      if (px>=t.minx&&py>=t.miny&&px<=t.maxx&&py<=t.maxy&&v2[px][py]!=flag)
         paint2(px,py,t);
   }
}

int main()
{
   long i,j,k,l,x,s=0,sum=0;
   scanf("%ld%ld%ld\n",&n,&m,&x);
   for (i=1;i<=n;i++)
      gets(map[i]+1);
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         if (!hash[i][j])
         {
            num=0;
            paint1(i,j,map[i][j]);
            if (num>=x)
            {
               q[++s]=(struct case2){oo,-oo,oo,-oo};
               for (k=1;k<=num;k++)
               {
                  v[p[k].x][p[k].y]=s;
                  q[s].minx=min(q[s].minx,p[k].x);
                  q[s].maxx=max(q[s].maxx,p[k].x);
                  q[s].miny=min(q[s].miny,p[k].y);
                  q[s].maxy=max(q[s].maxy,p[k].y);
               }
            }
         }
   memset(hash,0,sizeof(hash));
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         if (v[i][j]&&!hash[i][j])
         {
            num=0;
            paint1(i,j,map[i][j]);
            flag++;
            for (k=1;k<=num;k++)
               v2[p[k].x][p[k].y]=flag;
            for (k=q[v[i][j]].minx;k<=q[v[i][j]].maxx;k++)
            {
               if (v2[k][q[v[i][j]].miny]!=flag)
                  paint2(k,q[v[i][j]].miny,q[v[i][j]]);
               if (v2[k][q[v[i][j]].maxy]!=flag)
                  paint2(k,q[v[i][j]].maxy,q[v[i][j]]);
            }
            for (k=q[v[i][j]].miny+1;k<q[v[i][j]].maxy;k++)
            {
               if (v2[q[v[i][j]].minx][k]!=flag)
                  paint2(q[v[i][j]].minx,k,q[v[i][j]]);
               if (v2[q[v[i][j]].maxx][k]!=flag)
                  paint2(q[v[i][j]].maxx,k,q[v[i][j]]);
            }
            for (k=q[v[i][j]].minx;k<=q[v[i][j]].maxx;k++)
               for (l=q[v[i][j]].miny;l<=q[v[i][j]].maxy;l++)
                  if (v2[k][l]!=flag)
                     ans[k][l]=hash[k][l]=1;
         }
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         sum+=!!(ans[i][j]|v[i][j]);
   printf("%ld\n",sum);
   return 0;
}
