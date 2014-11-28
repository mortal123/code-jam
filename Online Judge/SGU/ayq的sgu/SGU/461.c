#include <stdio.h>

char str[1001][1005]={0};

void work(long l,long r,long h)
{
   long i,j;
   for (i=l;i<=r;i=j+1)
   {
      j=i;
      if (str[i][h]=='*'||str[i][h]=='#')
         while (j<r&&str[j+1][h]==str[i][h])
            j++;
      if (h>1)
         puts("<li>");
      if (i==j)
         puts(str[i]+h);
      else
      {
         if (str[i][h]=='*')
            puts("<ul>");
         else
            puts("<ol>");
         work(i,j,h+1);
         if (str[i][h]=='*')
            puts("</ul>");
         else
            puts("</ol>");
      }
      if (h>1)
         puts("</li>");
   }
}

int main()
{
   long i,n;
   for (i=1;gets(str[i]+1)!=NULL;i++);
   work(1,i-1,1);
   return 0;
}
