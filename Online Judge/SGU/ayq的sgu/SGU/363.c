#include <stdio.h>

struct case1
{
   long left[101],num[101];
   long st,en;
}d[101]={{0,0},{0,0}};
long ans[101][2]={0};

int main()
{
   long i,j,n,m,k,t,tmp,last=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
      d[i].st=1;
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld",&k,&t);
      for (j=1;j<=m;j++)
      {
         tmp=last;
         while (d[j].st<=d[j].en&&d[j].left[d[j].st]<=k-tmp)
         {
            tmp+=d[j].left[d[j].st];
            ans[d[j].num[d[j].st++]][1]=tmp;
         }
         if (d[j].st<=d[j].en)
            d[j].left[d[j].st]-=k-tmp;
      }
      tmp=1;
      for (j=2;j<=m;j++)
         if (d[j].en-d[j].st<d[tmp].en-d[tmp].st)
            tmp=j;
      ans[i][0]=tmp;
      d[tmp].num[++d[tmp].en]=i;
      d[tmp].left[d[tmp].en]=t;
      last=k;
   }
   for (i=1;i<=m;i++)
   {
      tmp=last;
      while (d[i].st<=d[i].en)
      {
         tmp+=d[i].left[d[i].st];
         ans[d[i].num[d[i].st++]][1]=tmp;
      }
   }
   for (i=1;i<=n;i++)
      printf("%ld %ld\n",ans[i][0],ans[i][1]);
   return 0;
}
