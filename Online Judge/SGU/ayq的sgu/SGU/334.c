#include <stdio.h>

struct case1
{
   long x,y;
}p[11]={0,0};
long f[11]={0},num[11][11]={0},pos[10]={0},rec[10]={0},ans_pos[10]={0};
char map[11][11]={0},hash[10]={0},ans_rec[10]={0};
long ans=10;

long getf(long x)
{
   if (f[x]==x)
      return x;
   return f[x]=getf(f[x]);
}

void dfs(long x)
{
   long i,s=0;
   if (x==10)
   {
      for (i=1;i<=9;i++)
         f[i]=i;
      for (i=1;i<=9;i++)
      {
         if (i%3&&num[p[pos[i]].x][p[pos[i]].y+1]==pos[i+1])
            f[getf(i+1)]=getf(i);
         if (i<=6&&num[p[pos[i]].x+1][p[pos[i]].y]==pos[i+3])
            f[getf(i+3)]=getf(i);
      }
      for (i=1;i<=9;i++)
         if (f[i]==i)
            rec[i]=++s;
      if (s<ans)
      {
         ans=s;
         for (i=1;i<=9;i++)
         {
            ans_pos[pos[i]]=i;
            ans_rec[i]=rec[getf(i)]+'A'-1;
         }
      }
   }
   else
      for (i=1;i<=9;i++)
         if (!hash[i])
         {
            pos[x]=i;
            hash[i]=1;
            dfs(x+1);
            hash[i]=0;
         }
}

int main()
{
   long i,j,n,m,s=0;
   scanf("%ld%ld\n",&n,&m);
   for (i=1;i<=n;i++)
   {
      gets(map[i]+1);
      for (j=1;j<=m;j++)
         if (map[i][j]!='.')
         {
            p[++s]=(struct case1){i,j};
            num[i][j]=s;
         }
   }
   dfs(1);
   printf("%ld\n",ans);
   for (i=1;i<=n;i++)
   {
      for (j=1;j<=m;j++)
         if (!num[i][j])
            putchar('.');
         else
            putchar(ans_rec[ans_pos[num[i][j]]]);
      puts("");
   }
   for (i=1;i<=3;i++)
   {
      for (j=1;j<=3;j++)
         putchar(ans_rec[(i-1)*3+j]);
      puts("");
   }
   return 0;
}
