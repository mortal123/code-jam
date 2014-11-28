#include<stdio.h>
#define oo 1000001

struct case1
{
   long v,next,pos,relate;
   char sign;
}w[1201]={{0,0},{'\0'}};
long f[1202][602]={0},l[1202][602]={0},ans[602]={0};

long cmp(struct case1 a,struct case1 b)
{
   if (a.relate<b.relate)
      return -1;
   if (a.relate>b.relate)
      return 1;
   if (a.sign)
      return -1;
   return 1;
}

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=w[(x+y)>>1];
   if (x>=y)
      return;
   w[(x+y)>>1]=w[x];
   while (i<j)
   {
      while (i<j&&cmp(w[j],t)>0)
         j--;
      if (i<j)
         w[i++]=w[j];
      while (i<j&&cmp(w[i],t)<0)
         i++;
      if (i<j)
         w[j--]=w[i];
   }
   w[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

int main()
{
   long i,j,last,n,m,p,tot=0;
   scanf("%ld%ld%ld",&n,&m,&p);
   for (i=1;i<=m;i++)
   {
      scanf("%ld",&w[i].v);
      w[i].relate=i;
      w[i].sign=1;
   }
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld",&w[i+m].v,&w[i+m].relate);
      w[i+m].pos=i;
   }
   qs(1,n+m);
   last=n+m+1;
   for (i=n+m;i>=1;i--)
      if (w[i].sign)
      {
         w[i].next=last;
         last=i;
      }
   for (i=1;i<=n+m+1;i++)
      for (j=0;j<=n;j++)
         f[i][j]=oo;
   f[1][0]=0;
   for (i=1;i<=n+m;i++)
      for (j=0;j<=n;j++)
         if (f[i][j]<oo)
         {
            if (w[i].sign)
            {
               if (f[w[i].next][j]>f[i][j])
               {
                  f[w[i].next][j]=f[i][j];
                  l[w[i].next][j]=i*(n+1)+j;
               }
               if (f[i+1][j]>f[i][j]+w[i].v)
               {
                  f[i+1][j]=f[i][j]+w[i].v;
                  l[i+1][j]=i*(n+1)+j;
               }
            }
            else
            {
               if (f[i+1][j]>f[i][j])
               {
                  f[i+1][j]=f[i][j];
                  l[i+1][j]=i*(n+1)+j;
               }
               if (f[i+1][j+1]>f[i][j]+w[i].v)
               {
                  f[i+1][j+1]=f[i][j]+w[i].v;
                  l[i+1][j+1]=i*(n+1)+j;
               }
            }
         }
   for (j=n;f[n+m+1][j]>p;j--);
   printf("%ld\n",j);
   if (j)
   {
      i=n+m+1;
      while (j)
      {
         last=l[i][j];
         if (j==last%(n+1)+1)
            ans[++tot]=w[last/(n+1)].pos;
         i=last/(n+1);
         j=last%(n+1);
      }
      for (i=1;i<tot;i++)
         printf("%ld ",ans[i]);
      printf("%ld\n",ans[tot]);
   }
   return 0;
}
