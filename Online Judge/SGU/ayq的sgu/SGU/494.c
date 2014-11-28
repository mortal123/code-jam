#include <stdio.h>
#include <stdlib.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

int head[10002],du[10002],next[10002],e[10002],a[10002],stack[10002],f[1002][10002],g[10002],h[10002][2];
int r,n,totm,top=0;

void add(int a,int b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   du[b]++;
}

void work(int w)
{
   int i,j=0,s=0;
   for (i=1;i<=n;i++)
   {
      j=max(j,i-1);
      while (j<n&&s+a[j+1]+(j>=i)<=w)
      {
         s+=a[j+1]+(j>=i);
         j++;
      }
      f[w][i]=j+1;
      if (j==i)
         s=0;
      else if (j>i)
         s-=a[i]+1;
   }
   f[w][n+1]=n+1;
}

void dfs(int now,int last)
{
   int i;
   stack[++top]=now;
   g[now]=max(g[now],stack[max(top-r,1)]);
   for (i=head[now];i;i=next[i])
      if (e[i]!=last)
         dfs(e[i],now);
   top--;
}

int main()
{
   int i,j,q,w,c;
   scanf("%d",&q);
   while (q--)
   {
      scanf("%d%d%d%d",&n,&w,&r,&c);
      for (i=1;i<=n;i++)
         scanf("%d",&a[i]);
      for (i=0;i<=w-c;i++)
         work(i);
      work(w);
      memset(g,0,(n+2)*sizeof(int));
      for (i=0;i<w-c;i++)
      {
         totm=0;
         memset(head,0,(n+2)*sizeof(int));
         memset(du,0,(n+2)*sizeof(int));
         for (j=1;j<=n;j++)
            if (f[w-c-i][f[i][j]]!=j)
               add(f[w-c-i][f[i][j]],j);
         for (j=1;j<=n+1;j++)
            if (!du[j])
               dfs(j,0);
      }
      for (i=1;i<=n+1;i++)
         h[i][0]=h[i][1]=oo;
      h[1][0]=0;
      for (i=1;i<=n;i++)
      {
         h[f[w][i]][0]=min(h[f[w][i]][0],h[i][0]+1);
         h[f[w][i]][1]=min(h[f[w][i]][1],h[i][1]+1);
         h[g[i]][1]=min(h[g[i]][1],h[i][0]+r);
      }
      printf("%d\n",min(h[n+1][0]+r,h[n+1][1]));
   }
   return 0;
}
