#include <stdio.h>

char map[205][205]={0};

int main()
{
   long i,j,n,m;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         map[i][j]='0';
   for (i=3;i<=500;i+=3)
      for (j=i;j>=1;j--)
         if (j>=1&&j<=m&&i-j+1>=1&&i-j+1<=n)
            map[i-j+1][j]='#';
   for (i=1;i<=n;i++)
      puts(map[i]+1);
   return 0;
}
