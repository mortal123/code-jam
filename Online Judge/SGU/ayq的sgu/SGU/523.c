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

long a[101]={0},hash[101]={0};
char t[101]={0};

int main()
{
   long i,j,n,s;
   scanf("%ld%ld",&n,&s);
   for (i=1;i<=n;i++)
      scanf("%ld",&a[i]);
   for (i=1;i<=n;i++)
      if (!hash[i])
      {
         memset(t,0,sizeof(t));
         for (j=i;j<=n;j++)
            if (!hash[j]&&a[j]>=min(a[i],s)&&a[j]<=max(a[i],s))
            {
               hash[j]=1;
               t[a[j]]=1;
            }
         if (a[i]>s)
         {
            for (j=s;j<=a[i];j++)
               if (t[j])
                  printf("%ld ",j);
         }
         else
            for (j=s;j>=a[i];j--)
               if (t[j])
                  printf("%ld ",j);
         s=a[i];
      }
   return 0;
}
