#include <stdio.h>
#define oo 1000000000
#define abb(a) ((a)>0?(a):(-(a)))

long a[1001]={0},map[129][129]={0},f[1001][129]={0},last[1001][129]={0},rec[1001]={0};

int main()
{
   long i,j,k,l,n,m,t,ans=oo;
   scanf("%ld",&l);
   for (i=1;i<=l;i++)
      scanf("%ld",&a[i]);
   scanf("%ld%ld",&n,&m);
   for (i=0;i<n;i++)
      for (j=0;j<m;j++)
         scanf("%ld",&map[i][j]);
   for (i=1;i<m;i++)
      f[0][i]=oo;
   for (i=1;i<=l;i++)
      for (j=0;j<m;j++)
      {
         f[i][j]=oo;
         for (k=0;k<m;k++)
         {
            t=f[i-1][k]+abb(a[i]-map[k%n][j]);
            if (t<f[i][j])
            {
               f[i][j]=t;
               last[i][j]=k;
            }
         }
      }
   for (i=0;i<m;i++)
      if (f[l][i]<ans)
      {
         ans=f[l][i];
         t=i;
      }
   printf("%ld\n",ans);
   for (i=l;i>=1;i--)
   {
      rec[i]=t;
      t=last[i][t];
   }
   for (i=1;i<=l;i++)
      printf("%ld%c",rec[i],(i==l)?'\n':' ');
   return 0;
}
