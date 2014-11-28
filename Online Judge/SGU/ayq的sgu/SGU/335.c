#include <stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define abb(a) ((a)>0?(a):(-(a)))

int main()
{
   int n,m,cx,cy,tx,ty,ans,ans2,ans3;
   char t;
   scanf("%d%d%d%d%d%d\n%c",&n,&m,&cx,&cy,&tx,&ty,&t);
   if (tx<cx)
   {
      tx=n-tx+1;
      cx=n-cx+1;
   }
   if (ty<cy)
   {
      ty=m-ty+1;
      cy=m-cy+1;
   }
   if (t=='C'&&(tx==cx&&ty==cy+1||tx==cx+1&&ty==cy))
      puts("1");
   else if (n>1&&m>1&&((cx^cy^tx^ty^(t=='C'))&1))
      puts("0");
   else
   {
      if (t=='C')
      {
         if (tx-cx>ty-cy)
            cx++;
         else
            cy++;
      }
      if (n==1)
         ans=2*(m-cy-1)+((ty-cy)&1);
      else if (m==1)
         ans=2*(n-cx-1)+((tx-cx)&1);
      else
      {
         ans=2*(abb(n-1-cx)+abb(m-1-cy)+1);
         ans2=2*(abb(2-cx)+abb(m-1-cy)+1);
         ans3=2*(abb(n-1-cx)+abb(2-cy)+1);
         if (cx==n)
            ans=ans2;
         else if (cy==m)
            ans=ans3;
         else if (cx>=2&&tx-cx<ty-cy)
            ans=max(ans,ans2);
         else if (cy>=2&&tx-cx>ty-cy)
            ans=max(ans,ans3);
      }
      printf("%d\n",ans+(t=='C'));
   }
   return 0;
}
