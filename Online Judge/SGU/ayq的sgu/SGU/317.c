#include<stdio.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   long pos,p;
   long *d,*v;
}a[5002]={{0,0},{0,0}};
double f[5002]={0};

long qs1(long x,long y)
{
   long i=x,j=y;
   struct case1 t=a[(x+y)>>1];
   if (x>=y)
      return;
   a[(x+y)>>1]=a[x];
   while (i<j)
   {
      while (i<j&&a[j].pos>t.pos)
         j--;
      if (i<j)
         a[i++]=a[j];
      while (i<j&&a[i].pos<t.pos)
         i++;
      if (i<j)
         a[j--]=a[i];
   }
   a[i]=t;
   qs1(x,i-1);
   qs1(i+1,y);
}

void qs2(long v,long x,long y)
{
   long i=x,j=y,td,tv;
   if (x>=y)
      return;
   td=a[v].d[(x+y)>>1];
   tv=a[v].v[(x+y)>>1];
   a[v].d[(x+y)>>1]=a[v].d[x];
   a[v].v[(x+y)>>1]=a[v].v[x];
   while (i<j)
   {
      while (i<j&&a[v].v[j]<tv)
         j--;
      if (i<j)
      {
         a[v].d[i]=a[v].d[j];
         a[v].v[i++]=a[v].v[j];
      }
      while (i<j&&a[v].v[i]>tv)
         i++;
      if (i<j)
      {
         a[v].d[j]=a[v].d[i];
         a[v].v[j--]=a[v].v[i];
      }
   }
   a[v].d[i]=td;
   a[v].v[i]=tv;
   qs2(v,x,i-1);
   qs2(v,i+1,y);
}

int main()
{
   long i,j,k,b,n;
   scanf("%ld%ld",&b,&n);
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld",&a[i].pos,&a[i].p);
      a[i].d=(long*)malloc((a[i].p+1)*sizeof(long));
      a[i].v=(long*)malloc((a[i].p+1)*sizeof(long));
      for (j=1;j<=a[i].p;j++)
         scanf("%ld%ld",&a[i].v[j],&a[i].d[j]);
   }
   a[++n].pos=b;
   qs1(1,n);
   for (i=1;i<=n;i++)
      qs2(i,1,a[i].p);
   if (a[1].pos)
      printf("-1\n");
   else
   {
      f[1]=0;
      for (n=1;a[n].pos!=b;n++);
      for (i=2;i<=n;i++)
         f[i]=oo;
      for (i=1;i<=n-1;i++)
      {
         k=1;
         for (j=i+1;j<=n&&k<=a[i].p;j++)
         {
            while (k<=a[i].p&&a[i].d[k]<a[j].pos-a[i].pos)
               k++;
            if (k<=a[i].p)
               f[j]=min(f[j],f[i]+1.0*(a[j].pos-a[i].pos)/a[i].v[k]);
         }
      }
      if (f[n]<oo-1)
         printf("%lf\n",f[n]);
      else
         printf("-1\n");
   }
   return 0;
}
