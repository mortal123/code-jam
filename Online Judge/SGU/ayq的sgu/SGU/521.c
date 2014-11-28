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

struct case1
{
   long x,y,pos;
}p[100001]={{0,0,0}};
long tree[2000002]={0},f[100001]={0},m[100001]={0},count[100001]={0},rec[100001]={0},apos[100001]={0};
char hash[100001]={0};

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&(p[j].x>t.x||p[j].x==t.x&&p[j].y<t.y))
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&(p[i].x<t.x||p[i].x==t.x&&p[i].y>t.y))
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

void ins(long i,long t)
{
   for (;i<=2000001;i+=lowbit(i))
      tree[i]=max(tree[i],t);
}

long que(long i)
{
   long t=0;
   for (;i;i-=lowbit(i))
      t=max(t,tree[i]);
   return t;
}

int main()
{
   long i,n,ans=0,t=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld",&p[i].x,&p[i].y);
      p[i].pos=i;
      p[i].y+=1000001;
   }
   qs(1,n);
   for (i=1;i<=n;i++)
      apos[p[i].pos]=i;
   for (i=1;i<=n;i++)
   {
      ins(p[i].y+1,f[i]=que(p[i].y)+1);
      t=max(t,f[i]);
   }
   m[t]=oo;
   for (i=n;i>=1;i--)
      if (p[i].y<=m[f[i]])
      {
         hash[p[i].pos]=1;
         count[f[i]]++;
         m[f[i]-1]=max(m[f[i]-1],p[i].y-1);
      }
   for (i=1;i<=n;i++)
      if (hash[i])
         rec[++ans]=i;
   printf("%ld",ans);
   for (i=1;i<=ans;i++)
      printf(" %ld",rec[i]);
   ans=0;
   for (i=1;i<=n;i++)
      if (hash[i]&&count[f[apos[i]]]==1)
         rec[++ans]=i;
   printf("\n%ld",ans);
   for (i=1;i<=ans;i++)
      printf(" %ld",rec[i]);
   printf("\n");
   return 0;
}
