#include <stdio.h>
#define oo 100000000

long f[70][70]={0},move[70][70]={0},plate[70][70]={0},sum[70]={0};
long tot=0;

long dfs(long i,long j)
{
   long t,k;
   if (i==1)
      return 1;
   if (j<=2)
      return oo;
   if (f[i][j])
      return f[i][j];
   f[i][j]=oo;
   for (k=1;k<i;k++)
   {
      t=2*dfs(k,j)+dfs(i-k,j-1);
      if (t<f[i][j])
      {
         f[i][j]=t;
         move[i][j]=k;
      }
   }
   return f[i][j];
}

void print(long n,long s,long t,long m)
{
   long i;
   if (n==1)
   {
      tot++;
      printf("move %ld from %ld to %ld",plate[s][sum[s]],s,t);
      if (sum[t])
         printf(" atop %ld",plate[t][sum[t]]);
      printf("\n");
      plate[t][++sum[t]]=plate[s][sum[s]--];
   }
   else
   {
      for (i=1;plate[i][sum[i]]<plate[s][sum[s]]||i==s||i==t;i++);
      print(move[n][m],s,i,m);
      print(n-move[n][m],s,t,m-1);
      print(move[n][m],i,t,m);
   }
}

int main()
{
   long i,n,m;
   scanf("%ld%ld",&n,&m);
   printf("%ld\n",dfs(n,m));
   for (i=1;i<=m;i++)
      plate[i][0]=n+1;
   for (i=n;i>=1;i--)
      plate[1][++sum[1]]=i;
   print(n,1,m,m);
   return 0;
}
