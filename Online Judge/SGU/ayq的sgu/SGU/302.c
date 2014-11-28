#include<stdio.h>
#include<string.h>

char str[1005]={'\0'};
long stack[1005]={0};

int main()
{
   long i,l,top=0;
   scanf("%s",str+1);
   l=strlen(str+1);
   for (i=1;i<=l;i++)
   {
      if (str[i]=='<')
      {
         if (str[i+1]=='U')
            stack[++top]=1;
         else if (str[i+1]=='D')
            stack[++top]=0;
         else
            top--;
         while (str[i]!='>')
            i++;
      }
      else
      {
         if (top)
         {
            if (stack[top]&&str[i]>='a')
               str[i]-=32;
            else if (!stack[top]&&str[i]<='Z')
               str[i]+=32;
         }
         printf("%c",str[i]);   
      }
   }
   printf("\n");
   return 0;
}
