#include<stdio.h>

struct case1
{
   long x,y;
   char sign;
}p[1001]={{0,0},{'\0'}};

int main()
{
   long i,x,y,ans,t,tot=0;
   char ch;
   while (scanf("%c%ld%ld",&ch,&x,&y)!=EOF)
   {
      getchar();
      if (ch=='+')
      {
         ans=t=0;
         for (i=1;i<=tot;i++)
         {
            if (p[i].sign&&p[i].x>=x&&p[i].y<=y)
               ans++;
            if (p[i].sign==0&&!t)
               t=i;
         }
         if (!t)
            t=++tot;
         p[t].sign=1;
         p[t].x=x;
         p[t].y=y;
         printf("%ld\n",ans);
      }
      else
      {
         for (i=1;i<=tot;i++)
            if (p[i].sign&&p[i].x==x&&p[i].y==y)
            {
               p[i].sign=0;
               break;
            }
         while (p[tot].sign==0&&tot>=1)
            tot--;
      }
   }
   return 0;
}
