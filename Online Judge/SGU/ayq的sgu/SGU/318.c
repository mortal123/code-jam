#include <stdio.h>

char map[101][101]={'\0'},hash[101]={'\0'},need[101]={'\0'};
long f[101]={0};

long getf(long now)
{
   if (f[now]==now)
      return now;
   return f[now]=getf(f[now]);
}

int main()
{
   long i,j,k,n,m,a,b,ans=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld",&a);
      for (j=1;j<=a;j++)
      {
         scanf("%ld",&b);
         map[i][b]=need[b]=1;
      }
   }
   for (i=1;i<=n;i++)
      f[i]=i;
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
      {
         a=getf(i);
         b=getf(j);
         if (a!=b)
         {
            for (k=1;k<=m&&map[k][i]==map[k][j];k++);
            if (k>m)
               f[a]=b;
         }
      }
   for (i=1;i<=n;i++)
      hash[getf(i)]=1;
   for (i=1;i<=n;i++)
      ans+=hash[i]*need[i];
   printf("%ld\n",ans);
   return 0;
}
