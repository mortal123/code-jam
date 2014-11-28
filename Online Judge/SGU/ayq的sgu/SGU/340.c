#include <stdio.h>

long stack[1500001]={0};
char str[1500001]={0};

int main()
{
   long i,l,top=0;
   while (gets(str+1)!=NULL)
   {
      l=0;
      for (i=1;str[i]!='$';i++);
      for (i++;str[i]!='$';i++)
         if (str[i]!=' ')
            str[++l]=str[i];
      str[l+1]=0;
      for (i=1;i<=l+1;i++)
      {
         if (str[i]=='+'||str[i]=='-'||str[i]=='/'||str[i]=='*')
         {
            printf("&nbsp;");
            putchar(str[i]);
            printf("&nbsp;");
         }
         else if (str[i]=='{')
         {
            printf((str[i-1]=='^')?"<sup>":"<sub>");
            stack[++top]=(str[i-1]=='^');
         }
         else if (str[i]=='}')
            printf(stack[top--]?"</sup>":"</sub>");
         else if (str[i]>='a'&&str[i]<='z'||str[i]>='A'&&str[i]<='Z')
         {
            if ((str[i-1]<'a'||str[i-1]>'z')&&(str[i-1]<'A'||str[i-1]>'Z'))
               printf("<i>");
            putchar(str[i]);
            if ((str[i+1]<'a'||str[i+1]>'z')&&(str[i+1]<'A'||str[i+1]>'Z'))
               printf("</i>");
         }
         else if (str[i]!='^'&&str[i]!='_'&&str[i])
            putchar(str[i]);
         else if (str[i]=='^'&&str[i+1]!='{')
            printf("<sup>");
         else if (str[i]=='_'&&str[i+1]!='{')
            printf("<sub>");
         if (str[i]!='{')
         {
            if (str[i-1]=='^')
               printf("</sup>");
            else if (str[i-1]=='_')
               printf("</sub>");
         }
      }
      puts("");
   }
   return 0;
}
