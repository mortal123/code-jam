#include<stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))

long v[500001][2]={0},f[500001]={0},e[500001]={0},next[500001]={0},head[500001]={0},p[500001]={0};
char hash[500001]={'\0'};

int main()
{
   long i,j,n,t,max,totm=0;
   scanf("%ld",&n);
   for (i=2;i<=n;i++)
   {
      scanf("%ld",&f[i]);
      e[++totm]=i;
      next[totm]=head[f[i]];
      head[f[i]]=totm;
   }
   for (i=n;i>=1;i--)
   {
      v[i][1]=1;
      max=0;
      for (j=head[i];j;j=next[j])
      {
         v[i][1]+=v[e[j]][0];
         v[i][0]+=v[e[j]][0];
         if (v[e[j]][1]-v[e[j]][0]>max)
         {
            max=v[e[j]][1]-v[e[j]][0];
            p[i]=e[j];
         }
      }
      v[i][0]+=max;
   }
   printf("%ld\n",v[1][0]*1000);
   for (i=1;i<=n;i++)
   {
      if (!hash[i])
         hash[p[i]]=1;
      else
         printf("%ld\n",i);
   }
   return 0;
}
