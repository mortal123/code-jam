#include <stdio.h>

long d[40001]={0},mat[201][201]={0},ans[40001][2]={0},l[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
char hash[401][401]={0};

int main()
{
   long i,j,n,m,x,y,px,py,st=1,en=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
      {
         scanf("%ld",&mat[i][j]);
         if (mat[i][j]==1)
            d[++en]=(i-1)*m+j-1;
      }
   while (st<=en)
   {
      x=d[st]/m+1;
      y=d[st]%m+1;
      hash[x][y]=1;
      ans[st][0]=x;
      ans[st++][1]=y;
      for (i=0;i<4;i++)
      {
         px=x+l[i][0];
         py=y+l[i][1];
         if (px&&px<=n&&py&&py<=m)
         {
            mat[px][py]--;
            if (!mat[px][py]&&!hash[px][py])
               goto out;
            else if (mat[px][py]==1)
               d[++en]=(px-1)*m+py-1;
         }
      }
   }
   out:
   if (st==n*m+1)
      for (i=n*m;i>=1;i--)
         printf("%ld %ld\n",ans[i][0],ans[i][1]);
   else
      printf("No solution\n");
   return 0;
}
