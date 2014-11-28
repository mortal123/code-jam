#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define abb(a) (((a)>0)?(a):(-(a)))
#define pi 3.1415926535897932384626433832795
#define dis(i,j) sqrt((p[i].x-p[j].x)*(p[i].x-p[j].x)+(p[i].y-p[j].y)*(p[i].y-p[j].y))

struct case1
{
   double x,y;
}p[8],rec[73];
char e[8][8],hash[8];
int d[8],v[8];
int n,o=0;

int check(int now)
{
   int i;
   double x;
   for (i=1;i<=n;i++)
      if (i!=now&&hash[i])
      {
         x=dis(i,now);
         if (x<=1e-2||e[now][i]&&abb(x-1)>=1e-7||!e[now][i]&&abb(x-1)<=1e-2)
            return 0;
      }
   return 1;
}

int work(int now,int s)
{
   int tmp[8];
   int i,t=0,t2=0;
   double x,y;
   if (now>n)
      return 1;
   for (i=1;i<=n;i++)
      v[i]=rand();
   for (i=1;i<=n;i++)
      if (!hash[i]&&(!t||d[i]>d[t]||d[i]==d[t]&&v[i]<v[t]))
         t=i;
   hash[t]=1;
   for (i=1;i<=n;i++)
      if (!hash[i]&&e[t][i])
         d[i]++;
   if (!d[t])
   {
      p[t].x=s*10;
      if (work(now+1,s+1))
         return 1;
   }
   else if (d[t]==1)
   {
      for (t2=1;!hash[t2]||!e[t2][t];t2++);
      for (i=1;i<=o;i++)
      {
         p[t]=(struct case1){p[t2].x+rec[i].x,p[t2].y+rec[i].y};
         if (check(t)&&work(now+1,s))
            return 1;
      }
   }
   else
   {
      for (i=1;i<=n;i++)
         if (hash[i]&e[i][t])
            tmp[++t2]=i;
      if ((x=dis(tmp[1],tmp[2]))<=2-1e-10)
      {
         y=sqrt(1-x*x/4);
         p[t].x=(p[tmp[1]].x+p[tmp[2]].x)/2+(p[tmp[2]].y-p[tmp[1]].y)/x*y;
         p[t].y=(p[tmp[1]].y+p[tmp[2]].y)/2+(p[tmp[1]].x-p[tmp[2]].x)/x*y;
         if (check(t)&&work(now+1,s))
            return 1;
         p[t].x=(p[tmp[1]].x+p[tmp[2]].x)/2+(p[tmp[1]].y-p[tmp[2]].y)/x*y;
         p[t].y=(p[tmp[1]].y+p[tmp[2]].y)/2+(p[tmp[2]].x-p[tmp[1]].x)/x*y;
         if (check(t)&&work(now+1,s))
            return 1;
      }
   }
   for (i=1;i<=n;i++)
      if (!hash[i]&&e[t][i])
         d[i]--;
   return hash[t]=0;
}

int main()
{
   int i,m,a,b;
   for (i=0;i<60;i++)
      rec[++o]=(struct case1){cos(pi/60*i),sin(pi/60*i)};
   for (i=15;i<360;i+=30)
      rec[++o]=(struct case1){cos(pi/360*i),sin(pi/360*i)};
   scanf("%d%d",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%d%d",&a,&b);
      e[a+1][b+1]=e[b+1][a+1]=1;
   }
   if (!work(1,0))
      puts("No");
   else
   {
      puts("Yes");
      for (i=1;i<=n;i++)
         printf("%.15lf %.15lf\n",p[i].x,p[i].y);
   }
   return 0;
}
