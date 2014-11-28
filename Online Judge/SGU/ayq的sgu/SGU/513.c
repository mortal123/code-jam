#include <stdio.h>

int hash[101],c[101],pos[101],link[101][101],rec[2][101];
int n,x=0;

int dfs(int now,int v)
{
   int i;
   if (hash[pos[now]]==x)
      return 0;
   hash[pos[now]]=x;
   rec[v-1][++rec[v-1][0]]=now;
   c[now]=v;
   for (i=1;i<=n;i++)
      if (pos[i]!=pos[now]&&link[now][i])
         if (!c[i])
         {
            if (!dfs(i,3-v))
               return 0;
         }
         else if (c[i]==v)
            return 0;
   return 1;
}

int main()
{
   int i,j,k,a,b,m,flag=0,o=0;
   scanf("%d%d",&n,&m);
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         link[i][j]=link[j][i]=1;
   for (i=1;i<=m;i++)
   {
      scanf("%d%d",&a,&b);
      link[b][a]=link[a][b]=0;
   }
   for (i=1;i<n-1;i++)
      for (j=i+1;j<n;j++)
         for (k=j+1;k<=n;k++)
            if (link[i][j]&&link[j][k]&&link[k][i])
            {
               if (pos[i]||pos[j]||pos[k])
                  goto end;
               pos[i]=pos[j]=pos[k]=++o;
            }
   for (i=1;i<=n;i++)
      if (!pos[i])
         goto end;
   for (i=1;i<=n;i++)
      if (!c[i])
      {
         x++;
         rec[0][0]=rec[1][0]=0;
         if (!dfs(i,1))
            goto end;
         for (j=1;j<=rec[0][0];j++)
            for (k=1;k<=rec[1][0];k++)
               if (!link[rec[0][j]][rec[1][k]])
                  goto end;
      }
   flag=1;
   end:
   puts(flag?"YES":"NO");
   return 0;
}
