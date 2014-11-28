#include <stdio.h>
#define abb(a) ((a)>0?(a):(-(a)))
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))

struct case1
{
   long v;
   char hash;
}p[1001]={{0},{'\0'}};

int main()
{
   long i,j,n,k,x1,y1,x2,y2,x3,y3,x4,y4,p1,q1,p2,q2,mx,my,ans=0;
   struct case1 t;
   scanf("%ld%ld",&n,&k);
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld%ld%ld%ld%ld%ld%ld%ld%ld%ld%ld",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4,&p1,&q1,&p2,&q2);
      p[i].v=abb(cj(x3-x1,y3-y1,x2-x1,y2-y1));
      mx=x1+x2+x3+x4;
      my=y1+y2+y3+y4;
      p1*=4;
      q1*=4;
      p2*=4;
      q2*=4;
      p[i].hash=(p1==mx&&q1==my||p2==mx&&q2==my||(p1>=mx&&p2>=mx||p1<=mx&&p2<=mx)&&(q1>=my&&q2>=my||q1<=my&&q2<=my)&&!cj(p1-mx,q1-my,p2-mx,q2-my));
   }
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         if (p[i].v<p[j].v||p[i].v==p[j].v&&p[j].hash)
         {
            t=p[i];
            p[i]=p[j];
            p[j]=t;
         }
   for (i=1;i<=k;i++)
      if (p[i].hash==0)
         ans+=p[i].v;
   printf("%.3lf ",ans/2.0);
   ans=0;
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         if (p[i].v<p[j].v||p[i].v==p[j].v&&p[j].hash==0)
         {
            t=p[i];
            p[i]=p[j];
            p[j]=t;
         }
   for (i=1;i<=k;i++)
      if (p[i].hash==0)
         ans+=p[i].v;
   printf("%.3lf\n",ans/2.0);
   return 0;
}
