#include<stdio.h>

char map[102][102]={'\0'};

int main()
{
   long i,j,n,m,px,py;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
      {
         re:
         map[i][j]=getchar();
         if (map[i][j]=='P')
         {
            px=j;
            py=i;
         }
         else if (map[i][j]!='.'&&map[i][j]!='/'&&map[i][j]!='\\')
            goto re;
      }
   while (py<n)
   {
      py++;
      if (map[py][px]=='/')
      {
         px--;
         if (map[py][px]=='\\'||px==0)
         {
            printf("-1\n");
            goto end;
         }
      }
      else if (map[py][px]=='\\')
      {
         px++;
         if (map[py][px]=='/'||px==m+1)
         {
            printf("-1\n");
            goto end;
         }
      }
   }
   printf("%ld\n",px);
   end:
   return 0;
}
