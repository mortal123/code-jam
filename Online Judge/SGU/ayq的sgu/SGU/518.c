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

long map[201][201]={0},f[201][201]={0},rec[201]={0};

int main()
{
   long i,j,k,n,l,a,ans=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
         scanf("%ld",&map[i][j]);
   scanf("%ld",&l);
   f[0][1]=1;
   for (i=1;i<=l;i++)
   {
      scanf("%ld",&a);
      for (j=1;j<=n;j++)
         for (k=1;k<=n;k++)
            if (k!=j&&map[k][j]==a&&f[i-1][k])
            {
               f[i][j]=1;
               break;
            }
   }
   for (i=1;i<=n;i++)
      if (f[l][i])
         rec[++ans]=i;
   printf("%ld\n",ans);
   for (i=1;i<=ans;i++)
      printf("%ld%c",rec[i],(i==ans)?'\n':' ');
   return 0;
}
