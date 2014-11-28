#include <stdio.h>
#define abb(a) ((a)>0?(a):(-(a)))
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   long x,y;
}p[4001]={{0,0}};

struct case1 cross(long a,long b)
{
   long t;
   if (p[a].x==p[a-1].x&&p[b].x==p[b-1].x)
   {
      if (p[a].x!=p[b].x||max(p[a].y,p[a-1].y)!=min(p[b].y,p[b-1].y)&&min(p[a].y,p[a-1].y)!=max(p[b].y,p[b-1].y))
         return (struct case1){11111,0};
      return (struct case1){p[a].x,(max(p[a].y,p[a-1].y)==min(p[b].y,p[b-1].y))?max(p[a].y,p[a-1].y):min(p[a].y,p[a-1].y)};
   }
   if (p[a].y==p[a-1].y&&p[b].y==p[b-1].y)
   {
      if (p[a].y!=p[b].y||max(p[a].x,p[a-1].x)!=min(p[b].x,p[b-1].x)&&min(p[a].x,p[a-1].x)!=max(p[b].x,p[b-1].x))
         return (struct case1){11111,0};
      return (struct case1){(max(p[a].x,p[a-1].x)==min(p[b].x,p[b-1].x))?max(p[a].x,p[a-1].x):min(p[a].x,p[a-1].x),p[a].y};
   }
   if (p[a].x==p[a-1].x&&p[b].y==p[b-1].y)
   {
      t=a;
      a=b;
      b=t;
   }
   if (p[b].x>max(p[a].x,p[a-1].x)||p[b].x<min(p[a].x,p[a-1].x)||p[a].y>max(p[b].y,p[b-1].y)||p[a].y<min(p[b].y,p[b-1].y))
      return (struct case1){11111,0};
   return (struct case1){p[b].x,p[a].y};
}

int main()
{
   long i,j,n,s,ans=0;
   struct case1 t;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld",&p[i].x,&p[i].y);
      if (i>1)
         ans+=abb(p[i].x+p[i].y-p[i-1].x-p[i-1].y);
   }
   for (i=4;i<=n;i++)
   {
      s=abb(p[i-1].x+p[i-1].y-p[i-2].x-p[i-2].y);
      for (j=i-2;j>=2;j--)
      {
         t=cross(i,j);
         if (t.x!=11111)
            ans=min(ans,s+abb(t.x+t.y-p[i-1].x-p[i-1].y)+abb(t.x+t.y-p[j].x-p[j].y));
         s+=abb(p[j].x+p[j].y-p[j-1].x-p[j-1].y);
      }
   }
   printf("%ld\n",ans);
   return 0;
}
