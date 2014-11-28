#include <stdio.h>
#define oo 1000
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   long map[4];
   long x,y,px,py,pw,s;
   char sign,same;
}p[31]={{0},{0,0,0,0,0,0},{'\0','\0'}};
char map[25][25]={'\0'},hash[25][25]={'\0'},ans[7][7]={'\0'};
long n,minx,miny,maxx,maxy,tot=0;

void dfs(long x,long y)
{
   hash[x][y]=1;
   minx=min(minx,x);
   maxx=max(maxx,x);
   miny=min(miny,y);
   maxy=max(maxy,y);
   if (!hash[x+1][y]&&map[x+1][y]==map[x][y])
      dfs(x+1,y);
   if (!hash[x][y+1]&&map[x][y+1]==map[x][y])
      dfs(x,y+1);
   if (!hash[x-1][y]&&map[x-1][y]==map[x][y])
      dfs(x-1,y);
   if (!hash[x][y-1]&&map[x][y-1]==map[x][y])
      dfs(x,y-1);
}

long work(long now,long map)
{
   long i,j,k;
   if (now==tot+1)
      return 1;
   for (i=0;i<=2&&(!i||p[now].map[2]!=p[now].map[0])&&(p[now].same==0||i<=p[now-1].pw);i+=2)
      for (j=(p[now].same&&i==p[now-1].pw)*(p[now-1].px-1);j<=n-p[now].x;j++)
         for (k=(p[now].same&&i==p[now-1].pw&&j==p[now-1].px-1)*p[now-1].py;k<=n-p[now].y;k++)
            if (!(map&((p[now].map[i])<<(j*n+k))))
            {
               p[now].px=j+1;
               p[now].py=k+1;
               p[now].pw=i;
               if (work(now+1,map|((p[now].map[i])<<(j*n+k))))
                  return 1;
            }
   for (i=1;i<=3&&(i==1||p[now].map[3]!=p[now].map[1])&&(p[now].same==0||i<=p[now-1].pw);i+=2)
      if (p[now].map[i]!=p[now].map[0]&&p[now].map[i]!=p[now].map[2])
         for (j=(p[now].same&&i==p[now-1].pw)*(p[now-1].px-1);j<=n-p[now].y;j++)
            for (k=(p[now].same&&i==p[now-1].pw&&j==p[now-1].px-1)*p[now-1].py;k<=n-p[now].x;k++)
               if (!(map&((p[now].map[i])<<(j*n+k))))
               {
                  p[now].px=j+1;
                  p[now].py=k+1;
                  p[now].pw=i;
                  if (work(now+1,map|((p[now].map[i])<<(j*n+k))))
                     return 1;
               }
   return 0;
}

int main()
{
   long i,j,k,l;
   struct case1 t;
   scanf("%ld\n",&n);
   for (i=1;i<=20;i++)
      gets(map[i]+1);
   for (i=1;i<=20;i++)
      for (j=1;j<=20;j++)
         if (!hash[i][j]&&map[i][j]!='.')
         {
            minx=miny=oo;
            maxx=maxy=-oo;
            dfs(i,j);
            tot++;
            p[tot].x=maxx-minx+1;
            p[tot].y=maxy-miny+1;
            p[tot].sign=map[i][j];
            for (k=0;k<p[tot].x;k++)
               for (l=0;l<p[tot].y;l++)
                  if (map[k+minx][l+miny]==map[i][j])
                  {
                     p[tot].s++;
                     p[tot].map[0]+=(1<<(k*n+l));
                     p[tot].map[1]+=(1<<(l*n+p[tot].x-k-1));
                     p[tot].map[2]+=(1<<((p[tot].x-k-1)*n+p[tot].y-l-1));
                     p[tot].map[3]+=(1<<((p[tot].y-l-1)*n+k));
                  }
         }
   for (i=1;i<tot;i++)
      for (j=i+1;j<=tot;j++)
         if (p[i].s<p[j].s)
         {
            t=p[i];
            p[i]=p[j];
            p[j]=t;
         }
   for (i=2;i<=tot;i++)
      for (j=0;j<4;j++)
      {
         for (k=0;k<4&&p[i-1].map[(k+j)&3]==p[i].map[k];k++);
         if (k==4)
         {
            p[i].same=1;
            p[i].x=p[i-1].x;
            p[i].y=p[i-1].y;
            for (k=0;k<4;k++)
               p[i].map[k]=p[i-1].map[k];
            break;
         }
      }
   work(1,0);
   for (i=1;i<=tot;i++)
      for (j=0;j<p[i].x;j++)
         for (k=0;k<p[i].y;k++)
            if ((p[i].map[0])&(1<<(j*n+k)))
            {
               if (p[i].pw==0)
                  ans[p[i].px+j][p[i].py+k]=p[i].sign;
               else if (p[i].pw==1)
                  ans[p[i].px+k][p[i].py+p[i].x-j-1]=p[i].sign;
               else if (p[i].pw==2)
                  ans[p[i].px+p[i].x-j-1][p[i].py+p[i].y-k-1]=p[i].sign;
               else
                  ans[p[i].px+p[i].y-k-1][p[i].py+j]=p[i].sign;
            }
   for (i=1;i<=n;i++)
      puts(ans[i]+1);
   return 0;
}
