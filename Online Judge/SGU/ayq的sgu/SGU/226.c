#include<stdio.h>
#define oo 1000000000

long e[80001]={0},next[80001]={0},head[601]={0},f[601]={0},d[200001]={0};
char hash[601]={'\0'};
long totm=0;

void add(long a,long b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
}

int main()
{
   long i,j,n,m,a,b,c,now,ans,st=50001,en=50003;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld",&a,&b,&c);
      for (j=0;j<=2;j++)
         if (j!=c-1)
            add(a*3-j,b*3-c+1);
   }
   for (i=4;i<=3*n;i++)
      f[i]=oo;
   d[50000]=1;
   d[50001]=2;
   d[50002]=3;
   while (st<=en)
   {
      now=d[st++];
      hash[now]=0;
      for (i=head[now];i;i=next[i])
         if (f[e[i]]>f[now]+1)
         {
            f[e[i]]=f[now]+1;
            if (!hash[e[i]])
            {
               hash[e[i]]=1;
               if (f[e[i]]<=f[d[st]])
                  d[--st]=e[i];
               else
                  d[++en]=e[i];
            }
         }
   }
   ans=f[n*3-2];
   if (f[n*3-1]<ans)
      ans=f[n*3-1];
   if (f[n*3]<ans)
      ans=f[n*3];
   if (ans<oo/2)
      printf("%ld\n",ans);
   else
      printf("-1\n");
   return 0;
}
