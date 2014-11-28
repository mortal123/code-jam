#include <stdio.h>
#include <stdlib.h>

int s[101],c[101],head[101],hash[101],dfn[101],next[2001],e[2001];
int totm,tot,o,flag=0;

void add(int a,int b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
}

void dfs(int now)
{
   int i,s=0;
   dfn[now]=++o;
   hash[now]=flag;
   for (i=head[now];i;i=next[i])
      if (hash[e[i]]!=flag)
      {
         dfs(e[i]);
         if (!c[e[i]])
            s=1;
      }
   if (s)
   {
      c[now]=++tot;
      for (i=head[now];i;i=next[i])
         if (dfn[e[i]]>dfn[now]&&!c[e[i]])
            c[e[i]]=tot;
   }
}

int main()
{
   int i,j,q,n,m,a,b;
   scanf("%d",&q);
   while (q--)
   {
      totm=0;
      memset(head,0,sizeof(head));
      scanf("%d%d",&n,&m);
      for (i=1;i<=m;i++)
      {
         scanf("%d%d",&a,&b);
         add(a,b);
         add(b,a);
      }
      for (i=1;i<=n;i++)
      {
         tot=o=0;
         flag++;
         memset(c,0,sizeof(c));
         dfs(i);
         if (c[i])
            break;
         memset(s,0,sizeof(s));
         for (j=head[i];j;j=next[j])
            s[c[e[j]]]++;
         for (j=1;j<=tot;j++)
            if (s[j]==1)
            {
               c[i]=j;
               break;
            }
         if (c[i])
            break;
      }
      for (i=1;i<=n;i++)
         printf("%d%c",c[i],(i==n)?'\n':' ');
   }
   return 0;
}
