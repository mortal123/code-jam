#include <stdio.h>
#define oo 1000000000
#define abb(a) ((a)>0?(a):(-(a)))

long h[52]={0},f[52][5101]={0},lastx[52][5101]={0},lasty[52][5101]={0},ans[52]={0};

int main()
{
   long i,j,k,n,s,x,y,t;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%ld",&h[i]);
   s=(n<<1);
   for (i=1;i<=n+1;i++)
      s+=abb(h[i]-h[i-1]);
   s>>=1;
   for (i=0;i<=n+1;i++)
      for (j=0;j<=s;j++)
         f[i][j]=-oo;
   f[0][0]=0;
   for (i=1;i<=n+1;i++)
   {
      x=y=0;
      for (j=i-1;j>=0;j--)
      {
         x+=abb(h[j+1]-h[j]);
         t=x-abb(h[i]-h[j]);
         for (k=t;k<=s;k++)
            if (f[j][k-t]+y>f[i][k])
            {
               f[i][k]=f[j][k-t]+y;
               lastx[i][k]=j;
               lasty[i][k]=k-t;
            }
         y+=h[j];
         x+=2;
      }
   }
   y=0;
   for (i=1;i<=s;i++)
      if (f[n+1][i]>f[n+1][y])
         y=i;
   x=n+1;
   printf("%ld\n",f[x][y]);
   s=0;
   while (x)
   {
      for (i=x-1;i>lastx[x][y];i--)
         ans[++s]=i;
      i=x;
      j=y;
      x=lastx[i][j];
      y=lasty[i][j];
   }
   printf("%ld\n",s);
   for (i=s;i>=1;i--)
      printf("%ld%c",ans[i],(i==1)?'\n':' ');
   return 0;
}
