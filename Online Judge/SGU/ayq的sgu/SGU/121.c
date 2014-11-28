#include<stdio.h>
#include<string.h>
#include<stdlib.h>

long link[101][101]={0},du[101]={0},q[101][101]={0};
char hash[101]={'\0'},paint[101][101]={'\0'},in[101]={'\0'};
long n,node,root;

long dfs(long now)
{
   long i,flag=(du[now]==2);
   node++;
   hash[now]=1;
   for (i=1;i<=n;i++)
      if (link[now][i]&&!hash[i])
         if (!dfs(i))
            flag=0;
   return flag;
}

void work(long now,long c,long last)
{
   long i,flag=0;
   in[now]=hash[now]=1;
   if (now==root)
   {
      for (i=1;i<=n;i++)
         if (link[root][i]&&!hash[i])
         {
            if (!flag)
            {
               paint[i][root]=paint[root][i]=1;
               work(i,0,now);
            }
            else
               work(i,1,now);
            flag=1;
         }
   }
   else
   {
      for (i=1;i<=n;i++)
         if (link[now][i])
         { 
            if (now==2)
               now=2;
            if (i!=last&&(!hash[i]||in[i]))
            {
               paint[now][i]=paint[i][now]=c;
               flag++;
            }
            if (!hash[i])
            {
               work(i,!c,now);
               flag=2;
            }
         }
      if (flag>=2&&c&&link[now][root]&&last!=root)
         paint[now][root]=paint[root][now]=0;
   }
   in[now]=0;
}

int main()
{
   long i,j,t;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      while (1)
      {
         scanf("%ld",&t);
         if (!t)
            break;
         q[i][++q[i][0]]=t;
         link[i][t]=1;
         du[t]++;
      }
   for (i=1;i<=n;i++)
      if (!hash[i])
      {
         node=0;
         if (dfs(i))
            if (node&1)
               break;
      }
   if (i<=n)
      printf("No solution\n");  
   else
   {
      memset(hash,0,sizeof(hash));
      for (i=1;i<=n;i++)
         if (!hash[i])
         {
            root=i;
            work(i,0,0);
         }
      for (i=1;i<=n;i++)
      {
         for (j=1;j<=q[i][0];j++)
            printf("%ld ",paint[i][q[i][j]]+1);
         printf("0\n");
      }
   }
   return 0;
}
