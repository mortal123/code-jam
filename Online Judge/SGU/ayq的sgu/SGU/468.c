#include <stdio.h>
#include <time.h>

long p[8]={0},l[8][2]={{1,2},{2,1},{-1,2},{-2,1},{1,-2},{2,-1},{-1,-2},{-2,-1}},mat[251][251]={0},du[251][251]={0};

int main()
{
   long i,j,k,a,n,x,y,px,py,rx,ry;
   scanf("%ld",&n);
   for (i=1;i<=50;i++)
   {
      for (j=0;j<=7;j++)
         p[j]=j;
      for (j=0;j<=7;j++)
      {
         k=(rand()&7);
         if (j!=k)
         {
            p[j]^=p[k];
            p[k]^=p[j];
            p[j]^=p[k];
         }
      }
      for (j=1;j<=n;j++)
         for (k=1;k<=n;k++)
            mat[j][k]=du[j][k]=0;
      for (j=1;j<=n;j++)
         for (k=1;k<=n;k++)
            for (a=0;a<=7;a++)
            {
               x=j+l[a][0];
               y=k+l[a][1];
               if (x>0&&x<=n&&y>0&&y<=n)
                  du[x][y]++;
            }
      x=rand()%n+1;
      y=rand()%n+1;
      for (j=1;j<=n*n;j++)
      {
         mat[x][y]=j;
         for (k=0;k<=7;k++)
         {
            rx=x+l[k][0];
            ry=y+l[k][1];
            if (rx>0&&rx<=n&&ry>0&&ry<=n)
               du[rx][ry]--;
         }
         rx=0;
         for (k=0;k<=7;k++)
         {
            px=x+l[p[k]][0];
            py=y+l[p[k]][1];
            if (px>0&&px<=n&&py>0&&py<=n&&!mat[px][py]&&(!rx||du[px][py]<du[rx][ry]))
            {
               rx=px;
               ry=py;
            }
         }
         if (!rx)
            break;
         x=rx;
         y=ry;
      }
      if (j==n*n)
         break;
   }
   if (i==51)
      puts("No solution.");
   else
   {
      puts("There is solution:");
      for (i=1;i<=n;i++)
         for (j=1;j<=n;j++)
            printf("%ld%c",mat[i][j],(j==n)?'\n':' ');
   }
   return 0;
}
