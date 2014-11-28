#include<stdio.h>
#include<string.h>

char str[10005]={'\0'};

int main()
{
   long i,j,l,p=0,s=0;
   gets(str+1);
   l=strlen(str+1);
   for (i=1;i<=l;i++)
   {
      if (s<0&&str[i]=='(')
         p=i;
      if (str[i]=='(')
         s--;
      else
         s++;
   }
   if (!p)
      printf("No solution\n");
   else
   {
      s=0;
      str[p]=')';
      for (i=1;i<=p;i++)
         if (str[i]==')')
            s++;
      for (i=1,j=l;i<=l/2-s;i++,j--)
         str[j]=')';
      while (j>p)
      {
         str[j]='(';
         j--;
      }
      puts(str+1);
   }
   return 0;
}
