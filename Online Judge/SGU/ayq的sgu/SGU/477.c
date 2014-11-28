#include <stdio.h>
#define oo 1000000001
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

int x[5001],y[5001],p[5001],q[5001];
int d,n,m;

void qs(int x,int y,int rec[])
{
   int i=x,j=y,t=rec[(x+y)>>1];
   if (x>=y)
      return;
   rec[(x+y)>>1]=rec[x];
   while (i<j)
   {
      while (i<j&&rec[j]>t)
         j--;
      if (i<j)
         rec[i++]=rec[j];
      while (i<j&&rec[i]<t)
         i++;
      if (i<j)
         rec[j--]=rec[i];
   }
   rec[i]=t;
   qs(x,i-1,rec);
   qs(i+1,y,rec);
}

int check(int t1,int t2)
{
   int l1=0,r1=0,l2=0,r2=0,st1=1,en1,st2=1,en2;
   while (1)
   {
      if (r1<=r2)
      {
         if (st1>n)
            return 1;
         en1=st1;
         while (en1<n&&p[en1+1]-p[en1]<=t1<<1)
            en1++;
         l1=p[st1]-t1;
         r1=p[en1]+t1;
         st1=en1+1;
      }
      else
      {
         if (st2>m)
            return 1;
         en2=st2;
         while (en2<m&&q[en2+1]-q[en2]<=t2<<1)
            en2++;
         l2=q[st2]-t2;
         r2=q[en2]+t2;
         st2=en2+1;
      }
      if (min(r1,r2)-max(l1,l2)>d)
         return 0;
   }
}

int countx(int t1)
{
   int i,j,s=0;
   for (i=1;i<=n;i=j+1)
   {
      j=i;
      while (j<=n&&p[j+1]-p[j]<=t1<<1)
         j++;
      s++;
   }
   return s;
}

int county(int t2)
{
   int i,j,s=0;
   for (i=1;i<=m;i=j+1)
   {
      j=i;
      while (j<=m&&q[j+1]-q[j]<=t2<<1)
         j++;
      s++;
   }
   return s;
}

int main()
{
   int i,j,t,ans1,ans2,ans=oo;
   scanf("%d%d%d",&n,&m,&d);
   for (i=1;i<=n;i++)
      scanf("%d",&p[i]);
   for (i=1;i<=m;i++)
      scanf("%d",&q[i]);
   x[1]=y[1]=1;
   for (i=2;i<=n;i++)
      x[i]=(p[i]-p[i-1]+1)>>1;
   qs(1,n,x);
   for (i=2;i<=m;i++)
      y[i]=(q[i]-q[i-1]+1)>>1;
   qs(1,m,y);
   j=m;
   for (i=1;i<=n;i++)
   {
      while (j&&!check(x[i],y[j]))
         j--;
      if (j)
      {
         t=countx(x[i])+county(y[j]);
         if (t<ans)
         {
            ans=t;
            ans1=x[i];
            ans2=y[j];
         }
      }
   }
   if (ans<oo)
      printf("%d %d\n",ans1,ans2);
   else
      puts("No solution");
   return 0;
}
