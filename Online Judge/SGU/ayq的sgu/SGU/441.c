#include <stdio.h>

long one[10][10]={0},mat[10][10]={0};
long long tmp[10][10]={0};
long k;

void mi(long now)
{
   long i,j,x;
   if (!now)
      for (i=0;i<k;i++)
         mat[i][i]=1;
   else
   {
      mi(now>>1);
      memset(tmp,0,sizeof(tmp));
      for (i=0;i<k;i++)
         for (j=0;j<k;j++)
            for (x=0;x<k;x++)
               tmp[i][j]+=mat[i][x]*mat[x][j];
      for (i=0;i<k;i++)
         for (j=0;j<k;j++)
            mat[i][j]=tmp[i][j]%2007;
      if (now&1)
      {
         memset(tmp,0,sizeof(tmp));
         for (i=0;i<k;i++)
            for (j=0;j<k;j++)
               for (x=0;x<k;x++)
                  tmp[i][j]+=mat[i][x]*one[x][j];
         for (i=0;i<k;i++)
            for (j=0;j<k;j++)
               mat[i][j]=tmp[i][j]%2007;
      }
   }
}

int main()
{
   long i,j,n;
   scanf("%ld%ld",&n,&k);
   for (i=0;i<k-1;i++)
   {
      one[i][i]=i+1;
      one[i][i+1]=1;
   }
   one[k-1][k-1]=k;
   mi(n-1);
   printf("%ld\n",mat[0][k-1]);
   return 0;
}
