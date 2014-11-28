#include <stdio.h>
#define oo 1000000000

struct case1
{
   long a,b;
}q[60001]={0,0};
long r[101][60002]={0,0},p[101]={0},f[102][2001][21]={0},num[102][2001][21]={0},ans[21]={0};

void qs(long pos,long x,long y)
{
   long i=x,j=y,t=r[pos][(x+y)>>1];
   if (x>=y)
      return;
   r[pos][(x+y)>>1]=r[pos][x];
   while (i<j)
   {
      while (i<j&&q[r[pos][j]].a+q[r[pos][j]].b<q[t].a+q[t].b)
         j--;
      if (i<j)
         r[pos][i++]=r[pos][j];
      while (i<j&&q[r[pos][i]].a+q[r[pos][i]].b>q[t].a+q[t].b)
         i++;
      if (i<j)
         r[pos][j--]=r[pos][i];
   }
   r[pos][i]=t;
   qs(pos,x,i-1);
   qs(pos,i+1,y);
}

int main()
{
   long i,j,k,l,n,m,s,t,a=0,b=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld",&q[i].a,&q[i].b);
      r[q[i].b-q[i].a+50][++p[q[i].b-q[i].a+50]]=i;
   }
   for (i=0;i<=100;i++)
      qs(i,1,p[i]);
   for (i=0;i<=101;i++)
      for (j=0;j<=2000;j++)
         for (k=0;k<=m;k++)
            f[i][j][k]=-oo;
   f[0][1000][0]=0;
   for (i=1;i<=101;i++)
   {
      s=0;
      for (j=0;j<=p[i-1]&&j<=m;j++)
      {
         s+=q[r[i-1][j]].a+q[r[i-1][j]].b;
         for (k=0;k<=2000;k++)
            if (k-j*(i-51)>=0&&k-j*(i-51)<=2000)
               for (l=j;l<=m;l++)
                  if (f[i-1][k-j*(i-51)][l-j]+s>f[i][k][l])
                  {
                     f[i][k][l]=f[i-1][k-j*(i-51)][l-j]+s;
                     num[i][k][l]=j;
                  }
      }
   }
   for (i=0;f[101][1000-i][m]<0&&f[101][1000+i][m]<0;i++);
   if (f[101][1000-i][m]>f[101][1000+i][m])
      j=1000-i;
   else
      j=1000+i;
   k=m;
   s=0;
   for (i=101;i>=1;i--)
   {
      for (l=1;l<=num[i][j][k];l++)
      {
         a+=q[r[i-1][l]].a;
         b+=q[r[i-1][l]].b;
         ans[++s]=r[i-1][l];
      }
      t=num[i][j][k];
      j-=t*(i-51);
      k-=t;
   }
   for (i=1;i<m;i++)
      for (j=i+1;j<=m;j++)
         if (ans[i]>ans[j])
         {
            ans[i]^=ans[j];
            ans[j]^=ans[i];
            ans[i]^=ans[j];
         }
   printf("%ld %ld\n",a,b);
   for (i=1;i<=m;i++)
      printf("%ld%c",ans[i],(i==m)?'\n':' ');
   return 0;
}
