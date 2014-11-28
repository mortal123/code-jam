#include <stdio.h>
#include <string.h>

char a[30005]={'\0'},b[30005]={'\0'},stack[60005]={'\0'};

int main()
{
   long i,j=0,la,lb,st=60001;
   char now;
   scanf("%s%s",a+1,b+1);
   la=strlen(a+1);
   lb=strlen(b+1);
   for (i=1;i<=lb;i++)
   {
      if (st<=60000)
         now=stack[st++];
      else
      {
         if (j>la)
         {
            printf("NO\n");
            goto end;
         }
         now=a[++j];
      }
      if (now==b[i])
      {
         stack[--st]=now;
         stack[--st]=(now^'A'^'B');
      }
   }
   if (j==la&&st==60001)
      printf("YES\n");
   else
      printf("NO\n");
   end:
   return 0;
}
