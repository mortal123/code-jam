#include <stdio.h>

struct case1
{
   long d,num;
}p[101]={{0,0}};
long ans[10001][2]={0};

int main()
{
   long i,j,n,s=0;
   struct case1 t;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&p[i].d);
      p[i].num=i;
      s+=p[i].d;
   }
   s>>=1;
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         if (p[i].d<p[j].d)
         {
            t=p[i];
            p[i]=p[j];
            p[j]=t;
         }
   j=1;
   printf("%ld\n",s);
   for (i=1;i<=s;i++)
   {
      if (p[j].d==0)
         j++;
      if (p[j].d>1)
         ans[i][0]=p[j].num;
      else
      {
         ans[i][1]=p[j].num;
         ans[i][0]=p[j+1].num;
         p[j+1].d--;
      }
      p[j].d--;
   }
   for (i=1;i<=s;i++)
      if (!ans[i][1])
      {
         if (p[j].d==0)
            j++;
         ans[i][1]=p[j].num;
         p[j].d--;
      }
   for (i=1;i<=s;i++)
      printf("%ld %ld\n",ans[i][0],ans[i][1]);
   return 0;
}
