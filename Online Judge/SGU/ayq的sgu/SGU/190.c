#include <stdio.h>

struct case1
{
   long x,y;
}pos[2][801]={{0,0}};
long head[801]={0},e[3201]={0},next[3201]={0},map[42][42]={0},f[801]={0},hash[801]={0},choose[41][41][2]={0};
long totm=0,flag=0;

void add(long a,long b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
}

long match(long now)
{
   long i;
   for (i=head[now];i;i=next[i])
      if (hash[e[i]]!=flag)
      {
         hash[e[i]]=flag;
         if (!f[e[i]]||match(f[e[i]]))
         {
            f[e[i]]=now;
            return 1;
         }
      }
   return 0;
}

int main()
{
   long i,j,n,k,a,b;
   scanf("%ld%ld",&n,&k);
   for (i=1;i<=k;i++)
   {
      scanf("%ld%ld",&a,&b);
      map[a][b]=-1;
   }
   a=b=0;
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
         if (!map[i][j])
            if ((i+j)&1)
            {
               map[i][j]=++a;
               pos[1][a].x=i;
               pos[1][a].y=j;
            }
            else
            {
               map[i][j]=++b;
               pos[0][b].x=i;
               pos[0][b].y=j;
            }
   if (a!=b)
   {
      printf("No\n");
      goto end;
   }
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
         if (((i+j)&1)&&map[i][j]>0)
         {
            if (map[i-1][j]>0)
               add(map[i][j],map[i-1][j]);
            if (map[i+1][j]>0)
               add(map[i][j],map[i+1][j]);
            if (map[i][j-1]>0)
               add(map[i][j],map[i][j-1]);
            if (map[i][j+1]>0)
               add(map[i][j],map[i][j+1]);
         }
   for (i=1;i<=a;i++)
   {
      flag++;
      if (!match(i))
      {
         printf("No\n");
         goto end;
      }
   }
   for (i=1;i<=a;i++)
      if (pos[1][f[i]].x==pos[0][i].x&&pos[1][f[i]].y==pos[0][i].y-1)
         choose[pos[0][i].x][pos[0][i].y-1][1]=1;
      else if (pos[1][f[i]].x==pos[0][i].x&&pos[1][f[i]].y==pos[0][i].y+1)
         choose[pos[0][i].x][pos[0][i].y][1]=1;
      else if (pos[1][f[i]].x==pos[0][i].x-1&&pos[1][f[i]].y==pos[0][i].y)
         choose[pos[0][i].x-1][pos[0][i].y][0]=1;
      else
         choose[pos[0][i].x][pos[0][i].y][0]=1;
   a=b=0;
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
         if (choose[i][j][0])
            a++;
         else if (choose[i][j][1])
            b++;
   printf("Yes\n%ld\n",a);
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
         if (choose[i][j][0])
            printf("%ld %ld\n",i,j);
   printf("%ld\n",b);
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
         if (choose[i][j][1])
            printf("%ld %ld\n",i,j);
   end:
   return 0;
}
