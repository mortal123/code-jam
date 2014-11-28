#include <stdio.h>
#define abs(a) ((a)>0?(a):(-(a)))

struct case1
{
   long x,y;
}p[400001]={{0,0}};
long head[1000008]={0},e[400001]={0},next[400001]={0},f[400001]={0};
long totm=0,tot=0;

long getf(long now)
{
   if (f[now]==now)
      return now;
   return f[now]=getf(f[now]);
}

long find(long x,long y)
{
   long i,key=(abs(x)*19940405LL+abs(y)*19940910LL)%1000007;
   for (i=head[key];i&&(p[e[i]].x!=x||p[e[i]].y!=y);i=next[i]);
   if (p[e[i]].x==x&&p[e[i]].y==y)
      return e[i];
   else
   {
      p[++tot].x=x;
      p[tot].y=y;
      f[tot]=tot;
      e[++totm]=tot;
      next[totm]=head[key];
      head[key]=totm;
      return tot;
   }
}

int main()
{
   long i,n,a,b,x1,y1,x2,y2;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld%ld%ld",&x1,&y1,&x2,&y2);
      a=getf(find(x1,y1));
      b=getf(find(x2,y2));
      if (a==b)
      {
         printf("%ld\n",i);
         break;
      }
      else
         f[a]=b;
   }
   if (i>n)
      printf("0\n");
   return 0;
}
