#include <stdio.h>

long hash[92]={0},a[92]={0},l[14]={0};
long n,m,flag=0;

void dfs(long now)
{
   long i,j,k;
   if(now<=n)
   {
      for(i=1;i<=m;i++)
         if(!hash[i])
         {
            l[now]=a[i];
            for(j=1;j<now;j++)
            {
               for(k=1;k<=m;k++)
                  if(!hash[k]&&(l[j]^l[now])==a[k])
                  {
                     hash[k]=now;
                     break;
                  }
               if(k>m)
                  goto out;
            }
            dfs(now+1);
            if (flag)
               return;
            out:
            for(j=1;j<=m;j++)
               if(hash[j]==now)
                  hash[j]=0;
         }
   }
   else
   {
      for(i=1;i<=n;i++)
         printf("%ld%c",l[i],(i==n)?'\n':' ');
      flag=1;
   }
}

int main()
{
   long i;
   scanf("%ld",&m);
   for(i=1;i<=m;i++)
      scanf("%ld",&a[i]);
   for(n=1;n*(n-1)/2<m;n++);
   dfs(2);
   return 0;
}
