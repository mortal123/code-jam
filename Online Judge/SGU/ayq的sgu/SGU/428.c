#include <stdio.h>
#include <string.h>

char str[3][33]={'\0'},a[4]="AABC",b[4]="AABB",c[4]="DBCB",d[3]="RRR",e[3]="TTR",f[3]="EDT";
long tot=0;

void dfs(long l,long flag)
{
   long i;
   if (l)
   {
      tot++;
      for (i=1;i<=l;i++)
         printf("%c",str[0][i]);
      printf("+");
      for (i=1;i<=l;i++)
         printf("%c",str[1][i]);
      printf("=");
      for (i=1;i<=l;i++)
         printf("%c",str[2][i]);
      printf("\n");
      if (tot==1000)
         return;
   }
   if (l<=28&&!flag)
   {
      for (i=l+1;i<=l+4;i++)
      {
         str[0][i]=a[i-l-1];
         str[1][i]=b[i-l-1];
         str[2][i]=c[i-l-1];
      }
      dfs(l+4,0);
      if (tot<1000)
      {
         for (i=l+1;i<=l+4;i++)
         {
            str[0][i]=b[i-l-1];
            str[1][i]=a[i-l-1];
            str[2][i]=c[i-l-1];
         }
         dfs(l+4,0);
      }
   }
   if (l<=29&&flag)
   {
      for (i=l+1;i<=l+3;i++)
      {
         str[0][i]=d[i-l-1];
         str[1][i]=e[i-l-1];
         str[2][i]=f[i-l-1];
      }
      dfs(l+3,1);
      if (tot<1000)
      {
         for (i=l+1;i<=l+3;i++)
         {
            str[0][i]=e[i-l-1];
            str[1][i]=d[i-l-1];
            str[2][i]=f[i-l-1];
         }
         dfs(l+3,1);
      }
   }
}

int main()
{
   dfs(0,0);
   dfs(0,1);
   return 0;
}
