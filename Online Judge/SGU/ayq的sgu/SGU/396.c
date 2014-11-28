#include <stdio.h>
#define oo 1000000000

struct case1
{
   long a,b,c,d;
}last[1001][4][4][2][2]={0};
long f[1001][4][4][2][2]={0};
char pos[130]={0},str[1005]={0},rec[1001][2]={0},apos[5]="LRUD";

void renew(long x,long a1,long b1,long c1,long d1,long a2,long b2,long c2,long d2,long cost)
{
   if (f[x-1][a2][b2][c2][d2]+cost<f[x][a1][b1][c1][d1])
   {
      f[x][a1][b1][c1][d1]=f[x-1][a2][b2][c2][d2]+cost;
      last[x][a1][b1][c1][d1]=(struct case1){a2,b2,c2,d2};
   }
}

int main()
{
   long i,j,k,l,a,b,c,d,n,x,min=oo;
   pos['R']=1;
   pos['U']=2;
   pos['D']=3;
   scanf("%ld%s",&n,str+1);
   for (i=0;i<=3;i++)
      for (j=0;j<=3;j++)
         f[0][i][j][0][0]=f[0][i][j][0][1]=f[0][i][j][1][0]=f[0][i][j][1][1]=oo;
   f[0][0][1][0][0]=0;
   for (i=1;i<=n;i++)
      for (j=0;j<=3;j++)
         for (k=0;k<=3;k++)
         {
            f[i][j][k][0][0]=f[i][j][k][0][1]=f[i][j][k][1][0]=f[i][j][k][1][1]=oo;
            if ((j!=1||k)&&j!=k)
               for (a=0;a<=3;a++)
                  for (b=0;b<=3;b++)
                     for (c=0;c<=1;c++)
                        for (d=0;d<=1;d++)
                           if (str[i]=='N')
                           {
                              if (a==j&&b==k)
                                 renew(i,j,k,0,0,a,b,c,d,0);
                              else if (b==k)
                                 renew(i,j,k,0,0,a,b,c,d,6*c+3);
                              else if (a==j)
                                 renew(i,j,k,0,0,a,b,c,d,6*d+3);
                              else
                                 renew(i,j,k,0,0,a,b,c,d,10);
                           }
                           else if (a==j&&b==k&&pos[str[i]]==j)
                              renew(i,j,k,1,0,a,b,c,d,1);
                           else if (a==j&&b==k&&pos[str[i]]==k)
                              renew(i,j,k,0,1,a,b,c,d,1);
                           else if (b==k&&pos[str[i]]==j)
                              renew(i,j,k,1,0,a,b,c,d,6*c+3);
                           else if (a==j&&pos[str[i]]==k)
                              renew(i,j,k,0,1,a,b,c,d,6*d+3);
                           else if (pos[str[i]]==j)
                              renew(i,j,k,1,0,a,b,c,d,10);
                           else if (pos[str[i]]==k)
                              renew(i,j,k,0,1,a,b,c,d,10);
         }
   for (i=0;i<=3;i++)
      for (j=0;j<=3;j++)
         for (k=0;k<=1;k++)
            for (l=0;l<=1;l++)
               if (f[n][i][j][k][l]<min)
               {
                  min=f[n][i][j][k][l];
                  a=i;
                  b=j;
                  c=k;
                  d=l;
               }
   printf("%ld\n",min);
   for (x=n;x>=1;x--)
   {
      rec[x][0]=apos[i=a];
      rec[x][1]=apos[j=b];
      k=c;
      l=d;
      a=last[x][i][j][k][l].a;
      b=last[x][i][j][k][l].b;
      c=last[x][i][j][k][l].c;
      d=last[x][i][j][k][l].d;
   }
   for (i=1;i<=n;i++)
      printf("%c%c\n",rec[i][0],rec[i][1]);
   return 0;
}
