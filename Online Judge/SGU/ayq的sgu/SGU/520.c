#include<math.h>
#include<time.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define oo 1000000000
#define pi 3.14159265359
#define zero(a) (abb(a)<=1e-7)
#define lowbit(a) ((a)&(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abb(a) ((a)>0?(a):(-(a)))
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y2))
#define dj(x1,y1,x2,y2) ((x1)*(y1)+(y1)*(y2))
#define dis(x1,y1,x2,y2) sqrt(((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1)))

long head[1001]={0},e[2001]={0},next[2001]={0},dis[1001]={0},d[1001]={0};
char f[1001]={0};
long totm=0;

void add(long a,long b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
}

int main()
{
   long i,j,k,n,m,a,b,now,tot,st=1,en=1;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld",&a,&b);
      add(a,b);
      add(b,a);
   }
   dis[1]=d[1]=1;
   while (st<=en)
   {
      now=d[st++];
      for (i=head[now];i;i=next[i])
         if (!dis[e[i]])
         {
            dis[e[i]]=dis[now]+1;
            d[++en]=e[i];
         }
   }
   tot=dis[d[en]];
   for (i=tot;i>=1;i--)
      for (j=1;j<=n;j++)
         if (dis[j]==i)
            if (i&1)
            {
               for (k=head[j];k&&(f[e[k]]||dis[e[k]]!=i+1);k=next[k]);
               if (!k)
                  f[j]=1;
            }
            else
            {
               for (k=head[j];k&&(!f[e[k]]||dis[e[k]]!=i+1);k=next[k]);
               if (k)
                  f[j]=1;
            }
   if (!f[1])
      printf("Vladimir\n");
   else
      printf("Nikolay\n");
   return 0;
}
