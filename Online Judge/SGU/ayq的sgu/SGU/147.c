#include <stdio.h>
#define abb(a) ((a)>0?(a):(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

int main()
{
   long i,n,x1,y1,x2,y2,x3,y3,t,ly1,ly2,ry1,ry2,w;
   scanf("%ld%ld%ld%ld%ld%ld%ld",&n,&x1,&y1,&x2,&y2,&x3,&y3);
   if (abb(x2-x1)<abb(y2-y1))
   {
      t=x1;
      x1=y1;
      y1=t;
      t=x2;
      x2=y2;
      y2=t;
      t=x3;
      x3=y3;
      y3=t;
   }
   if (x1>x2)
   {
      t=y1;
      y1=y2;
      y2=t;
      t=x1;
      x1=x2;
      x2=t;
   }
   w=(x2-x1)-abb(y1-y2)+1;
   for (i=1;i<(x2-x1)/2;i++)
   {
      ly1=max(y1-i,y2-x2+x1+i);
      ly2=min(y1+i,y2+x2-x1-i);
      ry1=max(y2-i,y1-x2+x1+i);
      ry2=min(y2+i,y1+x2-x1-i);
      ly1=max(ly1,1);
      ry1=max(ry1,1);
      ly2=min(ly2,n);
      ry2=min(ry2,n);
      if ((x3-i==x1+i||x3+i==x1+i)&&y3+i>=ly1&&y3-i<=ly2||(y3+i<=ly2&&y3+i>=ly1||y3-i<=ly2&&y3-i>=ly1)&&x3-i<=x1+i&&x3+i>=x1+i||(x3-i==x2-i||x3+i==x2-i)&&y3+i>=ry1&&y3-i<=ry2||(y3+i<=ry2&&y3+i>=ry1||y3-i<=ry2&&y3-i>=ry1)&&x3-i<=x2-i&&x3+i>=x2-i)
         break;
   }
   if (i==(x2-x1)/2)
      printf("NO\n%ld\n",x2-x1-1);
   else
      printf("YES\n%ld\n",i);
   return 0;
}
