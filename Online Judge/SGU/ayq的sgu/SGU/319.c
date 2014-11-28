#include <stdio.h>
#define abb(a) ((a)>0?(a):(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   long x,y1,y2,num;
   char sign;
}q[120001]={0,0,0,0,0};
struct case2
{
   long l,r,st,en,c;
}p[2000001]={0,0,0,0,0};
long long a[60001]={0},b[60001]={0};
long f[60001]={0};
long tot=1;

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=q[(x+y)>>1];
   if (x>=y)
      return;
   q[(x+y)>>1]=q[x];
   while (i<j)
   {
      while (i<j&&q[j].x>t.x)
         j--;
      if (i<j)
         q[i++]=q[j];
      while (i<j&&q[i].x<t.x)
         i++;
      if (i<j)
         q[j--]=q[i];
   }
   q[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

void qs2(long x,long y)
{
   long i=x,j=y;
   long long t=a[(x+y)>>1];
   if (x>=y)
      return;
   a[(x+y)>>1]=a[x];
   while (i<j)
   {
      while (i<j&&a[j]>t)
         j--;
      if (i<j)
         a[i++]=a[j];
      while (i<j&&a[i]<t)
         i++;
      if (i<j)
         a[j--]=a[i];
   }
   a[i]=t;
   qs2(x,i-1);
   qs2(i+1,y);
}

void maintain(long now,long mid)
{
   if (p[now].l==0)
   {
      p[++tot]=(struct case2){0,0,p[now].st,mid,-1};
      p[now].l=tot;
   }
   if (p[now].r==0)
   {
      p[++tot]=(struct case2){0,0,mid,p[now].en,-1};
      p[now].r=tot;
   }
   if (p[now].c!=-1)
   {
      p[p[now].l].c=p[p[now].r].c=p[now].c;
      p[now].c=-1;
   }
}

long ins(long now,long st,long en,long c)
{
   long mid=(p[now].st+p[now].en)>>1;
   if (p[now].st==st&&p[now].en==en)
      p[now].c=c;
   else
   {
      maintain(now,mid);
      if (en<=mid)
         ins(p[now].l,st,en,c);
      else if (st>=mid)
         ins(p[now].r,st,en,c);
      else
      {
         ins(p[now].l,st,mid,c);
         ins(p[now].r,mid,en,c);
      }
   }
}

long que(long now,long pos)
{
   long mid=(p[now].st+p[now].en)>>1;
   if (p[now].st==p[now].en-1)
      return p[now].c;
   maintain(now,mid);
   if (pos<mid)
      return que(p[now].l,pos);
   return que(p[now].r,pos);
}

int main()
{
   long i,n,x1,y1,x2,y2;
   scanf("%ld%ld%ld",&n,&x1,&y1);
   a[0]=b[0]=(long long)x1*y1;
   p[1]=(struct case2){0,0,1,y1,0};
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld%ld%ld",&x1,&y1,&x2,&y2);
      a[i]=b[i]=abb((long long)(x1-x2)*(y1-y2));
      q[i*2-1]=(struct case1){min(x1,x2),min(y1,y2),max(y1,y2),i,1};
      q[i*2]=(struct case1){max(x1,x2),min(y1,y2),max(y1,y2),i,0};
   }
   qs(1,2*n);
   for (i=1;i<=2*n;i++)
      if (q[i].sign)
      {
         f[q[i].num]=que(1,q[i].y1);
         ins(1,q[i].y1,q[i].y2,q[i].num);
      }
      else
         ins(1,q[i].y1,q[i].y2,que(1,q[i].y2));
   for (i=1;i<=n;i++)
      a[f[i]]-=b[i];
   qs2(0,n);
   for (i=0;i<=n;i++)
      printf("%I64d%c",a[i],(i==n)?'\n':' ');
   return 0;
}
