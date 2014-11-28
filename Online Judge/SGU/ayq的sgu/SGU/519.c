#include<math.h>
#include<time.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define oo 1000000000
#define pi 3.14159265359
#define zero(a) (abb(a)<=1e-7)
#define lowbit(a) ((a)&(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abb(a) ((a)>0?(a):(-(a)))
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y2))
#define dj(x1,y1,x2,y2) ((x1)*(y1)+(y1)*(y2))
#define dis(x1,y1,x2,y2) sqrt(((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1)))

long mat[102][102]={0};

int main()
{
   long i,j,n,m,ans=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
      {
         scanf("%1ld",&mat[i][j]);
         if (mat[i][j])
            ans+=2;
      }
   for (i=1;i<=n;i++)
      for (j=1;j<=m+1;j++)
         ans+=abb(mat[i][j]-mat[i][j-1]);
   for (i=1;i<=m;i++)
      for (j=1;j<=n+1;j++)
         ans+=abb(mat[j][i]-mat[j-1][i]);
   printf("%ld\n",ans);
   return 0;
}
