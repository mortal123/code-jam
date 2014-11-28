#include<stdio.h>

long f[501]={0},e[50001]={0},next[50001]={0},head[501]={0},hash[501]={0},a[50001]={0},b[50001]={0};
char choose[501][501]={'\0'};
long totm=0,flag=0;

void add(long a,long b)
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
   long i,n,m,ans=0;
   scanf("%ld%ld",&n,&m);
   m=n*m/2;
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld",&a[i],&b[i]);
      add(a[i],b[i]);
      add(b[i],a[i]);
   }
   for (i=1;i<=n;i++)
   {
      flag++;
      ans+=match(i);
   }
   if (ans!=n)
      printf("NO\n");
   else
   {
      printf("YES\n");
      for (i=1;i<=n;i++)
         choose[i][f[i]]=choose[f[i]][i]=1;
      for (i=1;i<=m;i++)
         if (choose[a[i]][b[i]])
            printf("%ld\n",i);
   }
   return 0;
}
