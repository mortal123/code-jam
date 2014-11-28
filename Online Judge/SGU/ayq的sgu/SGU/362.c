#include <stdio.h>

long l[4][2]={{1,0},{0,-1},{-1,0},{0,1}};
char sign[5]="DLUR",hash[15][15]={'\0'};

int main()
{
   long i,n,m,x,y;
   scanf("%ld%ld%ld%ld",&n,&m,&x,&y);
   for (i=0;i<=m+1;i++)
      hash[0][i]=hash[n+1][i]=1;
   for (i=1;i<=n;i++)
      hash[i][0]=hash[i][m+1]=1;
   while (1)
   {
      hash[x][y]=1;
      for (i=0;i<4;i++)
         if (!hash[x+l[i][0]][y+l[i][1]])
         {
            x+=l[i][0];
            y+=l[i][1];
            putchar(sign[i]);
            break;
         }
      if (i==4)
         break;
   }
   return 0;
}
