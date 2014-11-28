#include <stdio.h>
#define oo 10000000

struct case1
{
   long l,r,h;
}p[101]={0,0,0};
long f[101][2]={0},g[101][2]={0};

int main()
{
   long i,j,x,s,n,x1,y1,x2,y2,st=0,en,ff=oo,gg;
   struct case1 t;
   scanf("%ld%ld%ld%ld%ld%ld%ld",&x,&s,&x1,&y1,&x2,&y2,&n);
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld%ld",&p[i].l,&p[i].r,&p[i].h);
      if (p[i].h>=y1||p[i].h<y2)
      {
         i--;
         n--;
      }
   }
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         if (p[i].h<p[j].h)
         {
            t=p[i];
            p[i]=p[j];
            p[j]=t;
         }
   for (i=1;i<=n;i++)
   {
      if (!st&&p[i].l<x1&&p[i].r>x1)
         st=i;
      if (p[i].l<=x2&&p[i].r>=x2&&p[i].h==y2)
         en=i;
   }
   if (!st)
   {
      if (x1==x2)
         printf("%ld %ld\n",x,s*(x-1)+y1-y2);
      else
         puts("0 0");
   }
   else if (st==en)
   {
      if (x2>=x1)
         printf("%ld %ld\n",x,s*(x-1)+y1-y2+x2-x1);
      else if (x>1)
         printf("%ld %ld\n",x-1,s*(x-1)+y1-y2+x1-x2);
      else
         puts("0 0");
   }
   else
   {
      for (i=1;i<en;i++)
         f[i][0]=f[i][1]=oo;
      f[st][1]=0;
      g[st][1]=y1-p[st].h+p[st].r-x1;
      f[st][0]=1;
      g[st][0]=y1-p[st].h+x1-p[st].l;
      for (i=1;i<en;i++)
      {
         for (j=i+1;j<=en&&(p[j].l>p[i].l||p[j].r<p[i].l);j++);
         if (j<en)
         {
            if (f[j][0]>f[i][0]||f[j][0]==f[i][0]&&g[j][0]>g[i][0]+p[i].h-p[j].h+p[i].l-p[j].l)
            {
               f[j][0]=f[i][0];
               g[j][0]=g[i][0]+p[i].h-p[j].h+p[i].l-p[j].l;
            }
            if (f[j][1]>f[i][0]+1||f[j][1]==f[i][0]+1&&g[j][1]>g[i][0]+p[i].h-p[j].h+p[j].r-p[i].l)
            {
               f[j][1]=f[i][0]+1;
               g[j][1]=g[i][0]+p[i].h-p[j].h+p[j].r-p[i].l;
            }
         }
         else if (j==en)
            if (x2>p[i].l&&(ff>f[i][0]+1||ff==f[i][0]+1&&gg>g[i][0]+p[i].h-y2+x2-p[i].l))
            {
               ff=f[i][0]+1;
               gg=g[i][0]+p[i].h-y2+x2-p[i].l;
            }
            else if (x2<=p[i].l&&(ff>f[i][0]||ff==f[i][0]&&gg>g[i][0]+p[i].h-y2+p[i].l-x2))
            {
               ff=f[i][0];
               gg=g[i][0]+p[i].h-y2+p[i].l-x2;
            }
         for (j=i+1;j<=en&&(p[j].l>p[i].r||p[j].r<p[i].r);j++);
         if (j<en)
         {
            if (f[j][0]>f[i][1]+1||f[j][0]==f[i][1]+1&&g[j][0]>g[i][1]+p[i].h-p[j].h+p[i].r-p[j].l)
            {
               f[j][0]=f[i][1]+1;
               g[j][0]=g[i][1]+p[i].h-p[j].h+p[i].r-p[j].l;
            }
            if (f[j][1]>f[i][1]||f[j][1]==f[i][1]&&g[j][1]>g[i][1]+p[i].h-p[j].h+p[j].r-p[i].r)
            {
               f[j][1]=f[i][1];
               g[j][1]=g[i][1]+p[i].h-p[j].h+p[j].r-p[i].r;
            }
         }
         else if (j==en)
            if (x2>=p[i].r&&(ff>f[i][1]||ff==f[i][1]&&gg>g[i][1]+p[i].h-y2+x2-p[i].r))
            {
               ff=f[i][1];
               gg=g[i][1]+p[i].h-y2+x2-p[i].r;
            }
            else if (x2<p[i].r&&(ff>f[i][1]+1||ff==f[i][1]+1&&gg>g[i][1]+p[i].h-y2+p[i].r-x2))
            {
               ff=f[i][1]+1;
               gg=g[i][1]+p[i].h-y2+p[i].r-x2;
            }
      }
      if (ff<x)
         printf("%ld %ld\n",x-ff,s*(x-1)+gg);
      else
         puts("0 0");
   }
   return 0;
}
