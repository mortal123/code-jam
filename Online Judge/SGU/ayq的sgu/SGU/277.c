#include <stdio.h>
#include <math.h>
#define eps 1e-8
#define pi 3.141592659
#define lowbit(a) ((a)&(-(a)))
#define abb(a) ((a)>0?(a):(-(a)))
#define sign(a) ((a)?((a)>0?1:-1):0)
#define cj(x1,y1,x2,y2) ((long long)(x1)*(y2)-(long long)(x2)*(y1))

struct case1
{
   long x,y,pos;
}p[100004]={{0,0,0}};
struct case2
{
   long pos;
   double d;
}rec[100004]={{0},{0}};
long tree[100004]={0};
long n,tot=0;

double D(double x,double y)
{
   if (x>1e-8&&y>=0)
      return atan(y/x);
   if (x<-1e-8)
      return pi+atan(y/x);
   if (x>1e-8)
      return 2*pi-atan(-y/x);
   if (y>0)
      return pi/2;
   return pi*3/2;
}

void qs(long x,long y)
{
   long i=x,j=y;
   struct case2 t=rec[(x+y)>>1];
   if (x>=y)
      return;
   rec[(x+y)>>1]=rec[x];
   while (i<j)
   {
      while (i<j&&rec[j].d>t.d)
         j--;
      if (i<j)
         rec[i++]=rec[j];
      while (i<j&&rec[i].d<t.d)
         i++;
      if (i<j)
         rec[j--]=rec[i];
   }
   rec[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

void ins(long i,long add)
{
   tot+=add;
   for (;i<=n+3;i+=lowbit(i))
      tree[i]+=add;
}

long sum(long i)
{
   long s=0;
   for (;i;i-=lowbit(i))
      s+=tree[i];
   return s;
}

long last(long now)
{
   long l=0,r=now-1,mid,t=sum(now-1);
   if (!t)
      return last(n+4);
   while (l<r-1)
   {
      mid=(l+r)>>1;
      if (sum(mid)==t)
         r=mid;
      else
         l=mid;
   }
   return rec[r].pos;
}

long next(long now)
{
   long l=now,r=n+3,mid,t=sum(now);
   if (t==tot)
      return next(0);
   while (l<r-1)
   {
      mid=(l+r)>>1;
      if (sum(mid)>t)
         r=mid;
      else
         l=mid;
   }
   return rec[r].pos;
}

int main()
{
   long i,x,y,a,b,pre;
   long long ans;
   scanf("%ld%ld%ld%ld%ld%ld%ld",&p[1].x,&p[1].y,&p[2].x,&p[2].y,&p[3].x,&p[3].y,&n);
   x=p[1].x+p[2].x+p[3].x;
   y=p[1].y+p[2].y+p[3].y;
   p[1].x*=3;
   p[1].y*=3;
   p[2].x*=3;
   p[2].y*=3;
   p[3].x*=3;
   p[3].y*=3;
   rec[1]=(struct case2){1,D(p[1].x-x,p[1].y-y)};
   rec[2]=(struct case2){2,D(p[2].x-x,p[2].y-y)};
   rec[3]=(struct case2){3,D(p[3].x-x,p[3].y-y)};
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld",&p[i+3].x,&p[i+3].y);
      p[i+3].x*=3;
      p[i+3].y*=3;
      rec[i+3]=(struct case2){i+3,D(p[i+3].x-x,p[i+3].y-y)};
   }
   qs(1,n+3);
   for (i=1;i<=n+3;i++)
      p[rec[i].pos].pos=i;
   ins(p[1].pos,1);
   ins(p[2].pos,1);
   ins(p[3].pos,1);
   ans=abb(cj(p[1].x-p[2].x,p[1].y-p[2].y,p[3].x-p[2].x,p[3].y-p[2].y));
   for (i=4;i<=n+3;i++)
   {
      a=last(p[i].pos);
      b=next(p[i].pos);
      if (sign(cj(p[i].x-p[a].x,p[i].y-p[a].y,p[b].x-p[a].x,p[b].y-p[a].y))*sign(cj(x-p[a].x,y-p[a].y,p[b].x-p[a].x,p[b].y-p[a].y))<0)
      {
         ans-=cj(p[a].x-x,p[a].y-y,p[b].x-x,p[b].y-y);
         while (1)
         {
            pre=last(p[a].pos);
            if (cj(p[a].x-p[i].x,p[a].y-p[i].y,p[pre].x-p[i].x,p[pre].y-p[i].y)>0)
            {
               ans-=cj(p[pre].x-x,p[pre].y-y,p[a].x-x,p[a].y-y);
               ins(p[a].pos,-1);
               a=pre;
            }
            else
               break;
         }
         while (1)
         {
            pre=next(p[b].pos);
            if (cj(p[b].x-p[i].x,p[b].y-p[i].y,p[pre].x-p[i].x,p[pre].y-p[i].y)<0)
            {
               ans-=cj(p[b].x-x,p[b].y-y,p[pre].x-x,p[pre].y-y);
               ins(p[b].pos,-1);
               b=pre;
            }
            else
               break;
         }
         ins(p[i].pos,1);
         ans+=cj(p[a].x-x,p[a].y-y,p[i].x-x,p[i].y-y)+cj(p[i].x-x,p[i].y-y,p[b].x-x,p[b].y-y);
      }
      printf("%I64d\n",ans/9);
   }
   return 0;
}
