#include<stdio.h>
#define oo 2100000000

long d[500001]={0},e[32001]={0},next[32001]={0},num[32001]={0},head[401]={0},f[401]={0},ans[401]={0};
char hash[401]={'\0'};
long totm=0;

void add(long a,long b,long c)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   num[totm]=c;
}

int main()
{
   long i,j,k,n,m,s,t,a,b,now,tot,st=200000,en=200000;
   scanf("%ld%ld%ld%ld",&n,&m,&s,&t);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld",&a,&b);
      add(a,b,i);
      add(b,a,i);
   }
   for (i=1;i<=n;i++)
      f[i]=oo;
   f[s]=0;
   d[200000]=s;
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
   printf("%ld\n",f[t]);
   for (i=0;i<f[t];i++)
   {
      tot=0;
      for (j=1;j<=n;j++)
         if (f[j]==i)
            for (k=head[j];k;k=next[k])
               if (f[e[k]]==i+1)
                  ans[++tot]=num[k];
      printf("%ld",tot);
      for (j=1;j<=tot;j++)
         printf(" %ld",ans[j]);
      printf("\n");
   }
   return 0;
}
