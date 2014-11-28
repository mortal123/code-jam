#include <stdio.h>

struct case1
{
   long v,pos;
}p[401]={{0,0}};
long e[160001]={0},next[160001]={0},head[401]={0},f[401]={0},rec[401]={0},hash[401]={0};
long totm=0,flag=0;

long add(long a,long b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
}

long match(long now)
{
   long i;
   for (i=head[now];i;i=next[i])
      if (hash[e[i]]!=flag)
      {
         hash[e[i]]=flag;
         if (!f[e[i]]||match(f[e[i]]))
         {
            f[e[i]]=now;
            return 1;
         }
      }
   return 0;
}

int main()
{
   long i,j,n,a,b;
   struct case1 t;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      p[i].pos=i;
      scanf("%ld",&p[i].v);
   }
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         if (p[i].v<p[j].v)
         {
            t=p[i];
            p[i]=p[j];
            p[j]=t;
         }
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&a);
      for (j=1;j<=a;j++)
      {
         scanf("%ld",&b);
         add(i,b);
      }
   }
   for (i=1;i<=n;i++)
   {
      flag++;
      match(p[i].pos);
   }
   for (i=1;i<=n;i++)
      rec[f[i]]=i;
   for (i=1;i<=n;i++)
      printf("%ld%c",rec[i],(i==n)?'\n':' ');
   return 0;
}
