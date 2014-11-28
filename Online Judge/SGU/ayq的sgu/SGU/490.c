#include<stdio.h>

long map[21][21]={0};

int main()
{
   long i,j,q,n,m,k,flag=0;
   scanf("%ld",&q);
   while (q--)
   {
      scanf("%ld%ld%ld",&n,&m,&k);
      flag++;
      for (i=2;i<=n-1&&k;i++)
         for (j=2+(i&1);j<=m-1&&k;j+=2)
         {
            map[i][j]=flag;
            k--;
         }
      if (k)
         printf("Impossible\n");
      else
         for (i=1;i<=n;i++)
         {
            for (j=1;j<=m;j++)
               printf("%c",(map[i][j]==flag)?'#':'.');
            printf("\n");
         }
      printf("\n");
   }
   return 0;
}
