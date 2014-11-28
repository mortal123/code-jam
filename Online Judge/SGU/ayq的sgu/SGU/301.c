#include <stdio.h>
#define oo 1000000000
#define lowbit(a) ((a)&(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   long v,sign;
}p[406001]={{0,0}};
long v[2001][2001]={0},ans[2001]={0},d[2001]={0},f[2001]={0};
char hash[2001]={0};

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&(p[j].v>t.v||p[j].v==t.v&&p[j].sign>t.sign))
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&(p[i].v<t.v||p[i].v==t.v&&t.sign>p[i].sign))
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

int main()
{
   long i,n,s,t,m,a,b,c,x,now,st=1,en=1,sum=0,tot=0;
   scanf("%ld%ld%ld%ld",&n,&s,&t,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld",&a,&b,&c);
      v[a][b]=v[b][a]=c;
   }
   for (i=1;i<=n;i++)
      f[i]=oo;
   f[s]=1;
   while (1)
   {
      x=0;
      for (i=1;i<=n;i++)
         if (!hash[i]&&f[i]<oo&&(!x||f[i]<f[x]))
            x=i;
      if (!x)
         break;
      hash[x]=1;
      for (i=1;i<=n;i++)
         if (v[x][i])
            f[i]=min(f[i],f[x]+v[x][i]);
   }
   d[1]=t;
   hash[t]=2;
   while (st<=en)
   {
      now=d[st++];
      p[++sum].v=f[now];
      p[++sum]=(struct case1){f[now]+1,-1};
      p[++sum]=(struct case1){f[now],now};
      for (i=1;i<=n;i++)
         if (v[now][i]&&f[i]==f[now]-v[now][i])
         {
            p[++sum].v=f[i]+1;
            p[++sum]=(struct case1){f[now],-1};
            if (hash[i]!=2)
            {
               hash[i]=2;
               d[++en]=i;
            }
         }
   }
   qs(1,sum);
   for (i=1;i<=sum;i++)
      if (p[i].sign==-1)
         tot--;
      else if (p[i].sign==0)
         tot++;
      else
         ans[p[i].sign]=tot;
   for (i=1;i<=n;i++)
      printf("%ld%c",ans[i],(i==n)?'\n':' ');
   return 0;
}
