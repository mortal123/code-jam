#include <stdio.h>

struct case1
{
   int v,x,y;
}p[1000001];
int du[2001],e[2001],next[2001],head[2001],tmp[2001],a[1001][1001],s[1000001],rec[2001],ans[1000001],hash[1000001];
int totm=0;

void add(int a,int b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   du[b]++;
}

void qs(int x,int y)
{
   int i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&p[j].v>t.v)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i].v<t.v)
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

int main()
{
   int i,j,n,m,o=0,tot=0,x=0;
   scanf("%d%d",&n,&m);
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
      {
         scanf("%d",&p[(i-1)*m+j].v);
         p[(i-1)*m+j].x=i;
         p[(i-1)*m+j].y=j;
      }
   qs(1,n*m);
   for (i=1;i<=n*m;i++)
   {
      if (i==1||p[i].v>p[i-1].v)
         s[++o]=p[i].v;
      a[p[i].x][p[i].y]=o;
   }
   for (i=2;i<=n;i++)
   {
      for (j=1;a[i][j]==a[1][j];j++);
      if (!hash[a[1][j]])
      {
         hash[a[1][j]]=++tot;
         rec[tot]=a[1][j];
      }
      if (!hash[a[i][j]])
      {
         hash[a[i][j]]=++tot;
         rec[tot]=a[i][j];
      }
      add(hash[a[1][j]],hash[a[i][j]]);
      add(hash[a[i][j]],hash[a[1][j]]);
   }
   x=0;
   for (i=1;i<=tot;i++)
      if (du[i]>49)
         ans[rec[i]]=++x;
   for (i=1;i<=tot;i++)
      if (!ans[rec[i]])
      {
         for (j=head[i];j;j=next[j])
            tmp[ans[rec[e[j]]]]=i;
         for (j=1;tmp[j]==i;j++);
         ans[rec[i]]=j;
      }
   puts("Yes");
   for (i=1;i<=o;i++)
      printf("%d -> %d\n",s[i],ans[i]-!!hash[i]);
   return 0;
}
