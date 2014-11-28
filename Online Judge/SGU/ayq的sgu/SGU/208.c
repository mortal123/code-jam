#include <stdio.h>

long mat[21][21]={0},tmp[21][21]={0},hash[21][21]={0},num[401]={0},a[201]={0},ans[201]={0};
long t,n,m,s=0,flag=0;

void count()
{
   long a,b,i,j,x,y,sum;
   s+=n*m;
   for (a=0;a<n;a++)
      for (b=0;b<m;b++)
      {
         sum=0;
         flag++;
         for (i=0;i<n;i++)
            for (j=0;j<m;j++)
               if (hash[i][j]!=flag)
               {
                  sum++;
                  for (x=i,y=j;hash[x][y]!=flag;t=x,x=mat[(x+a)%n][(y+b)%m]/m,y=mat[(t+a)%n][(y+b)%m]%m)
                     hash[x][y]=flag;
               }
         num[sum]++;
      }
}

void rotate()
{
   long i,j;
   for (i=0;i<n;i++)
      for (j=0;j<m;j++)
         tmp[i][j]=mat[i][j];
   for (i=0;i<m;i++)
      for (j=0;j<n;j++)
         mat[i][j]=tmp[n-j-1][i];
   t=n;
   n=m;
   m=t;
}

int main()
{
   long i,j;
   scanf("%ld%ld",&n,&m);
   if (n>m)
   {
      t=n;
      n=m;
      m=t;
   }
   for (i=0;i<n;i++)
      for (j=0;j<m;j++)
         mat[i][j]=i*m+j;
   count();
   rotate();
   if (n==m)
      count();
   rotate();
   count();
   if (n==m)
   {
      rotate();
      count();
   }
   a[1]=1;
   for (i=1;i<=n*m;i++)
   {
      for (j=1;j<=200;j++)
      {
         a[j]=(a[j]<<1)+a[j-1]/10;
         a[j-1]%=10;
      }
      if (num[i])
         for (j=1;j<=200;j++)
         {
            ans[j]+=a[j]*num[i]+ans[j-1]/10;
            ans[j-1]%=10;
         }
   }
   for (j=199;j>=0;j--)
   {
      ans[j]+=ans[j+1]%s*10;
      ans[j+1]/=s;
   }
   j=0;
   for (i=200;i>=1;i--)
   {
      if (ans[i])
         j=1;
      if (j||i==1)
         printf("%ld",ans[i]);
   }
   printf("\n");
   return 0;
}
