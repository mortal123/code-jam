#include <stdio.h>

struct case1
{
   long a,b;
}p[100001]={{0,0}};
long f[10001]={0},head[10001]={0},du[10001]={0},du2[10001]={0},e[200002]={0},next[200002]={0},stack[10002]={0},ans[10002]={0},rec[10001][2]={0};
char hash[200002]={'\0'};
long totm=1,top=0;

void add(long a,long b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
}

long getf(long now)
{
   if (f[now]==now)
      return now;
   return f[now]=getf(f[now]);
}

void dfs(long now)
{
   long i;
   for (i=head[now];i;i=next[i])
   {
      head[now]=next[i];
      if (!hash[i])
      {
         hash[i^1]=hash[i]=1;
         dfs(e[i]);
      }
   }
   stack[++top]=now;
}

int main()
{
   long i,n,m,fa,fb,tot=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
      f[i]=i;
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld",&p[i].a,&p[i].b);
      du[p[i].a]++;
      du[p[i].b]++;
   }
   for (i=1;i<=m;i++)
      if (du[p[i].a]!=2&&du[p[i].b]!=2)
      {
         fa=getf(p[i].a);
         fb=getf(p[i].b);
         if (fa!=fb)
            f[fa]=fb;
      }
   for (i=1;i<=m;i++)
   {
      fa=getf(p[i].a);
      fb=getf(p[i].b);
      if (fa!=fb)
      {
         add(fa,fb);
         add(fb,fa);
         du2[fa]++;
         du2[fb]++;
      }
   }
   for (i=1;i<=n&&(du2[i]&1)==0;i++);
   if (i<=n)
      printf("-1\n");
   else
   {
      dfs(getf(1));
      stack[0]=stack[--top];
      for (i=1;i<=m;i++)
      {
         if (du[p[i].a]==2)
         {
            if (rec[p[i].a][0])
               rec[p[i].a][1]=p[i].b;
            else
               rec[p[i].a][0]=p[i].b;
         }
         if (du[p[i].b]==2)
         {
            if (rec[p[i].b][0])
               rec[p[i].b][1]=p[i].a;
            else
               rec[p[i].b][0]=p[i].a;
         }
      }
      for (i=top;i>=1;i--)
         if (du[stack[i]]==2)
         {
            if (du[stack[i+1]]!=2)
               ans[++tot]=((getf(rec[stack[i]][0])==stack[i+1])?rec[stack[i]][0]:rec[stack[i]][1]);
            ans[++tot]=stack[i];
            if (du[stack[i-1]]!=2)
               ans[++tot]=((getf(rec[stack[i]][0])==stack[i-1])?rec[stack[i]][0]:rec[stack[i]][1]);
         }
      for (i=1;i<=tot;i++)
         printf("%ld%c",ans[i],(i==tot)?'\n':' ');
   }
   return 0;
}
