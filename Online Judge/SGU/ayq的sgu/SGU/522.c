#include <stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))

struct case1
{
   int x,y;
}p[401];
char ans[3201];
int m1[802],m2[802];

int main()
{
   int i,j,v,x,y,n,m,o=0,f1=0,f2=0,minx=400,maxx=-400,miny=400,maxy=-400,va=0;
   scanf("%d%d%d",&v,&x,&y);
   for (i=1;i<=v;i++)
   {
      scanf("%d%d",&p[i].x,&p[i].y);
      minx=min(minx,p[i].x);
      maxx=max(maxx,p[i].x);
      miny=min(miny,p[i].y);
      maxy=max(maxy,p[i].y);
   }
   if (x>=maxx&&y>=maxy)
   {
      n=x-minx;
      m=y-miny;
      f1=f2=1;
      x=-x;
      y=-y;
      for (i=1;i<=v;i++)
      {
         p[i].x=-p[i].x;
         p[i].y=-p[i].y;
      }
   }
   else if (x>=maxx&&y<=miny)
   {
      n=x-minx;
      m=maxy-y;
      f1=1;
      x=-x;
      for (i=1;i<=v;i++)
         p[i].x=-p[i].x;
   }
   else if (x<=minx&&y>=maxy)
   {
      n=maxx-x;
      m=y-miny;
      f2=1;
      y=-y;
      for (i=1;i<=v;i++)
         p[i].y=-p[i].y;
   }
   else if (x<=minx&&y<=miny)
   {
      n=maxx-x;
      m=maxy-y;
   }
   else
   {
      puts("-1");
      goto end;
   }
   n+=(!n);
   m+=(!m);
   for (i=0;i<=m;i++)
   {
      m1[i]=n-1;
      m2[i]=1;
   }
   for (i=1;i<=v;i++)
   {
      m1[p[i].y-y]=min(m1[p[i].y-y],p[i].x-x);
      m2[p[i].y-y]=max(m2[p[i].y-y],p[i].x-x);
   }
   for (i=m-1;i>=0;i--)
      m1[i]=min(m1[i],m1[i+1]);
   for (i=0;i<m-1;i++)
      m2[i]=max(m2[i],m1[i+2]+1);
   for (i=1;i<=m;i++)
      m2[i]=max(m2[i],m2[i-1]);
   ans[++o]='N';
   for (i=0;i<m1[1];i++)
      ans[++o]='E';
   for (i=1;i<m;i++)
   {
      for (j=m1[i];j<m1[i+1];j++)
         ans[++o]='E';
      ans[++o]='N';
   }
   for (i=m1[m];i<n;i++)
      ans[++o]='E';
   ans[++o]='S';
   for (i=n;i>m2[m-1];i--)
      ans[++o]='W';
   for (i=m-1;i;i--)
   {
      for (j=m2[i];j>m2[i-1];j--)
         ans[++o]='W';
      ans[++o]='S';
   }
   for (i=m2[0];i;i--)
      ans[++o]='W';
   x=y=0;
   for (i=1;i<=o;i++)
   {
      if (ans[i]=='E')
      {
         n=x+1;
         m=y;
      }
      else if (ans[i]=='W')
      {
         n=x-1;
         m=y;
      }
      else if (ans[i]=='N')
      {
         n=x;
         m=y+1;
      }
      else
      {
         n=x;
         m=y-1;
      }
      if (i>1&&i<o)
         va+=cj(n,m,x,y);
      x=n;
      y=m;
   }
   printf("%d\n",va>>1);
   for (i=1;i<=o;i++)
   {
      if (ans[i]=='E'&&!f1||ans[i]=='W'&&f1)
         putchar('E');
      else if (ans[i]=='E'&&f1||ans[i]=='W'&&!f1)
         putchar('W');
      else if (ans[i]=='N'&&!f2||ans[i]=='S'&&f2)
         putchar('N');
      else
         putchar('S');
   }
   puts("");
   end:
   return 0;
}
