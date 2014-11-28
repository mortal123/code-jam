#include<stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   long x1,y1,x2,y2;
}l[10001]={{0,0,0,0}};

int main()
{
   long i,j,n,x,y,num=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%ld%ld%ld%ld",&l[i].x1,&l[i].y1,&l[i].x2,&l[i].y2);
   scanf("%ld%ld",&x,&y);
   for (i=1;i<=n;i++)
   {
      if (l[i].x1==l[i].x2)
      {
         if (l[i].x1==x&&max(l[i].y1,l[i].y2)>=y&&min(l[i].y1,l[i].y2)<=y)
         {
            printf("BORDER\n");
            goto end;
         }
      }
      else
      {
         if (l[i].y1==y&&max(l[i].x1,l[i].x2)>=x&&min(l[i].x1,l[i].x2)<=x)
         {
            printf("BORDER\n");
            goto end;
         }
      }
   }
   for (i=1;i<=n;i++)
      if (l[i].x1==l[i].x2&&l[i].x1>x&&max(l[i].y1,l[i].y2)>=y&&min(l[i].y1,l[i].y2)<y)
         num++;
   if (num%2)
      printf("INSIDE\n");
   else
      printf("OUTSIDE\n");
   end:
   return 0;
}
